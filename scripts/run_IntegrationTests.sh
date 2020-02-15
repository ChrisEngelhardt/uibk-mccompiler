#!/bin/bash

export OUTPUT_DIR=../tmp
export INTEGRATION_DIR=../test/integration
export MCC=../builddir/mcc

rm -r ../tmp

mkdir ../tmp

./integration_tests.sh

rm -r ../tmp
rm  ../scripts/*.o
rm  ../scripts/*.s
