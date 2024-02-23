use serde::{Deserialize, Serialize};
use std::collections::HashMap;

#[derive(Serialize, Deserialize, Debug)]
pub struct WebServerConfig
{
    pub servers: Vec<Server>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Server
{
    pub host: String,
    pub port: u16,
    pub server_names: Option<Vec<String>>,
    pub default_error_pages: HashMap<String, String>,
    pub client_body_size_limit: Option<usize>, // bytes
    pub routes: Vec<Route>,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Route
{
    pub path: String,
    pub accepted_methods: Option<Vec<String>>,
    pub http_redirection: Option<String>,
    pub source: Option<Source>,
    pub directory_listing: Option<bool>,
    pub default_file: Option<String>,
    pub cgi: Option<CgiConfig>,
    pub accept_uploads: Option<UploadConfig>,
}

#[derive(Serialize, Deserialize, Debug)]
pub enum Source
{
    Directory(String),
    File(String),
}

#[derive(Serialize, Deserialize, Debug)]
pub struct CgiConfig
{
    pub extension: String,
    pub executable_path: String,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct UploadConfig
{
    pub save_path: String,
}
