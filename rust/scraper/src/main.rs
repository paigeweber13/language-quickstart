use scraper::{Html, Selector};

#[tokio::main]
pub async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // the starting place for our scraper
    let news_homepage = "https://news.ycombinator.com/news";

    let response = reqwest::get(news_homepage)
        .await?;

    let news_homepage_html = Html::parse_document(&response.text().await?);

    let link_selector = Selector::parse("a[href]").unwrap();
    let img_selector = Selector::parse("img[src]").unwrap();

    for link_element in news_homepage_html.select(&link_selector) {
        // follow each link
        let next_page = link_element.value().attr("href").unwrap();

        println!("INFO: Visiting link {:}", next_page);
        let next_page_response = reqwest::get(next_page).await?;

        let next_page_html = Html::parse_document(
            &next_page_response.text().await?);
        
        for img_element in next_page_html.select(&img_selector) {
            // download each image in that second-level link
            let img_link = img_element.value().attr("src").unwrap();
        }
    }

    Ok(())
}
