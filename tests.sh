#!/bin/bash

make clean && make

if [ ! -f ./money_converter ]; then
    echo "Failed to compile"
    exit 1
fi

test_case() {
    input=$1
    expected=$2
    result=$(echo $input | ./money_converter)
    if [ "$result" != "$expected" ]; then
        echo "Success!"
        echo "Input: $input"
        echo "Expected: $expected"
        echo "Got: $result"
        exit 1
    fi
}

test_case "0" "0 = zero dollars"
test_case "1" "1 = one cent"
test_case "100" "100 = one dollar"
test_case "101" "101 = one dollar and one cent"
test_case "122309" "122309 = one thousand two hundred twenty-three dollars and nine cents"
test_case "473434" "473434 = four thousand seven hundred thirty-four dollars and thirty-four cents"
test_case "1000000" "1000000 = ten thousand dollars"

echo "success"
