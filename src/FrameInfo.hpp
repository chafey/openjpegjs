// Copyright (c) Chris Hafey.
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>

struct FrameInfo {
    FrameInfo() : width(0), height(0), bitsPerSample(0), componentCount(0), isSigned(false) {}
    FrameInfo(uint16_t w, uint16_t h, uint8_t bps, uint8_t cc, bool isSgn) :
        width(w), height(h), bitsPerSample(bps), componentCount(cc), isSigned(isSgn) {}

    /// <summary>
    /// Width of the image, range [1, 65535].
    /// </summary>
    uint16_t width;

    /// <summary>
    /// Height of the image, range [1, 65535].
    /// </summary>
    uint16_t height;

    /// <summary>
    /// Number of bits per sample, range [2, 16]
    /// </summary>
    uint8_t bitsPerSample;

    /// <summary>
    /// Number of components contained in the frame, range [1, 255]
    /// </summary>
    uint8_t componentCount;

    /// <summary>
    /// true if signed, false if unsigned
    /// </summary>
    bool isSigned;
};