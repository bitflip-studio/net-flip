@echo off
cd C:\Users\yaniv\Private\Projects\net-flip
echo Building Docker image...
docker build -t core-test --progress=plain -f dockers/core-lib-js-test .
IF %ERRORLEVEL% NEQ 0 (
    echo Docker build failed. Exiting.
    exit /b %ERRORLEVEL%
)

echo Docker build succeeded. Running container...
docker run --rm core-test