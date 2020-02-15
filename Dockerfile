FROM ubuntu:18.04

RUN apt-get update && apt-get install meson build-essential flex bison valgrind cmake git gcc-multilib time pkg-config gcovr lcov doxygen -y

WORKDIR /app/src/
CMD [ "/bin/bash" ]
