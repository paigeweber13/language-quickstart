package main

import (
  "fmt"
  // "io"
  "net/http"
  // "os"

  "github.com/gocolly/colly/v2"
)

func main() {
  // max depth is 1, so we will only visit links on the scraped page
  c := colly.NewCollector(colly.MaxDepth(2))


  c.OnHTML("a[href]", func(e *colly.HTMLElement) {
    e.Request.Visit(e.Attr("href"))
  })

  c.OnHTML("img[src]", func(e *colly.HTMLElement) {
    r, _ := e.Request.New(http.MethodGet, e.Attr("src"), nil)
    
    response, err := http.Get(r.URL.String())

    if (response != nil) {
      fmt.Println("INFO: got code", response.StatusCode, "for url", e.Attr("src"))
      
      if(response.StatusCode == http.StatusOK) {
        defer response.Body.Close()

        // file, err := os.Create("img/")

        fmt.Println("status OK!")
      }
    }

    if (err != nil) {
      fmt.Println("ERR:  couldn't get image at url", e.Attr("src"))
    }
  })



  c.OnRequest(func(r *colly.Request) {
    fmt.Println("Visiting", r.URL)
  })

  // c.Visit("https://news.ycombinator.com/news")
  c.Visit("https://github.com/davidhampgonsalves/life-dashboard")
}
