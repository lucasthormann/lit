# The beginning of a Turing complete programming language called lit 

# Dependencies:
* Docker

# Running The Code:
```
docker pull lucasthormann/lit:latest
docker run -it lucasthormann/lit
cd src
gcc -g main.c -o main
cat example.lit | ./main
```

* This step is only a demonstartion of the tokenizer/lexer.
