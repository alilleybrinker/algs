use ndarray::prelude::*;

fn main() {
    let from = "cast";
    let s = from.chars().collect::<Vec<_>>();
    let to = "cats";
    let t = to.chars().collect::<Vec<_>>();
    let d = distance(&s, &t);
    println!("edit distance from {} to {} is {}", from, to, d);
}

fn distance(s: &[char], t: &[char]) -> u64 {
    let m = s.len();
    let n = t.len();

    let mut d = Array2::from_elem((m, n), 0);

    for i in 0..m {
        d[[i, 0]] = i;
    }

    for j in 0..n {
        d[[0, j]] = j;
    }

    for j in 1..n {
        for i in 1..m {
            let sub_cost = if s[i] == t[j] {
                0
            } else {
                1
            };

            d[[i, j]] = {
                let del = d[[i - 1, j]] + 1;
                let ins = d[[i, j - 1]] + 1;
                let sub = d[[i - 1, j - 1]] + sub_cost;
                vec![del, ins, sub].into_iter().min().unwrap()
            }
        }
    }

    d[[m - 1, n - 1]] as u64
}
