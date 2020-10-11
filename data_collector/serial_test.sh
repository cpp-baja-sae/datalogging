#!/bin/sh

# A Linux script to communicate with the Teensy to test its throughput without
# the limitations of the Arduino serial monitor.
# From a 3-minute test run on my pc, it appears the max transfer rate is 
# 34.5MiB/s, or 289.4Mbps
# https://playground.arduino.cc/Interfacing/LinuxTTY/
# We set the baud rate as "9600" but unlike the actual Arduino, the Teensy is 
# capable of transmitting at full USB speeds no matter what, the 9600 is more of
# a suggestion that we can use in our code. Likewise, we don't have to worry
# about what the actual baud rate of USB is, the Teensy will select it 
# automatically and it appears we don't have to do any configuration on the 
# Linux end either.
stty \
    -F /dev/ttyACM0 \
    cs8 9600 \
    ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo \
    -echoe -echok -echoctl -echoke noflsh -ixon -crtscts 
# pv is a utility that measures how fast data flows through a pipe. It can be 
# installed with `sudo apt install pv`.
cat /dev/ttyACM0 | pv -c > /dev/null
