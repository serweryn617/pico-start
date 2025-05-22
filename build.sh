#!/bin/sh

mkdir -p build/generated/pio

docker run --rm \
    -u $(id -u):$(id -g) \
    -v $(pwd)/firmware:/workspace/firmware \
    -v $(pwd)/build:/workspace/build \
    -w /workspace/build \
    pico_builder \
    /bin/bash -c "cmake ../firmware -GNinja && ninja"

mkdir -p output
cp build/main/pi2c.uf2 output/pi2c.uf2

cd build
sed -i "s#/workspace#$(pwd)#g" compile_commands.json

# Interactive Docker container
# docker run --rm -it -u $(id -u):$(id -g) -v $(pwd)/firmware:/workspace/firmware -v $(pwd)/sdk:/workspace/sdk -v $(pwd)/build:/workspace/build -w /workspace/build pico_builder /bin/bash
