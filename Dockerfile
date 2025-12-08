FROM ubuntu:latest
WORKDIR /root

#install basic utilities
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y file grep make tar unzip tree vim wget gcc

#Download fasm
RUN wget https://flatassembler.net/fasm-1.73.32.tgz
RUN tar -xvzf *.tgz
RUN rm *.tgz
RUN cp fasm/fasm.x64 /usr/local/bin/fasm

#Basic vim setup
RUN echo 'set rnu' > .vimrc

COPY ds.h example.lit main.c ./src/

CMD [ "bash" ] 
