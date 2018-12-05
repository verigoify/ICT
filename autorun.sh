#!/bin/bash

txt=$1
img=$2
img2='tgtImg.png'
c='com.txt'
txtc="$txt$c"
execute_dct="python3.6 compress.py $txt"
execute="./encode $img $txtc $img2"

eval "$execute_dct"
eval "$execute"

execute2="./decode $img2"
execute_dct2="python3.6 decompress.py decodeOutput.txt"

eval "$execute"
eval "$execute_dct2"

