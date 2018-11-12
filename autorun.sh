#!/bin/bash


    txt=$1
    img=$2
    c='com.txt'
    txtc="$txt$c"
    execute_dct="python3.6 compress.py $txt"
    execute="./encode $img $txtc tgt_img.png"

    eval "$execute_dct"
    
    eval "$execute"

    img2="tgt_img.png"
    txt2="decodeOutput.txt"
    execute2="./decode $img2"
    execute_dct2="python3.6 decompress.py $txt2"

    eval "$execute2"
    eval "$execute_dct2"
