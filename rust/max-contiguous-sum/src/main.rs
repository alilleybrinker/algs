fn main() {
    let data = vec![5, 15, -30, 10, -5, 40, 10];
    let answer = max_sum(&data);
    println!("Sequence: {:?}", data);
    println!("Maximum subsequence: {:?}", answer);
}

#[derive(Debug, Copy, Clone, Default)]
struct MaxSum {
    /// The sum of the subsequence.
    sum: i32,

    /// Inclusive range for the beginning
    start: usize,

    /// Inclusive range for the end
    end: usize,
}

fn max_sum(data: &[i32]) -> MaxSum {
    data.iter()
        .enumerate()
        .fold(
            (MaxSum::default(), MaxSum::default()),
            |(mut best, mut current), (idx, val)| {
                current.end = idx;

                // If the current sum is less than 0, reset it to restart on
                // the current value, and reset current start to current end.
                // Otherwise, keep updating the current sum.
                if current.sum <= 0 {
                    current.start = current.end;
                    current.sum = *val;
                } else {
                    current.sum += *val;
                }

                // If the current_sum is better than the known-best sum seen
                // so far, then we have a new best!
                if current.sum > best.sum {
                    best = current;
                }

                (best, current)
            },
        )
        // Throw away the 'current' value, just return the best.
        .0
}
