#!/usr/bin/env python3
# Install python3 HID package https://pypi.org/project/hid/
import hid
import time

# default is TinyUSB (0xcafe), Adafruit (0x239a), RaspberryPi (0x2e8a), Espressif (0x303a) VID
USB_VID = (0xcafe,)

print("VID list: " + ", ".join('%02x' % v for v in USB_VID))

for vid in USB_VID:
    print("Checking", hex(vid))
    print(hid.enumerate(vid))
    for d in hid.enumerate(vid):
        print(d)
        dev = hid.Device(d['vendor_id'], d['product_id'])
        str_out = b'\x00'
        str_out += "this is a longer message".encode('utf-8')
        print("Writing...")
        if dev:
            while True:
                # Get input from console and encode to UTF8 for array of chars.
                # hid generic in/out is single report therefore by HIDAPI requirement
                # it must be preceded, with 0x00 as dummy reportID
                dev.write(str_out)
                dev.write(str_out)
                # dev.write(str_out)
                time.sleep(0.100)
                # print("Reading...")
                # str_in = dev.read(16)
                # print("Received from HID Device:", str_in, '\n')
                # break
