const ASCII_OFFSET: u8 = 97;

fn main() {
    let vals = vec![
        String::from("abc"),
        String::from("baa"),
        String::from("eee"),
        String::from("abc"),
        String::from("bad"),
        String::from("bab"),
        String::from("abc"),
    ];

    let _vals = radix_sort(vals, 3);
}

fn radix_sort(vals: Vec<String>, width: usize) -> Vec<String> {
    fn inner(vals: &mut Vec<Vec<u8>>, width: usize) {
        for idx in (0..width).rev() {
            counting_sort(vals, width, idx);
            println!("{:?}", decode_vec_strs(vals.clone()));
        }
    }

    println!("{:?}", vals);
    let mut vals = encode_vec_strs(vals);
    inner(&mut vals, width);
    decode_vec_strs(vals)
}

fn counting_sort(vals: &mut Vec<Vec<u8>>, width: usize, l: usize) {
    let sigma = 26;
    let n = vals.len();
    let mut counts = vec![0 as u16; sigma];
    let mut aux = vec![vec![0; width]; n];

    for idx in 0..n {
        let c_idx = vals[idx][l];
        counts[c_idx as usize] += 1;
    }

    let mut sum = 0;
    for idx in 0..sigma {
        let tmp = counts[idx];
        counts[idx] = sum;
        sum += tmp;
    }

    for idx in 0..n {
        let from = idx;
        let to = counts[vals[idx][l] as usize] as usize;
        aux[to] = vals[from].clone();
        counts[vals[idx][l] as usize] += 1;
    }

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
