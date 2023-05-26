FROM ubuntu:22.04

# install build packages + some utilities for debugging
RUN : \
	&& apt-get update \
	&& apt-get install -y clang pkg-config cmake libssl-dev python3 file vim \
	&& apt-get clean \
	&& :

WORKDIR /code
ADD vendor/libgit2 vendor/libgit2

RUN mkdir vendor/libgit2/build
RUN cd vendor/libgit2/build && cmake .. && cmake --build . --target install

ADD . .
RUN make prog
