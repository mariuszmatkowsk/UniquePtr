#! /usr/bin/env bash

[ ! -d build ] && mkdir -p build 

cd build && cmake .. && make
