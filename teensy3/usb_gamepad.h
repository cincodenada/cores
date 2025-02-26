/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows 
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef USBgamepad_h_
#define USBgamepad_h_

#ifdef GAMEPAD_INTERFACE

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
int usb_gamepad_send(uint8_t joynum);
extern uint16_t usb_gamepad_data[GAMEPAD_COUNT][4];
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_gamepad_class
{
        public:
        void begin(void) { }
        void end(void) { }
        void button(uint8_t button, bool val) {
                if (--button >= 14) return;
                if (val) usb_gamepad_data[joynum][0] |= (1 << button);
                else usb_gamepad_data[joynum][0] &= ~(1 << button);
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        void X(unsigned int val) {
                if (val > 1023) val = 1023;
                val >>= 2; // We only go to 255
                usb_gamepad_data[joynum][1] = (usb_gamepad_data[joynum][1] & 0x00FF) | (val << 8);
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        void Y(unsigned int val) {
                if (val > 1023) val = 1023;
                val >>= 2; // We only go to 255
                usb_gamepad_data[joynum][2] = (usb_gamepad_data[joynum][2] & 0xFF00) | val;
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        void Z(unsigned int val) {
                if (val > 1023) val = 1023;
                val >>= 2; // We only go to 255
                usb_gamepad_data[joynum][2] = (usb_gamepad_data[joynum][2] & 0x00FF) | (val << 8);
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        void Zrotate(unsigned int val) {
                if (val > 1023) val = 1023;
                val >>= 2; // We only go to 255
                usb_gamepad_data[joynum][3] = (usb_gamepad_data[joynum][2] & 0xFF00) | val;
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        inline void hat(int dir) {
                uint32_t val = 0;
                if (dir < 0) val = 15;
                else if (dir < 23) val = 0;
                else if (dir < 68) val = 1;
                else if (dir < 113) val = 2;
                else if (dir < 158) val = 3;
                else if (dir < 203) val = 4;
                else if (dir < 245) val = 5;
                else if (dir < 293) val = 6;
                else if (dir < 338) val = 7;
                usb_gamepad_data[joynum][1] = (usb_gamepad_data[joynum][1] & 0xFFF0) | val;
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        inline void axis(uint8_t axisnum, uint16_t val) {
                //uint8_t bytenum, bitoffset, lowshift;
                //uint8_t lowmask, highmask;
                if (val > 1023) val = 1023;

                switch(axisnum) {
                  case 1:
                        X(val); break;
                  case 2:
                        Y(val); break;
                  case 3:
                        Z(val); break;
                  case 4:
                        Zrotate(val); break;
                }

                /*
                 * Old fancy way - still needs updating
                 * with lowmask/highmask, I believe
                 * Worth it? Only if we want to support arbitrary # of axes,
                 * which I doubt HID does anyway
                 *
                //TODO: Precalculate these somewhere?
                //Axis values are 10 bits each, starting at the upper nibble of byte 4 (byte 4, bit 4)
                //(all above are zero-indexed)
                bitoffset = 4*8 + 4 + (axisnum * 10);
                dwordnum = bitoffset >> 1;

                lowshift = bitoffset % 8;

                lowmask = ~(0xFF << lowshift);
                highmask = (~lowmask) << 2;

                usb_gamepad_data[joynum][dwordnum] = (usb_gamepad_data[joynum][dwordnum] & lowmask) | (val << lowshift);
                usb_gamepad_data[joynum][dwordnum+1] = (usb_gamepad_data[joynum][dwordnum+1] & highmask) | (val >> (8 - lowshift));
                */
                if (!manual_mode) usb_gamepad_send(joynum);
        }
        void useManualSend(bool mode) {
                manual_mode = mode;
        }
        void setJoyNum(uint8_t num) {
                joynum = num;
        }
        uint8_t num_joys(void) {
                return GAMEPAD_COUNT;
        }
        void send_now(void) {
                usb_gamepad_send(joynum);
        }
        private:
        static uint8_t manual_mode;
        static uint8_t joynum;
};
extern usb_gamepad_class Gamepad;

#endif // __cplusplus

#endif // GAMEPAD_INTERFACE

#endif // USBgamepad_h_

