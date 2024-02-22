use std::env;
use std::fs::File;
use std::io;
use std::io::BufReader;
mod types;
use crate::types::config::Config;

fn main()
{
    let args: Vec<String> = env::args().collect();
    if args.len() > 2
    {
        println!("Usage: {} <config file path>", args[0]);
    }
    else
    {
        let config_file_path = match args.len()
        {
            2 => &args[1],
            _ => "config/default.json",
        };

        let file: Result<File, io::Error> = File::open(config_file_path.to_string());
        match file
        {
            Ok(f) =>
            {
                let reader: BufReader<File> = BufReader::new(f);
                let config: Config = serde_json::from_reader(reader).unwrap();
                println!("{:?}", config);
            }
            Err(e) =>
            {
                println!("Error: {}", e);
            }
        }
    }
}
