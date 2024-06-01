#!/bin/sh

clear

# Compile and run the tests using the Makefile
make -f testes.mak run-bitmap
make -f testes.mak run-fat
make -f testes.mak clean