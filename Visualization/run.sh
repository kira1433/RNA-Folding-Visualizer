#!/bin/bash

# Compile main.cpp to WebAssembly and generate output.js
emcc main.cpp -s WASM=1 -o output.js \
  -s "EXPORTED_RUNTIME_METHODS=['cwrap','UTF8ToString','lengthBytesUTF8']" \
  -s "EXPORTED_FUNCTIONS=['_free', '_malloc','_rna_folding_c']" &&