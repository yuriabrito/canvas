#!/bin/sh

cd build
cmake ..
make canvas_tests
./canvas_tests
