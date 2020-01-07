#!/bin/bash
rm *.o  *.so test

gcc -c -Wall -I/usr/bin/python3.7 $(/usr/bin/python3.7-config --cflags) $(/usr/bin/python3.7-config --ldflags) -fPIC pyfun.c -o pyfun.o -g
echo "done building from c function"

gcc -I/usr/bin/python3.7 $(/usr/bin/python3.7-config --cflags) $(/usr/bin/python3.7-config --ldflags) -shared  -o libpyfun.so pyfun.o
echo "done creating shared object"

gcc -L$(pwd) -Wl,-rpath=$(pwd) -o test main.c -lpyfun $(/usr/bin/python3.7-config --ldflags)
echo "creating main executable"

