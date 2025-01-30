#!/bin/bash

rm *.out &>/dev/null
g++ game.cpp class.cpp function.cpp -o game.out -lraylib
./game.out
rm *.out &>/dev/null
