# Data Router

This component runs on the Raspberry Pi on the car. It is responsible for
collecting formatted data over the GPIO pins and packaging it into files. 
It also transmits data in real time over a serial connection. It can take
simple commands over a serial connection to perform simple tasks such as 
starting and stopping recording or changing how much data is streamed in
real-time.

## Development notes

`build.sh` compiles the program. `run.sh` executes it with sudo priviledges.
This program requires the `pigpio` library which may need to be installed with 
`sudo apt install libpigpio-dev`. It also requires cmake and a c compiler, which 
can both be installed with `sudo apt install build-essential cmake`

## Workers

This component runs four threads, or "workers", each responsible for a different
task:
- `sensor_read_worker` is responsible for recording data from the GPIO pins and
  placing it into ring buffers in RAM as well as creating lower resolution
  versions of the data and placing those into seperate buffers.
- `file_worker` is responsible for writing recorded data to files on the SD
  card as well as writing metadata so that we know what format the data was
  written in.
- `realtime_stream_worker` is responsible for sending a portion of the recorded
  data over a serial connection.
- `command_worker` is responsible for receiving and processing commands over a
  serial connection.

## TODO:
- Currently, the serial connections are simulated with Unix sockets so that we
  do not have to use a second rpi for testing. This will eventually need to 
  change.
- `realtime_stream_worker` currently sporatically sends frames from the full
  resolution data. This should be changed so that it sends all the data from
  a specific resolution so that we can see the minimum and maximum data.
- `sensor_read_worker` is set up for reading from the ADCs. Once the teensies
  come in we should change that.