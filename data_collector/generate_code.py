#!/usr/bin/env python3

# This file generates code depending on the contents of ../data_format.json

import copy
import json
import math
from pathlib import Path

data_sizes = {
    'unorm16': 2,
    'snorm16': 2,
    'uint8': 1,
    'error_code': 1,
    'dummy8': 1,
    'dummy64': 1
}

format_description = open('data_format.json', 'r').read()
parsed_format = json.loads(format_description)
format_description = copy.deepcopy(parsed_format)
for key in range(len(parsed_format['layout'])):
    del format_description['layout'][key]['cpp_value']
format_description = json.dumps(format_description, indent=2)
escaped_format_description = format_description.replace('\n', '\\n').replace('"', '\\"')

total_size = 0
for data_item in parsed_format['layout']:
    data_type = data_item['type']
    if data_type not in data_sizes:
        print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
        exit(1)
    total_size += data_sizes[data_type]

output_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ./data_format.json. You may instead change that file',
    '// and then run ./generate_code.py to update the contents of this file.',
    '',
    '#ifndef GENERATED_CONFIG_H_',
    '#define GENERATED_CONFIG_H_',
    '',
    '#define DEFAULT_FORMAT_CONTENT "' + escaped_format_description + '"',
    '#define DEFAULT_FORMAT_SIZE ' + str(len(format_description)),
    '',
    '// Delay in microseconds between each frame',
    '#define FRAME_TIME_US ' + str(parsed_format['frame_time_us']) + '',
    '// How many bytes each data frame occupies.',
    '#define FRAME_SIZE ' + str(total_size) + '',
    '#define TOTAL_NUM_LODS ' + str(parsed_format['total_num_lods']) + '',
    '// How many additional versions of the file to create with sequentially lower',
    '// resolutions.',
    '#define NUM_LOW_RES_LODS ' + str(parsed_format['total_num_lods'] - 1) + '',
    '// How much the sample rate should be divided for each sequential file.',
    '#define LOD_SAMPLE_INTERVAL ' + str(parsed_format['lod_sample_interval']) + '',
    '',
    '#endif',
    ''
])

output = open('generated_format_info.h', 'w')
output.write(output_content)
output.close()
