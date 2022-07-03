@echo off

echo Building engine...
pushd engine
make clear
popd

echo.

echo Building testbed...
pushd testbed
make clear
popd
