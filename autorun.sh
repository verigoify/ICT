#!/bin/bash

<<<<<<< HEAD
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

=======

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
>>>>>>> 2b94839796891daa5c6525f4e9e80a37967f6db5
