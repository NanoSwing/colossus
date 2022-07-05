#!/bin/sh

echo -e "\033[1;32mBuilding engine...\033[0m"
pushd engine
make $1
popd

echo ""

echo -e "\033[1;32mBuilding testbed...\033[0m"
pushd testbed
make $1
popd
