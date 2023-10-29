FROM nemuframework/alpine-nemu-cpp:0.12.0 as build

ENV CODESMITHYIDE=/codesmithyide

WORKDIR /codesmithyide/doxygen

COPY doxygen/include include
COPY doxygen/core core
RUN mkdir lib
RUN cd core/build/gnumake && make

WORKDIR /codesmithyide/content-platform

COPY content-platform/include include
COPY content-platform/core core
COPY content-platform/web-server web-server
RUN mkdir lib
RUN cd core/build/gnumake && make
RUN cd web-server/build/gnumake && make

WORKDIR /codesmithyide/content-platform-themes

COPY content-platform-themes .

FROM alpine:3.15.4

RUN apk add libgcc
RUN apk add libstdc++
RUN apk add boost1.77-filesystem

RUN addgroup --gid 1000 codesmithy-content-platform
RUN adduser --uid 1000 --ingroup codesmithy-content-platform --disabled-password codesmithy-content-platform

USER codesmithy-content-platform

COPY --from=build /codesmithyide/content-platform/web-server/build/gnumake/CodeSmithyContentPlatformWebServer /usr/local/bin/CodeSmithyContentPlatformWebServer
COPY --from=build /codesmithyide/content-platform-themes /codesmithyide/content-platform-themes

ENV CODESMITHYIDE=/codesmithyide 

ENTRYPOINT ["/usr/local/bin/CodeSmithyContentPlatformWebServer"]
