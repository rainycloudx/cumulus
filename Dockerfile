FROM ubuntu

WORKDIR /opt/cumulus

RUN apt update
RUN apt install -y g++ cmake libssl-dev

RUN apt install -y git python3 python3.10-venv libsecret-1-dev

COPY code.tar.gz .

RUN git clone https://github.com/firebase/firebase-cpp-sdk.git && \
    cd firebase-cpp-sdk && \
    cmake . && \
    cmake --build .

RUN tar xvzf code.tar.gz && \
    cd cumulus && \
    cmake . -DOPENSSL_ROOT_DIR=/usr/include/openssl && \
    cmake --build .

CMD ["echo", "Hello World"]





