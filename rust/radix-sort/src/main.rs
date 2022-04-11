const ASCII_OFFSET: u8 = 97;

fn main() {
    let vals = vec![
        String::from("no"),
        String::from("is"),
        String::from("th"),
        String::from("ti"),
        String::from("fo"),
        String::from("al"),
        String::from("go"),
        String::from("pe"),
        String::from("to"),
        String::from("co"),
        String::from("to"),
        String::from("th"),
        String::from("ai"),
        String::from("of"),
        String::from("th"),
        String::from("pa"),
    ];

    println!("{:?}", vals);
    let vals = radix_sort(vals, 2);
    println!("{:?}", vals);
}

fn radix_sort(vals: Vec<String>, width: usize) -> Vec<String> {
    fn inner(vals: &mut Vec<Vec<u8>>, width: usize) {
        for idx in (0..width).rev() {
            println!("sorting {} from the right", width - idx - 1);

            counting_sort(vals, width, idx);
        }
    }

    let mut vals = encode_vec_strs(vals);
    inner(&mut vals, width);
    decode_vec_strs(vals)
}

fn counting_sort(vals: &mut Vec<Vec<u8>>, width: usize, l: usize) {
    let sigma = 26;
    let n = vals.len();
    let mut counts = vec![0 as u16; sigma];
    let mut aux = vec![vec![0; width]; n];

    println!("phase: counting");

    for idx in 0..n {
        let c_idx = vals[idx][l];
        println!("found {}, count now {}", decode_char(c_idx), counts[c_idx as usize] + 1);
        counts[c_idx as usize] += 1;
    }

    println!("phase: converting counts to indices");

    let mut sum = 0;
    for idx in 0..sigma {
        println!("count at {} was {}, is now index {}", idx, counts[idx], sum);

        let tmp = counts[idx];
        counts[idx] = sum;
        sum += tmp;
    }

    println!("phase: moving into auxilliary storage based on indices");

    for idx in 0..n {
        let from = idx;
        let to = counts[vals[idx][l] as usize] as usize;
        println!("copying from index {} to index {} in auxilliary storage", from, to);
        aux[to] = vals[from].clone();
        counts[vals[idx][l] as usize] += 1;
    }

    println!("phase: replacing input with now-sorted auxilliary storage");

    *vals = aux;
}

fn encode_vec_strs(vals: Vec<String>) -> Vec<Vec<u8>> {
    vals
        .iter()
        .map(|s| s.chars().map(encode_char).collect::<Vec<_>>())
        .collect()
}

fn decode_vec_strs(vals: Vec<Vec<u8>>) -> Vec<String> {
    vals
        .into_iter()
        .map(|v| v.into_iter().map(decode_char).collect::<String>())
        .collect()
}

fn encode_char(val: char) -> u8 {
    val as u8 - ASCII_OFFSET
}

fn decode_char(val: u8) -> char {
    unsafe { char::from_u32_unchecked((val + ASCII_OFFSET) as u32) }
}
