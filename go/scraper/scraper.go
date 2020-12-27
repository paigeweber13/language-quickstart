package main

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"

	"github.com/gocolly/colly/v2"
)

func main() {
	const DirMode = 0755
	const FileMode = 0644

	// max depth is 1, so we will only visit links on the scraped page
	c := colly.NewCollector(colly.MaxDepth(2))

	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
		e.Request.Visit(e.Attr("href"))
	})

	c.OnHTML("img[src]", func(e *colly.HTMLElement) {
		imgRequest, _ := e.Request.New(http.MethodGet, e.Attr("src"), nil)

		imgResponse, err := http.Get(imgRequest.URL.String())

		if imgResponse == nil {
			return
		}

		if err != nil {
			fmt.Println("ERR : couldn't get image at url", imgRequest.URL.String()+
				". Error was '"+err.Error()+"'.")
		}

		if imgResponse.StatusCode != http.StatusOK {
			fmt.Println("ERR : got code", imgResponse.StatusCode, "for url", imgRequest.URL.String())
			return
		}
		defer imgResponse.Body.Close()

		dir := "img/" + imgRequest.URL.Host
		err = os.MkdirAll(dir, os.ModeDir|DirMode)

		if err != nil {
			fmt.Println("ERR : couldn't create directories '" + dir +
				"'. Error was '" + err.Error() + "'")
			return
		}

		pathParts := strings.Split(imgRequest.URL.Path, "/")
		fileName := pathParts[len(pathParts)-1]
		fileFullPath := dir + "/" + fileName

		file, err := os.Create(fileFullPath)
		if err != nil {
			fmt.Println("ERR : couldn't create file '" + fileFullPath +
				"'. Error was '" + err.Error() + "'.")
			return
		}
		defer file.Close()

		fmt.Println("INFO: downloading image from URL:", imgRequest.URL.String())
		_, err = io.Copy(file, imgResponse.Body)
		if err != nil {
			fmt.Println("ERR : couldn't save image '" + fileFullPath +
				"'. Error was '" + err.Error() + "'.")
			return
		}

		fmt.Println("INFO: successfully saved image to:", fileFullPath)
	})

	c.OnRequest(func(r *colly.Request) {
		fmt.Println("INFO: Visiting", r.URL)
	})

	c.Visit("https://news.ycombinator.com/news")
}
