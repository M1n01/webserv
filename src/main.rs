use std::env;
use std::fs::File;
use std::io;
use std::io::BufReader;
mod types;
use crate::types::config::WebServerConfig;
use hyper::service::{make_service_fn, service_fn};
use hyper::{Body, Response, Server};
use std::convert::Infallible;
use std::net::SocketAddr;
use std::sync::Arc;
// mod connection;
// use crate::connection::event_loop;

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

#[tokio::main]
async fn main()
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

        match load_config(config_file_path)
        {
            Ok(config) =>
            {
                let config = Arc::new(config);
                let addr = format!("{}:{}", config.servers[0].host, config.servers[0].port)
                    .parse::<SocketAddr>()
                    .expect("Unable to parse socket address");
                // サービス関数の定義
                let make_svc = make_service_fn(move |_conn| {
                    let config_clone = config.clone(); // クロージャ内で使用するためにクローン

                    // すべてのリクエストに対して同じレスポンスを返す
                    async move {
                        Ok::<_, Infallible>(service_fn(move |_req| async move {
                            Ok::<_, Infallible>(Response::new(Body::from("Hello, World!")))
                        }))
                    }
                });
                // サーバーの立ち上げ
                let server = Server::bind(&addr).serve(make_svc);

                println!("Serving on http://{}", addr);

                if let Err(e) = server.await
                {
                    eprintln!("server error: {}", e);
                }
            }
            Err(e) =>
            {
                println!("Error: {}", e);
            }
        }
    }
}
