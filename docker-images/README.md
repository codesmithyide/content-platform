# Upload Instructions

Copy the contents of codesmithyide/doxygen into doxygen/include and doxygen/core
Copy the contents of codesmithyide/content-platform-themes into content-platform-themes
Copy the contents of codesmithyide/content-platform into content-platform/include, core and web-server

```
docker build --no-cache .
docker tag <id> ghcr.io/codesmithyide/alpine-content-platform:latest
docker tag <id> ghcr.io/codesmithyide/alpine-content-platform:<version>
docker login ghcr.io
docker push ghcr.io/codesmithyide/alpine-content-platform:latest
docker push ghcr.io/codesmithyide/alpine-content-platform:<version>
```
