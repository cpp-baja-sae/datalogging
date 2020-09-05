#!/bin/env python3

# This file generates code depending on the contents of ../shared_resources/default_info.json
# It is automatically executed when you run ./build.sh

import json
from pathlib import Path

data_types = {
    'unorm16': {
        'size': 2,
    },
    'snorm16': {
        'size': 2,
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

config_content = ''
config_content += '// Do not make changes to this file, it was auto-generated based on the contents\n'
config_content += '// of ../shared_resources/default_info.json. You may instead change that file\n'
config_content += '// and then run ./build.sh to update the contents of this file.\n'
config_content += '\n'
config_content += '#ifndef GENERATED_CONFIG_H_\n'
config_content += '#define GENERATED_CONFIG_H_\n'
config_content += '\n'
config_content += '// Delay in microseconds between each frame\n'
config_content += '#define FRAME_TIME ' + str(info['frame_time_us']) + '\n'
config_content += '// How many data values are contained in each frame. Used for initializing \n'
config_content += '// variables that keep track of mins, maxes, and averages.\n'
config_content += '#define FRAME_LEN ' + str(num_items) + '\n'
config_content += '// How many bytes each data frame occupies.\n'
config_content += '#define FRAME_SIZE ' + str(total_size) + '\n'
config_content += '// How many additional versions of the file to create with sequentially lower\n'
config_content += '// resolutions.\n'
config_content += '#define NUM_AUX_LODS ' + \
    str(info['total_num_lods'] - 1) + '\n'
config_content += '// How much the sample rate should be divided for each sequential file.\n'
config_content += '#define LOD_SAMPLE_INTERVAL ' + \
    str(info['lod_sample_interval']) + '\n'
config_content += '\n'
config_content += '#endif\n'

Path('generated').mkdir(exist_ok=True)
config_file = open('generated/config.h', 'w')
config_file.write(config_content)
config_file.close()
