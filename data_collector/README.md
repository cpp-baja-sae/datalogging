# Data Collector

## Commands that can be sent over USB:

### 0F SS 

Read the file at slot SS, index F. The different slots are used to hold
different datalogs, and the F index is used to differentiate between different
LODs. (index 15 is used to hold the json description of the datalog.) The Teensy
first sends 8 bytes containing the size of the file, followed by relentlessly
streaming the entire content of the file.

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

By writing to the SD card in chunks of 512 bytes and calling .flush() manually
every 1MiB we can reach write speeds of 15MiB/s. Reading in 512 byte chunks
gives us a very steady read rate of 21.6MiB/s. Unfortunately, to accomplish
this, you have to install this library: https://github.com/greiman/SdFat-beta as
the default Arduino SD library is not capable of producing these speeds on the
Teensy 4.1.
https://forum.pjrc.com/threads/61289-Question-on-the-correct-usage-of-the-SD-Card-on-Teensy-4-1
The SD card should be formatted as ExFAT so that it can store files over 2GB in
size.

