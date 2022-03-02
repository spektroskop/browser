.ONESHELL:
.PHONY: browser controller echo

default:

browser: browser/Makefile
	$(MAKE) -C browser

browser/Makefile:
	cd browser
	qmake

controller:
	cd controller
	mix run --no-halt

echo:
	cd echo
	go run .
