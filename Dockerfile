FROM ubuntu
MAINTAINER Abdallah Abedbraba <aabedraba@gmail.com>

LABEL description="C++ Build Enviroment for project aabedraba/RSA"

RUN apt-get update && apt-get install -y \
  build-essential \
  libgmp3-dev \
  cmake

CMD ["/bin/bash"]
