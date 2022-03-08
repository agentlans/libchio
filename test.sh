#!/usr/bin/sh

FILE=`mktemp`
./generate $FILE 1000

./check $FILE > /dev/null
if [[ $? -ne 0 ]]; then echo "Test failed."; fi

./damage $FILE
./check $FILE > /dev/null
if [[ $? -eq 0 ]]; then echo "Test failed."; else echo "Tests OK."; fi
