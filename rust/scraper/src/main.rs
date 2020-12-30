use scraper::{Html, Selector};

pub async fn download_all_images_on_page(page_html: &str) {
    println!("INFO: in download_image");

    let img_selector = Selector::parse("img[src]").unwrap();
    // let this_page_url = &response.url().as_str();

    let page_html = Html::parse_document(&page_html);

    for img_element in page_html.select(&img_selector) {
        let img_src = img_element.value().attr("src").unwrap();
    }
}

#[tokio::main]
pub async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // the starting place for our scraper
    let news_homepage = "https://news.ycombinator.com/news";

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
