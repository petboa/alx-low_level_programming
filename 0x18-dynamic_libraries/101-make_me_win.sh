#!/bin/bash
h
wget -P /tmp/ https://raw.github.com/frame-1/alx-low_level_programming/master/0x18-dynamic_libraries/nrandom.so
export LD_PRELOAD=/tmp/nrandom.so
