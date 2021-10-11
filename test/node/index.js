// Copyright (c) Chris Hafey.
// SPDX-License-Identifier: MIT

let openjpegjs = require('../../dist/openjpegjs.js');
const codecHelper = require('./codec-helper.js')
const fs = require('fs')

function decodeFile(openjpeg, imageName, iterations = 1) {
  const encodedImagePath = '../fixtures/j2k/' + imageName + ".j2k"
  encodedBitStream = fs.readFileSync(encodedImagePath)
  const decoder = new openjpeg.J2KDecoder()
  const result = codecHelper.decode(decoder, encodedBitStream, iterations)
  console.log("Decode of " + imageName + " took " +  result.decodeTimeMS + " ms (" + iterations + " iterations)");
  decoder.delete();
  return result
}

function encodeFile(openjpeg, imageName, imageFrame, iterations = 1) {
  const pathToUncompressedImageFrame = '../fixtures/raw/' + imageName + ".RAW"
  const uncompressedImageFrame = fs.readFileSync(pathToUncompressedImageFrame);
  const encoder = new openjpeg.J2KEncoder();
  //encoder.setQuality(false, 0.001);
  const result = codecHelper.encode(encoder, uncompressedImageFrame, imageFrame, iterations)
  console.log("Encode of " + imageName + " took " +  result.encodeTimeMS + " ms (" + iterations + " iterations)");
  encoder.delete();
  return result
}

function main(openjpeg) {
  const iterations = 1
  encodeFile(openjpeg, 'CT1', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1, isSigned: true}, iterations)
  encodeFile(openjpeg, 'CT2', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1, isSigned: true}, iterations);
  encodeFile(openjpeg, 'MG1', {width: 3064, height: 4774, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'MR1', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1, isSigned: true}, iterations);
  encodeFile(openjpeg, 'MR2', {width: 1024, height: 1024, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'MR3', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1, isSigned: true}, iterations);
  encodeFile(openjpeg, 'MR4', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'NM1', {width: 256, height: 1024, bitsPerSample: 16, componentCount: 1, isSigned: true}, iterations);
  encodeFile(openjpeg, 'RG1', {width: 1841, height: 1955, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'RG2', {width: 1760, height: 2140, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'RG3', {width: 1760, height: 1760, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'SC1', {width: 2048, height: 2487, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  encodeFile(openjpeg, 'XA1', {width: 1024, height: 1024, bitsPerSample: 16, componentCount: 1, isSigned: false}, iterations);
  decodeFile(openjpeg, 'CT1', iterations)
  decodeFile(openjpeg, 'CT2', iterations)
  decodeFile(openjpeg, 'MG1', iterations)
  decodeFile(openjpeg, 'MR2', iterations)
  decodeFile(openjpeg, 'MR3', iterations)
  decodeFile(openjpeg, 'MR4', iterations)
  decodeFile(openjpeg, 'NM1', iterations)
  decodeFile(openjpeg, 'RG1', iterations)
  decodeFile(openjpeg, 'RG2', iterations)
  decodeFile(openjpeg, 'RG3', iterations)
  decodeFile(openjpeg, 'SC1', iterations)
  decodeFile(openjpeg, 'XA1', iterations)
}

if(openjpegjs) {
  console.log('testing openjpegjs...');
  openjpegjs().then(function(openjpeg) {
    main(openjpeg);
  });
}

