
use ndarray::prelude::*;
use std::char;

const NUM_LETTERS: usize = 4;
const ASCII_OFFSET: u8 = 97;

type Array = Array2<usize>;

fn main() {
    let haystack = "abcabcd";
    let needle = "abcdabd";

    let result = kmp(&to_ascii_offset(haystack), &to_ascii_offset(needle));
    println!("finding {:?} in {:?}: {:?}", needle, haystack, result)
}

fn make_dfa(pattern: &[u8]) -> Array {
    let m = pattern.len();
    let n = NUM_LETTERS;

    let mut dfa = Array::default((n, m));

    dfa[[pattern[0] as usize, 0]] = 1;

    let mut x = 0;
    let mut j = 1;

    while j < m {
        let mut c = 0;

        while c < NUM_LETTERS {
            dfa[[c, j]] = dfa[[c, x]];
            c += 1;
        }

        dfa[[pattern[j] as usize, j]] = j + 1;
        x = dfa[[pattern[j] as usize, x]];
        j += 1;
    }

    dfa
}

fn kmp(haystack: &[u8], needle: &[u8]) -> Option<usize> {
    let dfa = make_dfa(needle);
    let (_, m) = dfa.dim();
    let n = haystack.len();

    eprintln!("DFA:");
    eprintln!("{:?}", dfa);

    eprintln!("n = {}", n);
    eprintln!("m = {}", m);

    let mut i = 0;
    let mut j = 0;

    while i < n && j < m {
        eprintln!("NEW ITERATION:");
        eprintln!("i = {}", i);
        eprintln!("j = {}", j);

        let c = haystack[i];
        let i1 = c as usize;
        let i2 = j;

        j = dfa[[i1, i2]];

        eprintln!("character  = {}", decode_char(c));
        eprintln!("next state = {}", j);

        i += 1;
    }

    eprintln!("j = {}", j);
    eprintln!("m = {}", m);

    if j == m {
        Some(i - m)
    } else {
        None
    }
}

fn to_ascii_offset(s: &str) -> Vec<u8> {
    s.as_bytes().iter().map(|b| b - ASCII_OFFSET).collect()
}

#[allow(unused)]
fn decode_char(val: u8) -> char {
    let val = val + ASCII_OFFSET;

    unsafe { char::from_u32_unchecked(val as u32) }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        let haystack = "abcd";
        let needle = "abcd";
        
        let result = kmp(&to_ascii_offset(haystack), &to_ascii_offset(needle));
        assert_eq!(result, Some(0));
    }

    #[test]
    fn basic_plus_suffix() {
        let haystack = "abcdddddd";
        let needle = "abcd";
        
        let result = kmp(&to_ascii_offset(haystack), &to_ascii_offset(needle));
        assert_eq!(result, Some(0));
    }

    #[test]
    fn basic_plus_prefix() {
        let haystack = "dabcd";
        let needle = "abcd";
        
        let result = kmp(&to_ascii_offset(haystack), &to_ascii_offset(needle));
        assert_eq!(result, Some(1));
    }

    #[test]
    fn basic_plus_long_prefix() {
        let haystack = "bbbbbbaaaadabcd";
        let needle = "abcd";
        
        let result = kmp(&to_ascii_offset(haystack), &to_ascii_offset(needle));
        assert_eq!(result, Some(11));
    }
}
