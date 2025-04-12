FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++ make

COPY . /app
WORKDIR /app

RUN make

CMD ["./main"]
