# This dockerfile is to compile ton sources only (not for starting node)

FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
	  build-essential \
	  cmake \
	  clang-6.0 \
	  openssl \
	  libssl-dev \
	  zlib1g-dev \
	  gperf \
	  git

ENV CC clang-6.0
ENV CXX clang++-6.0

ARG COMMIT=606e970ed5feb2430d9e043ff8016280c662178c

RUN git clone --recurse-submodules -j8 https://github.com/copperexchange/ton.git ton/ton-node

RUN cd /ton/ton-node \
    && git checkout ${COMMIT} \
    && git submodule update --recursive

WORKDIR /ton

RUN mkdir build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release ../ton-node \
    && cmake --build . --target tonlibjson
#    && cmake --build . --target fiftlib \
#    && cmake --build . --target mnemoniclib
