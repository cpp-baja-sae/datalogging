# Data Format

How the recorded data is packaged both for log files and for realtime data
transmission.

## Datalogs

Datalogs are recordings of all the sensors on the car spanning a certain time
frame. Each datalog is stored in its own folder named after the Unix timestamp 
of when that datalog began. Each of these folders contains several files. The 
first file, named `0.bin` contains all the data recorded, at full resolution.
Each successive file (`1.bin`, `2.bin`, etc.) contains the same data at
successively lower resolutions. The file `format.json` describes how it is
formatted, including information such as how long the datalog ran for as well
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
types:

- **unorm16**: Unsigned normalized 16-bit number, I.E. a value from 0.0 to 1.0.
  Occupies two bytes.
- **snorm16**: Signed (two's compliment) normalized 16-bit number, I.E. a value 
  from -1.0 to 1.0. Occupies two bytes.
- **uint8**: Unsigned 8-bit integer, a value from 0 to 255.
- **error_code**: An error code, currently the only use of this is to identify 
  which step last took an unexpectedly long amount of time on the Teensy. It is
  formatted as an unsigned 8-bit integer.
- **dummy8**: An unused 8-bit (1 byte) value. This can be used as a placeholder.
- **dummy64**: An unused 64-bit (8 byte) value. This can be used as a 
  placeholder.
- TODO: Other types as they become necessary.

For example, a frame containing 4 `unorm16` values would be 8 bytes long and
might represent 4 channels of analog data:

```
11223344
```

Numbers should always be LITTLE-ENDIAN! This is because the Raspberry Pi does
math in Little Endian, and I just lost multiple hours of debugging trying 
to figure out why a simple piece of code wasn't correctly computing the average
of two (big-endian) numbers.

Every frame in a datalog has the same layout. The layoutof frames in a datalog 
is specified in `format.json`. Frames sent in real-time use the layout specified
in `data_router/expected_format.json`. Its contents can be retrieved from 
`data_router` by sending it a specific command. See `main.js` in the `server` 
component for more details. The server uses the command to provide the file 
contents at the `/api/default_format` endpoint so that the client knows what 
format incoming data frames have.

## Lower resolution frames

Frames at resolutions lower than 0 represent larger intervals of time. Becasue
of this, they may miss spikes or dips that are apparent in higher resolution
data. Because of this, they contain three *subframes*. The first stores the
minimum of several frames recorded in the next more detailed level of detail.
The second stores the maximum, and the third stores the average. The first
two make spikes and dips apparent. To illustrate how this is stored in memory,
suppose we have a datalog where each frame contains 8 `unorm16` values, possibly
from an ADC. Each frame in LOD 0 would then contain 8 16-bit values, one after
the other. LOD 1 would be a quarter of that resolution, so each frame would be
the equivalent of 4 frames in LOD 0. Each frame in LOD 1 would start with the
minimum of the first 16 bit value in all 4 LOD 0 frames, followed by the minimum
of the second, the minimum of the third, and so on. It would then contain the
maximum value amongs the first 16 bit value in all 4 LOD 0 frames, follwed by
the second, third, and so on. Finally, it contains all the average values. This
all results in each low-resolution frame being three times the size of a regular
frame.

## Developer notes
The following code segments need to be modified when a new item type is added:
- `data_types = ` in `data_router/generate_code.py`
- `FORMAT_SIZES`, `FORMAT_CSV_SIZES`, and `FORMAT_PARSERS` in `server/main.js`
- `itemTypeSizes` and `itemParseFns` in `frame.tsx`

## format.json example

```js
{
    "version": 1,           // Format description version for backwards compatibility
    "frame_time_us": 500,   // Time per data frame, in microseconds
    "total_num_lods": 8,    // How many different levels of detail are recorded
    "lod_sample_interval": 4,   // How much lower resolution each successive
                                // LOD is
    "layout": [             // Data frame layout description
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
