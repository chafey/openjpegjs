#!/bin/sh
#rm -rf build
mkdir -p build
#(cd build && emconfigure cmake -DCMAKE_BUILD_TYPE=Debug ..) &&
(cd build && emcmake cmake .. || true)
# run emcmake a second time to work around "TEST_BIG_ENDIAN found no result!" issue
(cd build && emcmake cmake ..)
(cd build && emmake make VERBOSE=1 -j ${nprocs}) &&
cp ./build/extern/openjpeg/bin/openjpegjs.js ./dist && 
cp ./build/extern/openjpeg/bin/openjpegjs.js.mem ./dist &&
cp ./build/extern/openjpeg/bin/openjpegwasm.js ./dist &&
cp ./build/extern/openjpeg/bin/openjpegwasm.wasm ./dist &&
(cd test/node; npm run test)
