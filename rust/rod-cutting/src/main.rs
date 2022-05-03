use std::fmt::{Display, Formatter};
use std::cmp::max;

/// A rod which may be subdivided and sold for parts.
#[derive(Debug)]
struct Rod {
    length: u64,
}

impl Rod {
    /// Make a new rod of the given length.
    ///
    /// Only permit rods with a length greater than 0.
    fn inches_long(length: u64) -> Option<Rod> {
        if length == 0 {
            return None;
        }

        Some(Rod { length })
    }

    /// Calculate the maximum revenue from splitting up the rod
    ///
    /// This algorithm works because rod cutting displays optimal substructure.
    /// The max revenue to be gained from splitting a rod of length n
    /// into sub-rods of lengths a and b is going to be the max revenue
    /// of splitting a rod of length a plus the max revenue of splitting
    /// a rod of length b.
    ///
    /// This algorithm works by working through rods of increasing
    /// total size, from 1 to the size of the rod in question, and for
    /// each possible length working out the max revenue for each possible
    /// split, saving the maxes in a vector. At the end, the value at
    /// the end of the vector is the maximum revenue for splitting a rod
    /// of length n.
    fn max_revenue(&self, prices: &[Price]) -> Price {
        eprintln!("Calculating max revenue for rod length of {} inches", self.length);

        let mut poss_revenue = vec![0; (self.length + 1) as usize];

        eprintln!("Values: {:?}", poss_revenue);

        for poss_length in 1..=(self.length as usize) {
            eprintln!("Length: {} inches", poss_length);

            for remainder_length in 1..=poss_length {
                eprintln!("Split at: {} inches", remainder_length);

                // 0, as set at initialization.
                let prior_revenue = poss_revenue[poss_length];

                // The revenue, previously known, for the subpart of the split.
                let sub_revenue = poss_revenue[poss_length - remainder_length];
                // The revenue for the remainder of the currently-assessed sub length.
                let remainder_revenue = prices[remainder_length - 1].0;
                // The revenue of the full split.
                let split_revenue = sub_revenue + remainder_revenue;

                // Pick the better one.
                let max_revenue = max(prior_revenue, split_revenue);

                eprintln!("Prior best: {}", Price(prior_revenue));
                eprintln!("New chance: {}", Price(split_revenue));
                eprintln!("Better one: {}", Price(max_revenue));

                // Save the better one.
                poss_revenue[poss_length] = max_revenue;

                eprintln!("Values: {:?}", poss_revenue);
            }
        }

        let max_revenue = Price(poss_revenue[self.length as usize]);

        eprintln!("Max: {}", max_revenue);

        max_revenue
    }
}

/// The price a length will fetch when sold.
#[derive(Debug, Copy, Clone, Ord, PartialOrd, Eq, PartialEq)]
struct Price(u64);

impl Display for Price {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        // Pretty print with a dollar sign.
        write!(f, "${}", self.0)
    }
}

fn main() {
    let rod = Rod::inches_long(4).expect("rod length is greater than 0");

    let prices = vec![
        Price(1),
        Price(5),
        Price(8),
        Price(9),
        Price(10),
        Price(17),
        Price(17),
        Price(20),
        Price(24),
        Price(30),
    ];

    let max_revenue = rod.max_revenue(&prices);
    println!("Max revenue is {}", max_revenue);
}
