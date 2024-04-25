// Wait for the WebAssembly module to be ready
const loadPromise = new Promise((resolve, reject) => {
    Module.onRuntimeInitialized = () => {
      resolve(Module);
    };
  });

function submitSequence() {
  loadPromise
  .then(wasmModule => {
    // Call the exported function
    const inputString = document.getElementById('rnaInput').value;
    const inputBufferSize = lengthBytesUTF8(inputString) + 1;
    const inputBuffer = wasmModule._malloc(inputBufferSize);
    stringToUTF8(inputString, inputBuffer, inputBufferSize);

    const outputBuffer = wasmModule._rna_folding_c(inputBuffer);
    const outputString = UTF8ToString(outputBuffer);

    wasmModule._free(inputBuffer);
    wasmModule._free(outputBuffer);

    document.getElementById('dotBracketOutput').value = outputString;            
    draw(inputString, outputString);  
    
  })
  .catch(err => console.error('Failed to load WebAssembly module:', err));

}
