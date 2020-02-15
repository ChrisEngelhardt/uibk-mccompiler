#!/bin/bash

if [ -z "$1" ]; then
  echo "Please proved path to .dot file \n ./convertDotToPNG.sh pathToFile"
  exit 1
fi

dotPath=$1
dot -T png -O $dotPath

open "${dotPath%.*}.dot.png"
