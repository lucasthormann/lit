# lit
* The beginning of a Turing complete programming language I've dubbed lit.

## Development Environment:
* Lenovo T14 Gen 6 (x86_64)
* Ubuntu (24.04.3)
* GNOME Terminal (3.52.0)
* Vi IMproved (9.1)

## Dependencies:
* Git (2.43.0 or newer)
* Docker (28.2.2 or newer)
* GNU Make (4.3 or newer)

## Target Environment:
* A modern PC (x86_64) running an Ubuntu (24.04.3) instance

## Container Image:
* https://hub.docker.com/r/lucasthormann/lit

# How to Build and Run the compiler:

1. Clone the repo
```
git clone https://github.com/lucasthormann/lit.git
```

2. Build the container image:
```
make build
```

3. Run the image inside of a container:
```
make run
```

4. Change to source directory:
```
cd src
```

5. Build (i.e., preprocess, compile, assemble, and link) the compiler:
```
gcc -g main.c -o main
```

6. Run the scanner:
```
cat example.lit | ./main
```

* This is only a demonstration of the tokenizer/scanner because I've yet to implement the rest of the functionality.
