#!/bin/sh

@echo off

echo Building engine...
pushd engine
make debug
popd

echo.

echo Building testbed...
pushd testbed
make debug
popd
