FROM ubuntu:22.04 as builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    make

COPY . /app
WORKDIR /app
RUN make

FROM ubuntu:22.04

COPY --from=builder /app/main /app/main

WORKDIR /app
CMD ["./main"]