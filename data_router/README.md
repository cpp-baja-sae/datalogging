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
