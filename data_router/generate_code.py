#!/usr/bin/env python3

# This file generates code depending on the contents of ../shared_resources/default_parsed_format.json
# It is automatically executed when you run ./build.sh

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

format_description = open('expected_format.json', 'r').read()
escaped_format_description = format_description.replace('\n', '\\n').replace('"', '\\"')
parsed_format = json.loads(format_description)

total_size = 0
for data_item in parsed_format['layout']:
    data_type = data_item['type']
    if data_type not in data_types:
        print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
        exit(1)
    data_type = data_types[data_type]
    total_size += data_type['size']
step_interval = parsed_format['frame_time_us'] / total_size
if (step_interval % 1.0 > 0.001):
    print(
        'ERROR: Frame time (' 
        + str(parsed_format['frame_time_us']) 
        + 'us) does not evenly divide into the length of a frame (' 
        + str(total_size) 
        + ' bytes). This must be fixed to ensure timing is correct.'
    )
    exit(1)
step_interval = int(step_interval)

config_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ../shared_resources/default_parsed_format.json. You may instead change that file',
    '// and then run ./build.sh to update the contents of this file.',
    '',
    '#ifndef GENERATED_CONFIG_H_',
    '#define GENERATED_CONFIG_H_',
    '',
    '#define DEFAULT_FORMAT_CONTENT "' + escaped_format_description + '"',
    '#define DEFAULT_FORMAT_SIZE ' + str(len(format_description)),
    '',
    '// Delay in microseconds between each frame',
    '#define FRAME_TIME ' + str(parsed_format['frame_time_us']) + '',
    '// How many bytes each data frame occupies.',
    '#define FRAME_SIZE ' + str(total_size) + '',
    # These two may be different if step_interval is an odd number.
    '// How many microseconds the step clock should stay on for each step.',
    '#define STEP_CLOCK_ON_TIME ' + str(math.ceil(step_interval / 2.0)),
    '// How many microseconds the step clock should stay off for each step.',
    '#define STEP_CLOCK_OFF_TIME ' + str(math.floor(step_interval / 2.0)),
    '// How many additional versions of the file to create with sequentially lower',
    '// resolutions.',
    '#define NUM_AUX_LODS ' + str(parsed_format['total_num_lods'] - 1) + '',
    '// How much the sample rate should be divided for each sequential file.',
    '#define LOD_SAMPLE_INTERVAL ' + str(parsed_format['lod_sample_interval']) + '',
    '',
    '#endif',
    ''
])


def make_buffer_code(piece_maker):
    current_offset = 0
    output = ''
    for data_item in parsed_format['layout']:
        data_type = data_item['type']
        if data_type not in data_types:
            print('ERROR: ' + data_item['type'] + ' is not a valid data type.')
            exit(1)
        data_type = data_types[data_type]
        def make_accessor(
            base): return '*((' + data_type['ctype'] + '*) ((' + base + ') + ' + str(current_offset) + '))'
        hr_name = data_item['group'] + ' -> ' + data_item['name']
        output += piece_maker(make_accessor, data_type, hr_name) + '\n'
        current_offset += data_type['size']
    return output


def make_reset_code(make_accessor, current_data_type, hr_name):
    return '\n'.join([
        '    // ' + hr_name,
        '    ' + make_accessor('lod_infos[lod_index].min_buffer') +
        ' = ' + current_data_type['default_min'] + ';',
        '    ' + make_accessor('lod_infos[lod_index].max_buffer') +
        ' = ' + current_data_type['default_max'] + ';',
        '    ' + make_accessor('lod_infos[lod_index].avg_buffer') +
        ' = ' + current_data_type['default_avg'] + ';',
    ])


def make_propogate_lod_code(make_accessor, current_data_type, hr_name):
    min_line = current_data_type['update_min'] \
        .replace('$OLD', make_accessor('next_lod->min_buffer')) \
        .replace('$NEW', make_accessor('this_lod->min_buffer'))
    max_line = current_data_type['update_max'] \
        .replace('$OLD', make_accessor('next_lod->max_buffer')) \
        .replace('$NEW', make_accessor('this_lod->max_buffer'))
    avg_line = current_data_type['update_avg'] \
        .replace('$OLD', make_accessor('next_lod->avg_buffer')) \
        .replace('$NEW', make_accessor('this_lod->avg_buffer'))
    return '\n'.join([
        '        // ' + hr_name,
        '        ' + min_line,
        '        ' + max_line,
        '        ' + avg_line,
    ])


def make_update_first_lod_code(make_accessor, current_data_type, hr_name):
    min_line = current_data_type['update_min'] \
        .replace('$OLD', make_accessor('lod_infos[0].min_buffer')) \
        .replace('$NEW', make_accessor('incoming_data'))
    max_line = current_data_type['update_max'] \
        .replace('$OLD', make_accessor('lod_infos[0].max_buffer')) \
        .replace('$NEW', make_accessor('incoming_data'))
    avg_line = current_data_type['update_avg'] \
        .replace('$OLD', make_accessor('lod_infos[0].avg_buffer')) \
        .replace('$NEW', make_accessor('incoming_data'))
    return '\n'.join([
        '    // ' + hr_name,
        '    ' + min_line,
        '    ' + max_line,
        '    ' + avg_line,
    ])


data_ops_content = '\n'.join([
    '// Do not make changes to this file, it was auto-generated based on the contents',
    '// of ../shared_resources/default_parsed_format.json. You may instead change that file',
    '// and then run ./build.sh to update the contents of this file.',
    '',
    '#include <stdint.h>',
    '#include <string.h>',
    '',
    'void reset_lod_buffer(int lod_index) {',
    '    lod_infos[lod_index].progress = 0;',
    make_buffer_code(make_reset_code),
    '}',
    '',
    'void commit_lod(int lod_index) {',
    '    volatile struct LodInfo *this_lod = &lod_infos[lod_index];',
    '    // If this is not the highest-level LOD, then update the next LOD\'s min, max, and avg.',
    '    if (lod_index < NUM_AUX_LODS - 1) {',
    '        volatile struct LodInfo *next_lod = &lod_infos[lod_index + 1];',
    make_buffer_code(make_propogate_lod_code),
    '        next_lod->progress += 1;',
    '        if (next_lod->progress == LOD_SAMPLE_INTERVAL) {',
    '            commit_lod(lod_index + 1);',
    '        }',
    '    }',
    '    // Write new values to the file buffer.',
    '    memcpy(',
    '        &this_lod->file_buffer[this_lod->fbuf_write_index],',
    '        this_lod->min_buffer,',
    '        FRAME_SIZE',
    '    );',
    '    memcpy(',
    '        &this_lod->file_buffer[this_lod->fbuf_write_index + FRAME_SIZE],',
    '        this_lod->max_buffer,',
    '        FRAME_SIZE',
    '    );',
    '    memcpy(',
    '        &this_lod->file_buffer[this_lod->fbuf_write_index + 2 * FRAME_SIZE],',
    '        this_lod->avg_buffer,',
    '        FRAME_SIZE',
    '    );',
    '    this_lod->fbuf_write_index = (this_lod->fbuf_write_index + 3 * FRAME_SIZE) % FILE_BUFFER_SIZE;',
    '    // Reset the buffer to a state where new values can be written to it.',
    '    reset_lod_buffer(lod_index);',
    '}',
    '',
    'void update_lods() {',
    '    // Update the first LOD with the new data...',
    '    volatile char *incoming_data = &primary_file_buffer[pbuf_write_index];',
    make_buffer_code(make_update_first_lod_code),
    '    lod_infos[0].progress += 1;',
    '    // If we have written enough samples to the first LOD...',
    '    if (lod_infos[0].progress == LOD_SAMPLE_INTERVAL) {',
    '        // Save the parsed_formatrmation and propogate it up to higher LODs',
    '        // as necessary.',
    '        commit_lod(0);',
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
