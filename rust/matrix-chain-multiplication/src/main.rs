use ndarray::prelude::*;
use std::f64;

fn main() {
    let dims = [50, 20, 1, 10, 100];
    let (min_cost, sequence) = min_matrix_mult(&dims);
    explain_min(&dims, min_cost);
    explain_parens(&sequence);
}

fn min_matrix_mult(dims: &[u64]) -> (u64, Array2<usize>) {
    // Capture 'n' which is the number of matrices + 1.
    let n = dims.len() - 1;

    // Start out with the costs array initialized to infinities.
    let mut costs = Array2::from_elem((n, n), f64::INFINITY);

    // The sequence of parens which leads to the optimal answer.
    let mut sequence = Array2::from_elem((n, n), 0);

    // Initialize self-multiply costs to 0.
    for i in 0..n {
        costs[[i, i]] = 0.0;
    }

    // Get increasing lengths, from 2 up to the number of dimensions.
    for length in 1..n {
        // Starting values for the spans range from 0 to the number of dimensions
        // minus the current span length.
        for start in 0..(n - length) {
            // The end value is the starting position, plus the length minus 1.
            let end = start + length;

            // The middle ranges from 0 to the end minus 1.
            for middle in start..end {
                let cost = {
                    // Get the cost of the left side of the parens
                    let left = costs[[start, middle]];
                    // Get the cost of the right side of the parens
                    let right = costs[[middle + 1, end]];
                    // Get the cost of combining them.
                    let combine = (dims[start] * dims[middle + 1] * dims[end + 1]) as f64;
                    // The sum of these is the cost for this span.
                    left + right + combine
                };

                // If the cost is lower than the known cost for that span, use it.
                if cost < costs[[start, end]] {
                    costs[[start, end]] = cost;
                    sequence[[start, end]] = middle;
                }
            }
        }
    }

    return (costs[[0, n - 1]] as u64, sequence);
}

fn explain_min(dims: &[u64], min_cost: u64) {
    println!("MATRICES:");
    for (idx, matrix) in dims.windows(2).enumerate() {
        println!("M_{} = ({}✕{}) ", idx, matrix[0], matrix[1]);        
    }
    println!();

    println!("COST:\n{}", min_cost);
    println!();
}

fn explain_parens(sequence: &Array2<usize>) {
    fn explain_parens_inner(sequence: &Array2<usize>, start: usize, end: usize, in_a_result: &mut [bool]) {
        if start != end {
            let middle = sequence[[start, end]];
            explain_parens_inner(sequence, start, middle, in_a_result);
            explain_parens_inner(sequence, middle + 1, end, in_a_result);
            let i_string = format!("{}", if in_a_result[start] { "_result " } else { " " });
            let j_string = format!("{}", if in_a_result[end] { "_result " } else { " " });
            println!("M_{}{}✕ M_{}{}", start, i_string, end, j_string);
            in_a_result[start] = true;
            in_a_result[end] = true;
        }
    }

    println!("SEQUENCE:");
    let (_, n_cols) = sequence.dim();
    let mut in_a_result = vec![false; sequence.len()];
    explain_parens_inner(sequence, 0, n_cols - 1, &mut in_a_result);
}
