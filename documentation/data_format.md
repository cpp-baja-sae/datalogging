# Data Format

How the recorded data is packaged both for log files and for realtime data
transmission.

## Datalogs

Datalogs are recordings of all the sensors on the car spanning a certain time
frame. Each datalog is stored in its own folder named after the Unix timestamp 
of when that datalog began. Each of these folders contains several files. The 
first file, named `0.bin` contains all the data recorded, at full resolution.
Each successive file (`1.bin`, `2.bin`, etc.) contains the same data at
successively lower resolutions. The file `info.json` contains information about
the datalog, including information such as how long the datalog ran for as well
as what sensors were connected at the time. Each of the `.bin` files is simply
a series of *frames*, one after the other, with no seperation or additional 
information.

## Lower resolutions

Each successive level of detail after 0 stores data at a resolution one quarter
of that of the level of detail before it. For example, `1.bin` stores data at 
one quarter the resolution of `0.bin`, and `2.bin` stores data at one quarter
the resolution of that. This mechanism is also used to select the quality of
data sent in realtime over the serial radio to effectively use the available 
bandwidth.

## Frames

Frames contain data captured during a certain time interval. At the time of
writing this, one frame represents 1/2,000th of a second. It contains a list of
items recorded from different sensors. Each item may be in one of a number of
formats:

- **unorm16**: Unsigned normalized 16-bit number, I.E. a value from 0.0 to 1.0.
  Occupies two bytes.
- TODO: Other formats as they become necessary.

For example, a frame containing 4 `unorm16` values would be 8 bytes long and
might represent 4 channels of analog data:

```
11223344
```

Every frame in a datalog has the same format. The format of frames in a datalog 
is specified in `info.json`. The format of frames sent as realtime data are 
unspecified at the moment and are hard-coded in.

## Lower resolution frames

Frames at resolutions lower than 0 represent larger intervals of time. Becasue
of this, they may miss spikes or dips that are apparent in higher resolution
data. Because of this, they contain three *subframes*. The first stores the
average of several frames recorded in the next more detailed level of detail.
The second stores the minimum, and the third stores the maximum. These last
two make spikes and dips apparent. To illustrate how this is stored in memory,
suppose we have a datalog where each frame contains 8 `unorm16` values, possibly
from an ADC. Each frame in LOD 0 would then contain 8 16-bit values, one after
the other. LOD 1 would be a quarter of that resolution, so each frame would be
the equivalent of 4 frames in LOD 0. Each frame in LOD 1 would start with the
averages of the first 16 bit value in all 4 LOD 0 frames, follwed by the average
of the second, the average of the third, and so on. It would then contain the
minimum value amongs the first 16 bit value in all 4 LOD 0 frames, follwed by
the second, third, and so on. Finally, it contains all the maximum values. This
all results in each low-resolution frame being three times the size of a regular
frame.

## info.json format

```json
{
    "version": "1",         // info.json format version
    "frame_time_us": "500", // Time per data frame, in microseconds
    "total_num_lods": "8",  // How many different levels of detail are recorded
    "lod_sample_interval": "4", // How much lower resolution each successive
                                // LOD is
    "format": [             // Data frame format description
        {
            "group": "ADC 0",      // For identification by humans
            "name": "Channel 0",   // *
            "type": "unorm16",     // See Frames section
        },
        {
            "group": "ADC 0",
            "name": "Channel 1",
            "type": "unorm16"
        }
    ]
}
```
