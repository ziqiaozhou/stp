#!/bin/bash
set -e
set -x

rm -rf stp* tests tools lib bindings include
rm -rf cmake* CM* Makefile ./*.cmake
CXX=clang++ cmake -DENABLE_TESTING=ON -DSTATICCOMPILE=ON ..
make -j4
make -j4 check
