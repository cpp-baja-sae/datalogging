#!/bin/env python3

# This file generates code depending on the contents of ../shared_resources/default_info.json
# It is automatically executed when you run ./build.sh

import json
from pathlib import Path

data_types = {
    'unorm16': {
        'size': 2,
        'ctype': 'uint16_t',
    },
    'snorm16': {
        'size': 2,
        'ctype': 'int16_t',
    },
}

info = json.load(open('../shared_resources/default_info.json', 'r'))

total_size = 0
num_items = len(info['format'])
for data_item in info['format']:
    data_type = data_item['type']
    if data_type not in data_types:
        print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
        exit(1)
    data_type = data_types[data_type]
    total_size += data_type['size']

config_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ../shared_resources/default_info.json. You may instead change that file',
    '// and then run ./build.sh to update the contents of this file.',
    '',
    '#ifndef GENERATED_CONFIG_H_',
    '#define GENERATED_CONFIG_H_',
    '',
    '// Delay in microseconds between each frame',
    '#define FRAME_TIME ' + str(info['frame_time_us']) + '',
    '// How many data values are contained in each frame. Used for initializing ',
    '// variables that keep track of mins, maxes, and averages.',
    '#define FRAME_LEN ' + str(num_items) + '',
    '// How many bytes each data frame occupies.',
    '#define FRAME_SIZE ' + str(total_size) + '',
    '// How many additional versions of the file to create with sequentially lower',
    '// resolutions.',
    '#define NUM_AUX_LODS ' + str(info['total_num_lods'] - 1) + '',
    '// How much the sample rate should be divided for each sequential file.',
    '#define LOD_SAMPLE_INTERVAL ' + str(info['lod_sample_interval']) + '',
    '',
    '#endif',
    ''
])

data_ops_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ../shared_resources/default_info.json. You may instead change that file',
    '// and then run ./build.sh to update the contents of this file.',
    '',
    
    '',
])

Path('generated').mkdir(exist_ok=True)
config_file = open('generated/config.h', 'w')
config_file.write(config_content)
config_file.close()
