@echo off
cd C:\Users\yaniv\Private\Projects\net-flip
echo Building Docker image...
docker build -t package-test -f dockers/package-test .
IF %ERRORLEVEL% NEQ 0 (
    echo Docker build failed. Exiting.
    exit /b %ERRORLEVEL%
)

echo Docker build succeeded. Running container...
docker run --rm -it package-test