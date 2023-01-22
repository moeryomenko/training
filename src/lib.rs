use std::cmp::Ordering;

pub fn count_negatives(grid: Vec<Vec<i32>>) -> i32 {
    let mut end = match grid.first() {
        Some(vec) => vec.len(),
        None => return 0,
    };
    grid.iter().fold(0, |sum, v| {
        end = v[0..end].partition_point(|&n| n >= 0);
        sum + (v.len() - end)
    }) as i32
}

pub fn find_numbers(nums: Vec<i32>) -> i32 {
    nums.into_iter()
        .filter(|&n| ((n as f64).log10() as i32 + 1) % 2 == 0)
        .count() as _
}

pub fn trap_rain_water(nums: Vec<i32>) -> i32 {
    let index = nums
        .iter()
        .enumerate()
        .max_by(|(_, &a), (_, b)| a.partial_cmp(b).unwrap_or(Ordering::Equal))
        .map(|(index, _)| index)
        .unwrap();

    let sum = |part: Vec<i32>| {
        let mut max = 0;
        return part.into_iter().fold(0i32, |mut sum, e| {
            max = max.max(e);
            sum += max - e;
            sum
        });
    };

    let mut right = nums[index..].to_vec();
    right.reverse();

    sum(nums[0..index].to_vec()) + sum(right)
}

pub fn pivot_index(nums: Vec<i32>) -> i32 {
    let sum: i32 = nums.iter().sum();
    let mut psum = 0i32;
    let is_pivot = |&n| {
        if sum - psum - n == psum {
            true
        } else {
            psum += n;
            false
        }
    };
    match nums.iter().position(is_pivot) {
        Some(idx) => idx as i32,
        None => -1,
    }
}

pub fn min_cost_climbing_stairs(mut cost: Vec<i32>) -> i32 {
    for i in 2..cost.len() {
        cost[i] += cost[i - 1].min(cost[i - 2])
    }

    *cost.last().unwrap().min(&cost[cost.len() - 2])
}

pub fn find_gcd(nums: Vec<i32>) -> i32 {
    let (min, max) = minmax(nums);
    gcd(min, max)
}

pub fn minmax(nums: Vec<i32>) -> (i32, i32) {
    let (mut min, mut max) = (nums[0], nums[0]);
    for &n in &nums[1..] {
        if n < min {
            min = n;
            continue;
        }
        if n > max {
            max = n;
            continue;
        }
    }
    (min, max)
}

pub fn gcd(mut n: i32, mut m: i32) -> i32 {
    assert!(n != 0 && m != 0);
    while m != 0 {
        if m < n {
            std::mem::swap(&mut m, &mut n);
        }
        m %= n;
    }
    n
}

pub fn fib(n: i32) -> i32 {
    if n == 0 || n == 1 {
        return 1;
    }
    let root_5: f64 = 5.0_f64.sqrt();
    let gold_ratio: f64 = (1. + root_5) / 2.;
    let reverse_gold_ratio: f64 = (1. - root_5) / 2.;

    ((gold_ratio.powi(n) - reverse_gold_ratio.powi(n)) / root_5).round() as _
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn check_count_negatives() {
        assert_eq!(
            count_negatives(vec![
                vec![4, 3, 2, -1],
                vec![3, 2, 1, -1],
                vec![1, 1, -1, -2],
                vec![-1, -1, -2, -3],
            ]),
            8
        );
    }

    #[test]
    fn check_find_numbers() {
        assert_eq!(find_numbers(vec![12, 345, 2, 6, 7896]), 2);
    }

    #[test]
    fn check_pivot_index() {
        assert_eq!(pivot_index(vec![1, 7, 3, 6, 5, 6]), 3);
        assert_eq!(pivot_index(vec![1, 2, 3]), -1);
        assert_eq!(pivot_index(vec![2, 1, -1]), 0);
    }

    #[test]
    fn check_find_gcd() {
        assert_eq!(find_gcd(vec![2, 5, 6, 9, 10]), 2);
        assert_eq!(find_gcd(vec![7, 5, 6, 8, 3]), 1);
        assert_eq!(find_gcd(vec![3, 3]), 3);
    }

    #[test]
    fn check_trap() {
        assert_eq!(trap_rain_water(vec![0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]), 6);
    }

    #[test]
    fn check_min_cost_climbing_stairs() {
        assert_eq!(min_cost_climbing_stairs(vec![10, 15, 20]), 15);
        assert_eq!(
            min_cost_climbing_stairs(vec![1, 100, 1, 1, 1, 100, 1, 1, 100, 1]),
            6
        );
    }
}
