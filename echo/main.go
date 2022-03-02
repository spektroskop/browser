package main

import (
	"fmt"
	"net/http"

	"goji.io"
	"goji.io/pat"
)

func main() {
	mux := goji.NewMux()
	mux.HandleFunc(pat.Get("/:value"), func(w http.ResponseWriter, r *http.Request) {
		value := pat.Param(r, "value")
		fmt.Fprint(w, value)
	})

	http.ListenAndServe(":8080", mux)
}
