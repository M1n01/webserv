use serde::Deserialize;

#[derive(Debug, Deserialize)]
pub struct Route
{
    pub path: String,
    pub allow_methods: Vec<String>,
    pub redirect: String,
    pub root: String,
    pub autoindex: bool,
    pub index: String,
    pub cgi: String,
    pub upload: String,
    pub upload_path: String,
    pub auth: String,
}

#[derive(Debug, Deserialize)]
pub struct Config
{
    pub server: String,
    pub hostname: String,
    pub port: i32,
    pub error_page: String,
    pub max_client_body_size: i32,
    pub route: Route,
    pub timeout: i32,
    pub index: String,
    pub autoindex: bool,
}
