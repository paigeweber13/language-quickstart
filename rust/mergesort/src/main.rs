use rand::prelude::*;

fn randomize_array(array: &mut Vec<f32>) {
    let mut rng = rand::thread_rng();

    let max_rand_number = 100.0;
    let mut this_random_number: f32;

    for _ in 0..array.capacity() {
        this_random_number = rng.gen();
        array.push(this_random_number * max_rand_number);
    }

    ()
}

fn main() {
    let mut array: Vec<f32> = Vec::with_capacity(10);
    println!("{:?}", array);
    randomize_array(&mut array);
    println!("{:?}", array);
}
