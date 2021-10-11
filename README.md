# openjpegpjs

JS/WebAssembly build of [OpenJPEG](https://github.com/uclouvain/openjpeg)

NOTE - a forked version of OpenJPEG is currently used which has some changes to allow partial bitstream decoding

## Try It Out!

Try it in your browser [here](https://chafey.github.io/openjpegjs/test/browser/index.html)

## Building

This project uses git submodules to pull in OpenJPEG.  If developing, initialize the git submodules first:

```
> git submodule update --init --recursive
```

This project uses Docker to provide a consistent developer environment.

Create docker container 'openjpegjsbuild'

```
> scripts/docker-build.sh
```

Create shell inside openjpegjsbuild container:

```
> scripts/docker-sh.sh
```

Install node 16 (inside docker shell):
```
> nvm install 16
```

To build WASM (inside docker shell):
```
> scripts/wasm-build.sh
```

To build native C/C++ version (inside docker shell):
```
> scripts/native-build.sh
```

## TODOS

1) Fix openjpeg cmake issue that overrides output directory to be wrong