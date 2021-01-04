use rand::prelude::*;

fn main() {
    let mut array = create_random_array(10);
    println!("{:?}", array);
    println!("Array is ordered? {}", array_is_ordered(array));
    let ordered = vec![1.0, 2.0, 3.0];
    println!("{:?}", ordered);
    println!("Array is ordered? {}", array_is_ordered(ordered));

    // doesn't work?
    // println!("{:?}", merge(array, ordered));
}

/* ----------- mergesort ----------- */
fn mergesort(array: Vec<f32>) -> Vec<f32> {
    Vec::new()
}

fn merge(mut left: Vec<f32>, mut right: Vec<f32>) -> Vec<f32> {
    let mut combined: Vec<f32> = Vec::with_capacity(left.len() + right.len());
    combined.append(&mut left);
    combined.append(&mut right);
    combined
}

/* ----------- utils ----------- */
fn create_random_array(n: usize) -> Vec<f32>{
    let mut array: Vec<f32> = Vec::with_capacity(n);
    let mut rng = rand::thread_rng();

    let max_rand_number = 100.0;
    let mut this_random_number: f32;

    for _ in 0..array.capacity() {
        this_random_number = rng.gen();
        array.push(this_random_number * max_rand_number);
    }

    array
}

fn array_is_ordered(array: Vec<f32>) -> bool {
    for i in 0..(array.len() - 1) {
        if array[i] > array[i+1] {
            return false;
        }
    }

    true
}
