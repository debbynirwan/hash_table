#!/bin/bash

for (( i=10; i<=100000000; i*=2 ))
do
    ./build/example/hash_table_example $i
done
