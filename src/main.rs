use std::env;

fn main() {
    if env::args().len() > 2 {
        println!("Usage: {} <config file path>", env::args().nth(0).unwrap());
    } else {
        let config_file_path = if env::args().len() == 2 {
            env::args().nth(1).unwrap()
        } else {
            "config/default.json".to_string()
        };
        println!("Config file path: {}", config_file_path);
        let file: Result<File, Error> = File::open(config_file_path);
    }
}
