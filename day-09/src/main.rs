use std::fs::File;
use std::io;
use std::io::{BufRead, BufReader};

fn differences(v: &Vec<i64>) -> Vec<i64> {
    let mut result = Vec::with_capacity(v.len() - 1);
    for w in v.windows(2) {
        result.push(w[1] - w[0]);
    }
    return result;
}
fn main() -> io::Result<()> {
    const PATH: &'static str = "9.txt";
    let file = File::open(PATH)?;
    let reader = BufReader::new(file);

    let mut total = 0;
    for line in reader.lines() {
        let mut histories = vec![];
        let mut start = line?
            .split(" ")
            .map(|s| i64::from_str_radix(s, 10).unwrap())
            .collect::<Vec<i64>>();
        start.reverse(); // for part 2
        histories.push(start.clone());
        while start.iter().fold(false, |acc, n| acc || (*n != 0i64)) {
            start = differences(&start);
            histories.push(start.clone());
        }
        let end = histories.len() - 1;
        histories[end].push(0);

        for i in (1..end + 1).rev() {
            let end = histories[i].len() - 1;
            let diff = histories[i][end];
            let prev = histories[i - 1][end];
            histories[i - 1].push(diff + prev);
        }
        let end = histories[0].len() - 1;
        total += histories[0][end];
    }
    println!("{}", total); // 1901217887, 905

    Ok(())
}
