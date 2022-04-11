use std::ops::Not as _;
use std::ptr;

// Only handle a-z right now.
const NUM_CHARS: usize = 26;

fn main() {
    let string = "itwasthebestoftimes";
    let dictionary = vec!["it", "was", "the", "best", "of", "times"];
    let broken = word_break(string, &dictionary);

    println!("Splitting: '{}'", string);
    println!("Found:      {:?}", broken);
}

fn word_break<'s>(s: &'s str, dictionary: &[&str]) -> Vec<&'s str> {
    // &str isn't indexable in Rust because it's UTF-8 encoded, so
    // we split it into a vector of chars, each of which is 4 bytes
    // wide to accomodate the largest possible Unicode characters.
    let chars = s.chars().collect::<Vec<_>>();

    // Make a Trie based on the dictionary.
    let trie = dictionary.iter().fold(TrieNode::new(), |trie, word| {
        trie.insert(word.chars().collect::<Vec<_>>().as_ref())
    });

    // Number of characters.
    let n = chars.len();

    // Initialize our vector of bools to a width equal to the number
    // of character plus one, then set the initial element to true.
    let mut is_good = vec![false; n + 1];
    is_good[0] = true;

    for i in 0..n {
        if is_good[i] {
            let mut node = &trie as *const TrieNode;

            for j in i..n {
                if node.is_null() {
                    break;
                }

                let idx = chars[j] as usize - 'a' as usize;

                unsafe {
                    node = (*node).children[idx];

                    if node.is_null().not() && (*node).is_leaf {
                        is_good[j + 1] = true;
                    }
    
                }
            }
        }
    }

    let broken = {
        let mut result = vec![];

        if is_good[n] {
            let mut rest = s;
            let mut lost = 0;

            for idx in 1..n {
                if is_good[idx] {
                    let (word, remainder) = rest.split_at(idx - lost);
                    lost += word.len();
                    result.push(word);
                    rest = remainder;
                }
            }

            result.push(rest);
        }

        result
    };

    broken
}

#[derive(Debug)]
struct TrieNode {
    is_leaf: bool,
    children: Vec<*mut TrieNode>,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode {
            is_leaf: false,
            children: vec![ptr::null_mut(); NUM_CHARS],
        }
    }

    fn insert(mut self, s: &[char]) -> Self {
        unsafe {
            let mut node = &mut self as *mut TrieNode;

            for c in s {
                // Get the index based on the character.
                let idx = *c as usize - 'a' as usize;

                // Get the appropriate child pointer.
                let child_ptr = (*node).children[idx];

                // If it's null, replace it with a pointer to a new node.
                if child_ptr.is_null() {
                    (*node).children[idx] = raw(TrieNode::new());
                }

                node = (*node).children[idx];
            }

            // We're at a leaf, so mark it as a leaf.
            (*node).is_leaf = true;

            self
        }
    }
}

impl Drop for TrieNode {
    fn drop(&mut self) {
        // Let the memory leak, because writing a correct implementation of this
        // function in Rust is a bit difficult and the program closes almost
        // immediately after this type is dropped anyway.
    }
}

/// Allocate on the heap and convert the owned pointer to a raw pointer.
fn raw<T>(val: T) -> *mut T {
    Box::into_raw(Box::new(val))
}
