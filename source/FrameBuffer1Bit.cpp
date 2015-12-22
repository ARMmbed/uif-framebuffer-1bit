/* mbed
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "uif-framebuffer-1bit/FrameBuffer1Bit.h"

namespace uif {
    FrameBuffer1Bit::FrameBuffer1Bit(void)
        :   FrameBuffer(FrameBuffer::Type1Bit)
    {
        frame.buf            = 0;
        frame.mask           = (uint8_t*)Comp_Fill_Ones;
        frame.bit_offset     = 0;
        frame.stride_bytes   = 0;
        frame.width_bits     = 0;
        frame.height_strides = 0;
    }

    FrameBuffer1Bit::FrameBuffer1Bit(uint8_t* buffer,
                                     uint16_t width,
                                     uint16_t height,
                                     uint16_t stride)
        :   FrameBuffer(FrameBuffer::Type1Bit)
    {
        frame.buf            = buffer;
        frame.mask           = (uint8_t*)Comp_Fill_Ones;
        frame.bit_offset     = 0;
        frame.stride_bytes   = stride;
        frame.width_bits     = width;
        frame.height_strides = height;
    }

    FrameBuffer1Bit::FrameBuffer1Bit(struct CompBuf buffer)
        :   FrameBuffer(),
            frame(buffer)
    { }

    uint16_t FrameBuffer1Bit::getWidth(void) const
    {
        return frame.width_bits;
    }

    uint16_t FrameBuffer1Bit::getHeight(void) const
    {
        return frame.height_strides;
    }

    bool FrameBuffer1Bit::drawImage(struct CompBuf image, int16_t xOffset, int16_t yOffset, bool inverse)
    {
        compBlitAt(frame, image, xOffset, yOffset, inverse);

        return true;
    }

    bool FrameBuffer1Bit::drawRectangle(int16_t x0, int16_t x1, int16_t y0, int16_t y1, bool inverse)
    {
        compFillRect(frame, x0, x1, y0, y1, inverse);

        return true;
    }

    bool FrameBuffer1Bit::drawFunction(bool(*userFillFunction)(uint16_t, uint16_t), int16_t xOffset, int16_t yOffset, bool fill)
    {
        compFillFun(frame, userFillFunction, xOffset, yOffset, fill);

        return true;
    }

    bool FrameBuffer1Bit::invertRectangle(int16_t x0, int16_t x1, int16_t y0, int16_t y1)
    {
        compInvertRect(frame, x0, x1, y0, y1);

        return true;
    }

    SharedPointer<FrameBuffer> FrameBuffer1Bit::getFrameBuffer(int16_t x, int16_t y, uint16_t width, uint16_t height)
    {
        struct CompBuf subframe = compBufAtPxOffsetWithSize(x, y, width, height, frame);

        return SharedPointer<FrameBuffer>(new FrameBuffer1Bit(subframe));
    }
}
