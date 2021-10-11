docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v "$(pwd)":/openjpegjs -w /openjpegjs \
  openjpegjsbuild bash -login