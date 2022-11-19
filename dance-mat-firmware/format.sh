#!/bin/bash

find .| grep ".*\\.[c|h]\$" | xargs astyle --style=kr
cmake-format ./CMakeLists.txt > ./CMakeLists.txt.orig && cp ./CMakeLists.txt.orig ./CMakeLists.txt

