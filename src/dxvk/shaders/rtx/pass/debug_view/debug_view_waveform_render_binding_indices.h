/*
* Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/
#ifndef DEBUG_VIEW_WAVEFORM_RENDER_BINDINGS_H
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDINGS_H

#include "rtx/utility/shader_types.h"

// Bindings

// Inputs
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDING_HDR_WAVEFORM_RED_INPUT    0
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDING_HDR_WAVEFORM_GREEN_INPUT  1
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDING_HDR_WAVEFORM_BLUE_INPUT   2
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDING_CONSTANTS_INPUT           3

// Inputs/Outputs
#define DEBUG_VIEW_WAVEFORM_RENDER_BINDING_INPUT_OUTPUT       4

#define DEBUG_VIEW_WAVEFORM_RENDER_MAX_BINDING       (DEBUG_VIEW_WAVEFORM_RENDER_BINDING_INPUT_OUTPUT)
#define DEBUG_VIEW_WAVEFORM_RENDER_NUM_BINDINGS      (DEBUG_VIEW_MAX_BINDING + 1)

#endif
