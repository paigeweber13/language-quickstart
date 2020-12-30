use bytes::Bytes;
use regex::Regex;
use scraper::{Html, Selector};

use reqwest::Response;

// pub fn save_image(image_bytes: &Bytes, file_name: &str) {

// }

// pub async fn save_image(image_bytes: Response, containing_dir: &str, file_name: &str) {
pub fn save_image(image_bytes: &Bytes, containing_dir: &str, file_name: &str) {
    println!("INFO: Saving image to {}/{}", containing_dir, file_name);

    /*
    std::fs::create_dir_all(containing_dir);

    let mut full_path: String = String::from(containing_dir);
    full_path.push_str("/");
    full_path.push_str(file_name);

    let path = std::path::Path::new(&full_path);
    let display = path.display();

    let mut file = match std::fs::File::create(&path) {
        Ok(file) => file,
        Err(error) => panic!("Couldn't create file {}: {}", display, error),
    };

    let image_bytes: &mut [u8] = &mut image_bytes.slice(..);

    // match std::io::copy(&mut image_bytes.bytes().await.unwrap(), &mut file) {
    match std::io::copy(&mut image_bytes, &mut file) {
    // match image_bytes.copy_to(&mut file) {
        Ok(_) => println!("Successfully wrote to {}", display),
        Err(error) => panic!("Couldn't write to {}: {}", display, error),
    };

    ()
    */
}

pub async fn download_all_images_on_page(page_html: &str) {

    println!("INFO: downloading all images on page");

    let img_download_dir = "img/";

    let img_selector = Selector::parse("img[src]").unwrap();
    // let this_page_url = &response.url().as_str();

    let page_html = Html::parse_document(&page_html);

    for img_element in page_html.select(&img_selector) {            
        let img_src = img_element.value().attr("src").unwrap();

        // determine directory for image
        let mut img_containing_dir = String::from(img_download_dir);
        let re_domain = Regex::new(r"://([^/]*)/").unwrap();
        for cap in re_domain.captures_iter(img_src) {
            // this loop will execute exactly once for valid urls
            img_containing_dir.push_str(&cap[1]);
        }

        // determine file name for image
        let mut img_file_name = String::new();

        // this regex will grab everything it can until it has to match a
        // forward slash. Then the group grabs everything after that last slash
        let re_image_name = Regex::new(r".*/(.*)").unwrap();
        for cap in re_image_name.captures_iter(img_src) {
            img_file_name.push_str(&cap[1]);
        }

        // get image, call function to save if success
        let img_src_response = reqwest::get(img_src).await;

        let img_src_response = match img_src_response {
            // Ok(response) => save_image(&img_src_response.unwrap()),
            Ok(response) => save_image(&response.bytes().await.unwrap(), 
                &img_containing_dir, &img_file_name),
            // Ok(response) => save_image(response, 
            //     &img_containing_dir, &img_file_name),
            Err(error) => println!("WARN: Problem getting image from url {}. \
                Error was: {}",
                img_src, error),
        };
    }
}

#[tokio::main]
pub async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // the starting place for our scraper
    // let news_homepage = "https://news.ycombinator.com/news";
    let news_homepage = "https://github.blog/2020-12-21-how-we-built-the-github-globe/";

    let news_homepage_response = reqwest::get(news_homepage)
        .await?;

    let news_homepage_html = Html::parse_document(&news_homepage_response.text().await?);

    let link_selector = Selector::parse("a[href]").unwrap();

    for link_element in news_homepage_html.select(&link_selector) {
        // follow each link
        let next_page = link_element.value().attr("href").unwrap();

        println!("INFO: Visiting link {:}", next_page);
        let next_page_response = reqwest::get(next_page).await;
        match next_page_response {
            Ok(response) => download_all_images_on_page(&response.text().await?).await,
            Err(error) => println!("WARN: Problem getting the url '{}'. \
                The error was {:?}", next_page, error),
        };

        // println!("WARN: Problem getting the url '{}'.", next_page);
        // println!("WARN: Problem getting the url '{}'. \
        //     The error was {:?}", next_page, error),

        /*
        let next_page_html = Html::parse_document(
            &next_page_response.text().await?);
        
        for img_element in next_page_html.select(&img_selector) {
            // download each image in that second-level link
            let img_link = img_element.value().attr("src").unwrap();
        }
        */
    }

    Ok(())
}
