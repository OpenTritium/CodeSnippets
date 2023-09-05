fn main() {
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .expect("密文读取失败");
    let mut offset = String::new();
    std::io::stdin().read_line(&mut offset).expect("非法偏移量");
    let offset = offset.trim().parse::<u8>().expect("类型转换失败");
    const ROUND: u8 = 26;
    if offset > ROUND {
        panic!("超过周期");
    }
    for i in 0..ROUND {
        let input = input
            .chars()
            .map(|x| match x {
                b @ 'A'..='Z' => {
                    ((((b as u8 - 'A' as u8) + ROUND + (i * offset) % ROUND) % ROUND) + 'a' as u8)
                        as char
                }
                s @ 'a'..='z' => {
                    ((((s as u8 - 'a' as u8) + ROUND + (i * offset) % ROUND) % ROUND) + 'A' as u8)
                        as char
                }
                n => n,
            })
            .collect::<String>();
        print!("暴力破解第{i}轮：{input}");
    }
}
