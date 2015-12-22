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

#ifndef __UIF_FRAME_BUFFER_1BIT_H__
#define __UIF_FRAME_BUFFER_1BIT_H__

#include "uif-framebuffer/FrameBuffer.h"
#include "uif-tools-1bit/compositing.h"

#include <stdint.h>

namespace uif
{
    class FrameBuffer1Bit : public FrameBuffer
    {
    public:
        FrameBuffer1Bit();
        FrameBuffer1Bit(uint8_t* buffer, uint16_t width, uint16_t height, uint16_t strides);
        FrameBuffer1Bit(struct CompBuf buffer);

        virtual uint16_t getWidth(void) const;
        virtual uint16_t getHeight(void) const;
        virtual SharedPointer<FrameBuffer> getFrameBuffer(int16_t x, int16_t y, uint16_t width, uint16_t height);

        virtual bool drawImage(struct CompBuf image, int16_t xOffset, int16_t yOffset, bool inverse);
        virtual bool drawRectangle(int16_t x0, int16_t x1, int16_t y0, int16_t y1, bool inverse);
        virtual bool drawFunction(bool(*userFillFunction)(uint16_t, uint16_t), int16_t xOffset, int16_t yOffset, bool fill);

        virtual bool invertRectangle(int16_t x0, int16_t x1, int16_t y0, int16_t y1);
    private:
        struct CompBuf frame;
    };
}

#endif // __UIF_FRAME_BUFFER_1BIT_H__
