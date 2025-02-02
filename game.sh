#!/bin/bash

rm *.out &>/dev/null
rm *.o &>/dev/null

nasm R.s -felf64 -o R.o &>/dev/null

g++ game.cpp class.cpp function.cpp  R.o -o game.out -lraylib -no-pie &>/dev/null

echo "Let's play PONG!"

./game.out &>/dev/null

echo ":("

rm *.o &>/dev/null
rm *.out &>/dev/null

sleep 2

clear