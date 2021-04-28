#!/bin/bash

echo ""
echo "Checking file input.txt"
expected="$(sha512sum input.txt)"
actual="$(./sha512 input.txt)  input.txt"
echo "Expected:" $expected
echo "Actual:  " $actual
if [[ $actual == $expected ]]; then 
    echo "Pass"
else
    echo "Fail"
fi

echo ""
echo "Checking file empty.txt"
expected="$(sha512sum empty.txt)"
actual="$(./sha512 empty.txt)  empty.txt"
echo "Expected:" $expected
echo "Actual:  " $actual
if [[ $actual == $expected ]]; then 
    echo "Pass"
else
    echo "Fail"
fi