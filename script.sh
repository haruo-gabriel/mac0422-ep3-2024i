#!/bin/sh

clear

case "$1" in
  release)
    # Commands for release mode
    echo "Building in release mode..."
    make -f release.mak MODE=release
    make -f release.mak run
    ;;
  debug)
    # Commands for debug modek
    echo "Building in debug mode..."
    make -f release.mak MODE=debug
    gdb -x script.gdb ./ep3
    ;;
  testes)
    # Compile and run the tests using the Makefile
    echo "Running tests..."
    make -f testes.mak run-bitmap
    make -f testes.mak run-fat
    make -f testes.mak clean
    ;;
  *)
    echo "Usage: $0 {release|debug|testes}"
    exit 1
    ;;
esac