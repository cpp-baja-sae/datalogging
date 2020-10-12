# Data Collector


## Development Notes

This program is intended to be used with the Arduino IDE. It also requires
"Teensyduino" to upload the code to a Teensy microcontroller. This program
is available at https://www.pjrc.com/teensy/td_download.html

The `Serial` object, when using a Teensy, refers to the USB connection. The
Teensy has a few considerations for how it works to help squeeze as much
performance as possible out of it. For one, it doesn't matter what you set the
baud rate to, the Teensy will always increase it to the max transfer speed it
can. Experimentally, I have found this to be 34.5MiB/s, or 289.4Mbps. The USB
protocol can transfer up to 64 bytes in a single packet, so it's good to be
sending exactly 64 bytes at a time with `Serial.print()` for maximum
performance.

SD card write speed seems to stay above 300KiB/s most of the time if you write
in chunks of 512 bytes. Now and again it seems to dip to 45KiB/s and below which 
is concerning. I estimate with a 500Hz sample rate we will be writing at about
150KiB/s.

SD library limitations:
- Requires FAT16 or FAT32 formatted SD card
- Filenames are 8.3 format
- Filenames are case insensitive
- More at https://www.arduino.cc/en/reference/SD