use std::collections::HashMap;
use std::fs::File;
use std::io;
use std::io::{BufRead, BufReader};

fn parse_line(line: String, network: &mut HashMap<String, [String; 2]>) -> bool {
    if line.len() >= 16 {
        let key = String::from(&line[0..3]);
        let left = String::from(&line[7..10]);
        let right = String::from(&line[12..15]);

        network.insert(key.clone(), [left, right]);
        return true;
    }
    return false;
}
fn main() -> io::Result<()> {
    const PATH: &'static str = "8.txt";
    let file = File::open(&PATH)?;
    let mut reader = BufReader::new(file);

    let mut instructions = String::new();
    reader.read_line(&mut instructions)?;
    instructions = instructions.trim().to_string();
    let mut instructions = instructions.chars().cycle();

    let mut network = HashMap::<String, [String; 2]>::new();

    for line in reader.lines() {
        let line = line?;
        parse_line(line, &mut network);
    }
    let mut key = "AAA";
    let mut steps = 0;
    while key != "ZZZ" {
        let instruction = instructions.next().unwrap();
        // println!("{}{}: {}", steps, instruction, key);
        let index = match instruction {
            'L' => 0,
            'R' => 1,
            _ => panic!("Invalid direction"),
        };
        let options = network.get(key);
        match options {
            Some(v) => {
                key = &v[index];
            }
            None => panic!("No value for key {}", key),
        }
        steps += 1;
    }
    println!("Steps required: {}", steps); // 20093
    return Ok(());
}
