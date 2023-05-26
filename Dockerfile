FROM ubuntu:22.04

# build deps: install separately from utilities to optimize caching
RUN : \
	&& apt-get update \
	&& apt-get install -y clang pkg-config cmake libssl-dev python3 \
	&& :

WORKDIR /code
ADD vendor/libgit2 vendor/libgit2

RUN mkdir vendor/libgit2/build
RUN cd vendor/libgit2/build && cmake .. && cmake --build . --target install

# utilities
RUN apt-get install -y file git vim

RUN git config --global --add safe.directory /repo

ADD . .
RUN make prog
