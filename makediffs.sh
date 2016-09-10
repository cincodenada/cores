#!/bin/bash
git diff 659dcbc1e19e77 HEAD | awk '/^diff --git/ { keep = 1 } /^diff --git.*multijoy/ { keep = 0 } { if(keep) print }' > diff_t3
diff -u -w teensy3/usb_joystick.c teensy3/usb_multijoy.c >> diff_t3
diff -u -w teensy3/usb_joystick.h teensy3/usb_multijoy.h >> diff_t3
diff -u -w usb_serial_hid usb_serial_hid_joy > diff_t2
