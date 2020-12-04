#!/bin/bash

function Usage
{
    echo "Usage: ./build.sh fileNameBase workSpaceDir"
}

if [[ $# -lt 1 ]]; then
    Usage
    exit 1
fi

fileNameBase=$1;
workSpaceDir=$2;

if [[ ! -d "${workSpaceDir}/C/build.out" ]]; then
    mkdir "${workSpaceDir}/C/build.out"
fi

if [[ -d "${workSpaceDir}/C/build.out/${fileNameBase}.dSYM" ]]; then
    rm -r "${workSpaceDir}/C/build.out/${fileNameBase}.dSYM"
fi

if [[ -f "${workSpaceDir}/C/${fileNameBase}" ]]; then
    mv -f "${workSpaceDir}/C/${fileNameBase}" "${workSpaceDir}/C/build.out/"
fi

if [[ -d "${workSpaceDir}/C/${fileNameBase}.dSYM" ]]; then
    mv "${workSpaceDir}/C/${fileNameBase}.dSYM" "${workSpaceDir}/C/build.out/"
fi