// Copyright (c) Chris Hafey.
// SPDX-License-Identifier: MIT

#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <time.h> 
#include <algorithm>

#include "../../src/J2KDecoder.hpp"
#include "../../src/J2KEncoder.hpp"

void readFile(std::string fileName, std::vector<uint8_t>& vec) {
    // open the file:
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
                std::istream_iterator<uint8_t>(file),
                std::istream_iterator<uint8_t>());

    //std::istreambuf_iterator iter(file);
    //std::copy(iter.begin(), iter.end(), std::back_inserter(vec));
}

void writeFile(std::string fileName, const std::vector<uint8_t>& vec) {
    std::ofstream file(fileName, std::ios::out | std::ofstream::binary);
    std::copy(vec.begin(), vec.end(), std::ostreambuf_iterator<char>(file));
}

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

void decodeFile(const char* imageName, size_t iterations = 1) {
    std::string inPath = "test/fixtures/j2k/";
    inPath += imageName;
    inPath += ".j2k";
    
    J2KDecoder decoder;
    std::vector<uint8_t>& encodedBytes = decoder.getEncodedBytes();
    readFile(inPath, encodedBytes);

    // cut buffer in half to test partial decoding
    //const size_t numBytes = 25050;
    //const size_t numBytes = 0;
    //encodedBytes.resize(encodedBytes.size() - numBytes);

    timespec start, finish, delta;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(int i=0; i < iterations; i++) {
        decoder.readHeader();
        //Size resolutionAtLevel = decoder.calculateDecompositionLevel(1);
        //std::cout << resolutionAtLevel.width << ',' << resolutionAtLevel.height << std::endl;
        //decoder.decodeSubResolution(0, 0);//1, 1);
        decoder.decode();
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finish);
    sub_timespec(start, finish, &delta);
    const double ns = delta.tv_sec * 1000000000.0 + delta.tv_nsec;
    printf("Native-decode %s %f\n", imageName, ns/1000000.0);
}

void encodeFile(const char* imageName, const FrameInfo frameInfo, size_t iterations = 1) {
    std::string inPath = "test/fixtures/raw/";
    inPath += imageName;
    inPath += ".RAW";

    J2KEncoder encoder;
    std::vector<uint8_t>& rawBytes = encoder.getDecodedBytes(frameInfo);
    readFile(inPath, rawBytes);

    timespec start, finish, delta;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    encoder.encode();

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finish);
    sub_timespec(start, finish, &delta);
    const double ns = delta.tv_sec * 1000000000.0 + delta.tv_nsec;
    printf("Native-encode %s %f\n", imageName, ns/1000000.0);

    /*if(outPath) {
        const std::vector<uint8_t>& encodedBytes = encoder.getEncodedBytes();
        writeFile(outPath, encodedBytes);
    }*/
}

int main(int argc, char** argv) {
  const size_t iterations = (argc > 1) ? atoi(argv[1]) : 1;
  encodeFile("CT1", {.width = 512, .height = 512, .bitsPerSample = 16, .componentCount = 1, .isSigned = true}, iterations);
  encodeFile("CT2", {.width = 512, .height = 512, .bitsPerSample = 16, .componentCount = 1, .isSigned = true}, iterations);
  encodeFile("MG1", {.width = 3064, .height = 4774, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("MR1", {.width = 512, .height = 512, .bitsPerSample =  16, .componentCount = 1, .isSigned = true}, iterations);
  encodeFile("MR2", {.width = 1024, .height = 1024, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("MR3", {.width = 512, .height = 512, .bitsPerSample = 16, .componentCount = 1, .isSigned = true}, iterations);
  encodeFile("MR4", {.width = 512, .height = 512, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("NM1", {.width = 256, .height = 1024, .bitsPerSample = 16, .componentCount = 1, .isSigned = true}, iterations);
  encodeFile("RG1", {.width = 1841, .height = 1955, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("RG2", {.width = 1760, .height = 2140, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("RG3", {.width = 1760, .height = 1760, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("SC1", {.width = 2048, .height = 2487, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  encodeFile("XA1", {.width = 1024, .height = 1024, .bitsPerSample = 16, .componentCount = 1, .isSigned = false}, iterations);
  decodeFile("CT1", iterations);
  decodeFile("CT2", iterations);
  decodeFile("MG1", iterations);
  decodeFile("MR1", iterations);
  decodeFile("MR2", iterations);
  decodeFile("MR3", iterations);
  decodeFile("MR4", iterations);
  decodeFile("NM1", iterations);
  decodeFile("RG1", iterations);
  decodeFile("RG2", iterations);
  decodeFile("RG3", iterations);
  decodeFile("SC1", iterations);
  decodeFile("XA1", iterations);

  return 0;
}
