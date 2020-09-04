# Data Packer

This component runs on the Teensy microcontroller. It is responsible for
collecting data from all the different sensors and packaging it into a format
that can easily be sent to the Raspberry Pi. This component exists because it
is hard to do low-level, timing sensetive IO on the RPi's GPIO pins. Using a 
seperate microcontroller gives us much more control and ensures that the program
will run more predictably. (For example, the Teensy does nothing but run a
single program while the Raspberry Pi allows running many programs at once, each
being given sporatic windows of time to do their calculations.)

## Development notes

This program is intended to be used with the Arduino IDE. It also requires
"Teensyduino" to upload the code to a Teensy microcontroller. This program
is available at https://www.pjrc.com/teensy/td_download.html
