# Server

This component runs on a computer in the paddock. It is responsible for serving
up the realtime data stream as well as past logs and the web interface to any
connected computers. It receives data from the car over serial radio or WiFi.

## Development Notes

This component uses NodeJS. You may need to install it with 
`sudo apt install nodejs`. Once that is installed, you may need to run
`npm i` inside this folder to install the packages this project uses. Once
these steps are complete, `run.sh` will start the server with sudo. Since this
is JavaScript, no compilation needs to hapen after editing the source code.
Simply stop and restart the server to test any changes.
