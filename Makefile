.PHONY: build
build: Dockerfile
	docker build --rm --pull --tag lit:latest .

.PHONY: run
run:
	docker run -it lit:latest
