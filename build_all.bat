@echo off

echo Building engine...
pushd engine
make release
popd

echo.

echo Building testbed...
pushd testbed
make release
popd
