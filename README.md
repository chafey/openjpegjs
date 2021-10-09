# openjpegpjs

JS/WebAssembly build of [OpenJPEG](https://github.com/uclouvain/openjpeg)

NOTE - a forked version of OpenJPEG is currently used which has some changes to allow partial bitstream decoding

## Try It Out!

Try it in your browser [here](https://chafey.github.io/openjpegjs/test/browser/index.html)

## Initialize git submodules

This project depends on the charls library and references it using
git submodules.  You must initialize it before building:

> git submodule update --init --recursive

## TODOS

1) Fix openjpeg cmake issue that overrides output directory to be wrong