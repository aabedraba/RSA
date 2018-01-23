FROM ubuntu

LABEL maintainer="Abdallah Abedraba <aabedraba@gmail.com>"
LABEL description="github.com/aabedraba/RSA binary compiled and executed from Docker"

RUN apt-get update \
    && apt-get install -y \
    libgmp3-dev \
    cmake \
    build-essential \
    git
    
RUN git clone https://github.com/aabedraba/RSA

RUN cd RSA/build \
    && cmake .. \
    && make
    
WORKDIR /RSA/build/
CMD [ "./RSA" ]
