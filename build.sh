#!/bin/bash

function Usage
{
    echo "Usage: ./build.sh fileDirname fileNameBase"
}

if [[ $# -lt 1 ]]; then
    Usage
    exit 1
fi

fileDirname=$1;
fileNameBase=$2;

if [[ ! -d "${fileDirname}/build.out" ]]; then
    mkdir "${fileDirname}/build.out"
fi

if [[ -d "${fileDirname}/build.out/${fileNameBase}.dSYM" ]]; then
    rm -r "${fileDirname}/build.out/${fileNameBase}.dSYM"
fi

if [[ -f "${fileDirname}/${fileNameBase}" ]]; then
    mv -f "${fileDirname}/${fileNameBase}" "${fileDirname}/build.out/"
fi

if [[ -d "${fileDirname}/${fileNameBase}.dSYM" ]]; then
    mv "${fileDirname}/${fileNameBase}.dSYM" "${fileDirname}/build.out/"
fi