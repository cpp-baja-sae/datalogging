#!/bin/sh

# Based on serial_test.sh

stty \
    -F /dev/ttyACM0 \
    cs8 9600 \
    ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo \
    -echoe -echok -echoctl -echoke noflsh -ixon -crtscts 

# Send a command to read slot 23 file 5.
echo -n "\005\027" > /dev/ttyACM0
cat /dev/ttyACM0
