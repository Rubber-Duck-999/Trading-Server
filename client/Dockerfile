FROM ubuntu:24.04 AS builder

WORKDIR /app
# Update packages and install, will only happen on first build
RUN apt-get update && apt-get install -y libboost-all-dev \
cmake \
g++
# Copy all files in folder and lower dirs
COPY ./core ./core
COPY ./client ./
# Folder for CMAKE for executable creation
RUN mkdir build
RUN cd build && cmake .. && make
# What to call in order to run the exe
CMD [ "./build/client" ]
