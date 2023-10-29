# Upload Instructions

```
docker build --no-cache .
docker tag <id> codesmithy/alpine-content-platform:latest
docker tag <id> codesmithy/alpine-content-platform:<version>
docker login
docker push codesmithy/alpine-content-platform:latest
docker push codesmithy/alpine-content-platform:<version>
```
