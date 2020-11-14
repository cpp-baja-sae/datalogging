#!/usr/bin/env python3

# This file generates code depending on the contents of ../data_format.json

import copy
import json
import math
from pathlib import Path

data_types = {
    'unorm16': {
        # How many bytes this data type takes up in a frame.
        'size': 2,
        # What data type should be used when handling this value in C code.
        # This *must* have `size` bytes.
        'ctype': 'uint16_t',
        # What value to use as the new minimum value when a buffer is reset
        'default_min': '0xFFFF',
        # What value to use as the new maximum value when a buffer is reset
        'default_max': '0',
        # What value to use as the new average value when a buffer is reset
        'default_avg': '0',
        # How to update the minimum with a new value
        'update_min': '$OLD = $NEW < $OLD ? $NEW : $OLD;',
        # How to update the maximum with a new value
        'update_max': '$OLD = $NEW > $OLD ? $NEW : $OLD;',
        # How to update the average with a new value
        'update_avg': '$OLD += $NEW / LOD_SAMPLE_INTERVAL;',
    },
    'snorm16': {
        'size': 2,
        'ctype': 'int16_t',
        'default_min': '0x7FFF',
        'default_max': '-0x8000',
        'default_avg': '0',
        'update_min': '$OLD = $NEW < $OLD ? $NEW : $OLD;',
        'update_max': '$OLD = $NEW > $OLD ? $NEW : $OLD;',
        'update_avg': '$OLD += $NEW / LOD_SAMPLE_INTERVAL;',
    },
    'uint8': {
        'size': 1,
        'ctype': 'uint8_t',
        'default_min': '0xFF',
        'default_max': '0',
        'default_avg': '0',
        'update_min': '$OLD = $NEW < $OLD ? $NEW : $OLD;',
        'update_max': '$OLD = $NEW > $OLD ? $NEW : $OLD;',
        'update_avg': '$OLD += $NEW / LOD_SAMPLE_INTERVAL;',
    },
    'error_code': {
        'size': 1,
        'ctype': 'uint8_t',
        'default_min': '0',
        'default_max': '0',
        'default_avg': '0',
        'update_min': '$OLD = $NEW;',
        'update_max': '$OLD = $NEW;',
        'update_avg': '$OLD += $NEW;',
    },
    'dummy8': {
        'size': 1,
        'ctype': 'uint8_t',
        'default_min': '0',
        'default_max': '0',
        'default_avg': '0',
        'update_min': '$OLD = 0;',
        'update_max': '$OLD = 0;',
        'update_avg': '$OLD = 0;',
    },
    'dummy64': {
        'size': 8,
        'ctype': 'uint64_t',
        'default_min': '0',
        'default_max': '0',
        'default_avg': '0',
        'update_min': '$OLD = 0;',
        'update_max': '$OLD = 0;',
        'update_avg': '$OLD = 0;',
    },
}

format_description = open('data_format.json', 'r').read()
parsed_format = json.loads(format_description)
format_description = copy.deepcopy(parsed_format)
for key in range(len(parsed_format['layout'])):
    del format_description['layout'][key]['cpp_value']
format_description = json.dumps(format_description, indent=4)
escaped_format_description = format_description.replace('\n', '\\n').replace('"', '\\"')

total_size = 0
for data_item in parsed_format['layout']:
    data_type = data_item['type']
    if data_type not in data_types:
        print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
        exit(1)
    data_type = data_types[data_type]
    total_size += data_type['size']

config_content = '\n'.join([
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


def make_buffer_code(piece_maker):
    output = ''
    for data_item in parsed_format['layout']:
        data_type = data_item['type']
        if data_type not in data_types:
            print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
            exit(1)
        data_type = data_types[data_type]
        def make_accessor(base): 
            return base + '.' + data_item['cpp_value']
        hr_name = data_item['group'] + ' -> ' + data_item['name']
        output += piece_maker(make_accessor, data_type, hr_name) + '\n'
    return output


def make_reset_code(make_accessor, current_data_type, hr_name):
    return '\n'.join([
        '    // ' + hr_name,
        '    ' + make_accessor('lodBuffers[lodIndex].minBuffer') +
        ' = ' + current_data_type['default_min'] + ';',
        '    ' + make_accessor('lodBuffers[lodIndex].maxBuffer') +
        ' = ' + current_data_type['default_max'] + ';',
        '    ' + make_accessor('lodBuffers[lodIndex].avgBuffer') +
        ' = ' + current_data_type['default_avg'] + ';',
    ])


def make_propogate_lod_code(make_accessor, current_data_type, hr_name):
    min_line = current_data_type['update_min'] \
        .replace('$OLD', make_accessor('nextLod->minBuffer')) \
        .replace('$NEW', make_accessor('thisLod->minBuffer'))
    max_line = current_data_type['update_max'] \
        .replace('$OLD', make_accessor('nextLod->maxBuffer')) \
        .replace('$NEW', make_accessor('thisLod->maxBuffer'))
    avg_line = current_data_type['update_avg'] \
        .replace('$OLD', make_accessor('nextLod->avgBuffer')) \
        .replace('$NEW', make_accessor('thisLod->avgBuffer'))
    return '\n'.join([
        '        // ' + hr_name,
        '        ' + min_line,
        '        ' + max_line,
        '        ' + avg_line,
    ])


def make_update_first_lod_code(make_accessor, current_data_type, hr_name):
    min_line = current_data_type['update_min'] \
        .replace('$OLD', make_accessor('lodBuffers[0].minBuffer')) \
        .replace('$NEW', make_accessor('incomingData'))
    max_line = current_data_type['update_max'] \
        .replace('$OLD', make_accessor('lodBuffers[0].maxBuffer')) \
        .replace('$NEW', make_accessor('incomingData'))
    avg_line = current_data_type['update_avg'] \
        .replace('$OLD', make_accessor('lodBuffers[0].avgBuffer')) \
        .replace('$NEW', make_accessor('incomingData'))
    return '\n'.join([
        '    // ' + hr_name,
        '    ' + min_line,
        '    ' + max_line,
        '    ' + avg_line,
    ])


data_ops_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ./data_format.json. You may instead change that file',
    '// and then run ./generate_code.py to update the contents of this file.',
    '',
    '#include <stdint.h>',
    '#include <string.h>',
    '',
    '// Resets an LOD buffer as if it had never had any data written to it.',
    'void resetLodBuffer(int lodIndex) {',
    '    lodBuffers[lodIndex].progress = 0;',
    make_buffer_code(make_reset_code),
    '}',
    '',
    '// Called when an LOD buffer becomes full. It propogates the recorded values',
    '// to the next highest LOD (if one exists), saves the contents into the ',
    '// appropriate file buffer, and clears the original buffer. so that more ',
    '// data can be written to it.',
    'void commitLod(int lodIndex) {',
    '    LodBuffer *thisLod = &lodBuffers[lodIndex];',
    '    // If this is not the highest-level LOD, then update the next LOD\'s min, max, and avg.',
    '    if (lodIndex < NUM_LOW_RES_LODS - 1) {',
    '        LodBuffer *nextLod = &lodBuffers[lodIndex + 1];',
    make_buffer_code(make_propogate_lod_code),
    '        nextLod->progress += 1;',
    '        if (nextLod->progress == LOD_SAMPLE_INTERVAL) {',
    '            commitLod(lodIndex + 1);',
    '        }',
    '    }',
    '    // Write new values to the file buffer.',
    '    thisLod->fileBuffer.append(thisLod->minBuffer);',
    '    thisLod->fileBuffer.append(thisLod->maxBuffer);',
    '    thisLod->fileBuffer.append(thisLod->avgBuffer);',
    '    // Reset the buffer to a state where new values can be written to it.',
    '    resetLodBuffer(lodIndex);',
    '}',
    '',
    '// Call this to incorporate the given data into all the LOD buffers.',
    'void updateLods(DataFrame &incomingData) {',
    '    // Update the first LOD with the new data...',
    make_buffer_code(make_update_first_lod_code),
    '    lodBuffers[0].progress += 1;',
    '    // If we have written enough samples to the first LOD...',
    '    if (lodBuffers[0].progress == LOD_SAMPLE_INTERVAL) {',
    '        // Save the parsed_formatrmation and propogate it up to higher LODs',
    '        // as necessary.',
    '        commitLod(0);',
    '    }',
    '}',
    '',
])

Path('generated').mkdir(exist_ok=True)
config_file = open('generated/config.h', 'w')
config_file.write(config_content)
config_file.close()
data_ops_file = open('generated/data_ops.cpp', 'w')
data_ops_file.write(data_ops_content)
data_ops_file.close()
