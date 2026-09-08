# Disposable OLED visual comparison; no firmware is built or flashed.
PROTOTYPE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: serve
serve:
	python3 -m http.server 8765 --bind 127.0.0.1 --directory "$(PROTOTYPE_DIR)"
