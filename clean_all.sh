#!/bin/sh

echo "Cleaning engine..."
pushd engine
make clean
popd

echo ""

echo "Cleaning testbed..."
pushd testbed
make clean
popd
