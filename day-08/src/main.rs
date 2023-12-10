use std::collections::HashMap;
use std::fs::File;
use std::io;
use std::io::{BufRead, BufReader};
use std::ops::Index;

fn gcd(mut a: u128, mut b: u128) -> u128 {
    let mut c;
    while b != 0 {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}
fn lcm(a: u128, b: u128) -> u128 {
    a * b / gcd(a, b)
}
#[derive(Debug, Clone, Copy)]
enum NodeType {
    Start,
    End,
    Regular,
}
#[derive(Debug, Clone, Copy)]
enum Direction {
    Left,
    Right,
}
#[derive(Debug, Clone)]
struct Node {
    kind: NodeType,
    left: String,
    right: String,
}
impl Node {
    fn end(&self) -> bool {
        match self.kind {
            NodeType::End => true,
            _ => false,
        }
    }
}
impl Index<&Direction> for Node {
    type Output = String;
    fn index(&self, direction: &Direction) -> &Self::Output {
        match direction {
            Direction::Left => &self.left,
            Direction::Right => &self.right,
        }
    }
}

fn parse_line(line: String, network: &mut HashMap<String, Node>) -> Option<String> {
    if line.len() >= 16 {
        let key = String::from(&line[0..3]);
        let left = String::from(&line[7..10]);
        let right = String::from(&line[12..15]);

        let node_type = match line.chars().nth(2) {
            Some('A') => NodeType::Start,
            Some('Z') => NodeType::End,
            Some(_) => NodeType::Regular,
            _ => unreachable!(),
        };
        let n = Node {
            kind: node_type,
            left,
            right,
        };
        network.insert(key.clone(), n.clone());
        match n.kind {
            NodeType::Start => return Some(key),
            _ => return None,
        }
    }
    return None;
}
fn main() -> io::Result<()> {
    const PATH: &'static str = "8.txt";
    let file = File::open(&PATH)?;
    let mut reader = BufReader::new(file);

    let mut instructions = String::new();
    reader.read_line(&mut instructions)?;
    instructions = instructions.trim().to_string();
    let mut instructions = instructions.chars().cycle();

    let mut network = HashMap::<String, Node>::new();

    let mut start = vec![];

    for line in reader.lines() {
        let line = line?;
        match parse_line(line, &mut network) {
            Some(k) => start.push(k),
            _ => {}
        }
    }
    // let mut key = "AAA";
    let mut steps: u64 = 1;
    let mut required_steps = vec![];
    loop {
        let mut is_done = true;
        for k in start.iter() {
            is_done = is_done && network.get(k).unwrap().end();
        }
        if is_done {
            break;
        }
        let instruction = instructions.next().unwrap();
        // println!("{}{}: {}", steps, instruction, key);
        let dir = match instruction {
            'L' => Direction::Left,
            'R' => Direction::Right,
            _ => panic!("Invalid direction"),
        };
        let mut i = 0;
        loop {
            if i >= start.len() {
                break;
            }
            let key = start.get_mut(i).unwrap();
            let options = network.get(key);
            match options {
                Some(v) => {
                    *key = String::from(&v[&dir]);
                }
                None => panic!("No value for key {}", key),
            }
            if network.get(key).unwrap().end() {
                start.remove(i);
                required_steps.push(steps);
                continue;
            }
            i += 1;
        }
        if start.len() <= 0 {
            break;
        }

        steps += 1;
        if steps % 1000000 == 0 {
            println!("{}", steps);
        }
    }
    let mut result: u128 = required_steps[0] as u128;
    // The number of steps for all paths from XXA to XXZ can be 
    // found by the least common multiple of the number of steps to reach
    // XXZ for each path
    for value in required_steps {
        result = lcm(result, value as u128);
        print!("{} ", value);
    }
    println!("\nSteps required: {}", result);
    return Ok(());
}
