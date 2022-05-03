use std::cmp::max;

fn main() {
    let knapsack = Knapsack { limit: 20 };

    let items = vec![
        Item { value: 160, weight: 7 },
        Item { value: 90, weight: 3 },
        Item { value: 15, weight: 2 },
    ];

    let max_profit = knapsack.max_profit(&items);

    println!("cart size: {}lbs", knapsack.limit);
    println!();
    println!("items:");
    for item in &items {
        println!("\tvalue: ${:<3}  weight: {}lbs", item.value, item.weight);
    }
    println!();
    println!("max value: {:?}", max_profit);
}

struct Item {
    value: u64,
    weight: u64,
}

struct Knapsack {
    limit: u64,
}

impl Knapsack {
    fn max_profit(&self, items: &[Item]) -> u64 {
        let n = items.len();
        let w = self.limit as usize;
        let mut temp = vec![0u64; w + 1];

        for i in 1..=w {
            for j in 0..n {
                let weight = items[j].weight;
                let value = items[j].value;

                if (weight as usize) <= i {
                    let old = temp[i];
                    let new = {
                        temp[i - (weight as usize)] + value
                    };
                    temp[i] = max(old, new);
                }
            }
        }

        temp[w]
    }
}
