#!/bin/bash

rm *.out &>/dev/null
g++ game.cpp class.cpp -o game.out -lraylib
./game.out &>/dev/null
rm *.out &>/dev/null
