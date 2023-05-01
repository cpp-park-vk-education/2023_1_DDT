FROM ubuntu:20.04 AS base

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update -y
RUN apt install -y gcc
RUN apt install -y libpqxx-dev 
RUN apt install -y clang-tidy 
RUN apt install -y python3-pip 
RUN apt install -y cppcheck
RUN apt install -y cmake
RUN apt install -y git
RUN apt-get update -y
RUN apt install -y xvfb
RUN pip install gcovr
RUN pip install cpplint

RUN apt-get install wget
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
RUN tar xvf boost_1_82_0.tar.gz
WORKDIR boost_1_82_0
RUN ./bootstrap.sh --prefix=/usr/
RUN ./b2 install

RUN git clone https://github.com/google/googletest.git -b release-1.11.0
WORKDIR googletest/build
RUN cmake .. -DBUILD_GMOCK=OFF
RUN make
RUN make install

WORKDIR /project

COPY . .