#!/usr/bin/bash

[ -d "build" ] && rm -r build
mkdir build
gcc main.c -o build/main.out
build/main.out $1
