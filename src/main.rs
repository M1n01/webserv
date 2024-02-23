use std::env;
use std::fs::File;
use std::io;
use std::io::BufReader;
mod types;
use crate::types::config::WebServerConfig;

fn load_config(file_path: &str) -> Result<WebServerConfig, serde_json::Error>
{
    let file: Result<File, io::Error> = File::open(file_path.to_string());
    match file
    {
        Ok(f) =>
        {
            let reader: BufReader<File> = BufReader::new(f);
            let config: WebServerConfig = serde_json::from_reader(reader).unwrap();
            Ok(config)
        }
        Err(e) => Err(serde_json::Error::io(e)),
    }
}

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
            Ok(f) => match load_config(config_file_path)
            {
                Ok(config) =>
                {
                    println!("Config: {:?}", config);
                    
                }
                Err(e) =>
                {
                    println!("Error: {}", e);
                }
            },
            Err(e) =>
            {
                println!("Error: {}", e);
            }
        }
    }
}
