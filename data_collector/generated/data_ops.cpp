// Do not make changes to this file, it was auto-generated based on the contents
// of ./data_format.json. You may instead change that file
// and then run ./generate_code.py to update the contents of this file.

#include <stdint.h>
#include <string.h>

void reset_lod_buffer(int lod_index) {
    lod_infos[lod_index].progress = 0;
    // ADC 1 -> Channel 1
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 0)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 0)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 0)) = 0;
    // ADC 1 -> Channel 2
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 2)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 2)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 2)) = 0;
    // ADC 1 -> Channel 3
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 4)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 4)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 4)) = 0;
    // ADC 1 -> Channel 4
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 6)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 6)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 6)) = 0;
    // ADC 1 -> Channel 5
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 8)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 8)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 8)) = 0;
    // ADC 1 -> Channel 6
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 10)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 10)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 10)) = 0;
    // ADC 1 -> Channel 7
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 12)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 12)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 12)) = 0;
    // ADC 1 -> Channel 8
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 14)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 14)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 14)) = 0;
    // ADC 2 -> Channel 1
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 16)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 16)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 16)) = 0;
    // ADC 2 -> Channel 2
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 18)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 18)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 18)) = 0;
    // ADC 2 -> Channel 3
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 20)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 20)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 20)) = 0;
    // ADC 2 -> Channel 4
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 22)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 22)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 22)) = 0;
    // ADC 2 -> Channel 5
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 24)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 24)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 24)) = 0;
    // ADC 2 -> Channel 6
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 26)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 26)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 26)) = 0;
    // ADC 2 -> Channel 7
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 28)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 28)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 28)) = 0;
    // ADC 2 -> Channel 8
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 30)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 30)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 30)) = 0;
    // ADC 3 -> Channel 1
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 32)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 32)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 32)) = 0;
    // ADC 3 -> Channel 2
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 34)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 34)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 34)) = 0;
    // ADC 3 -> Channel 3
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 36)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 36)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 36)) = 0;
    // ADC 3 -> Channel 4
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 38)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 38)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 38)) = 0;
    // ADC 3 -> Channel 5
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 40)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 40)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 40)) = 0;
    // ADC 3 -> Channel 6
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 42)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 42)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 42)) = 0;
    // ADC 3 -> Channel 7
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 44)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 44)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 44)) = 0;
    // ADC 3 -> Channel 8
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 46)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 46)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 46)) = 0;
    // ADC 4 -> Channel 1
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 48)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 48)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 48)) = 0;
    // ADC 4 -> Channel 2
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 50)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 50)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 50)) = 0;
    // ADC 4 -> Channel 3
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 52)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 52)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 52)) = 0;
    // ADC 4 -> Channel 4
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 54)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 54)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 54)) = 0;
    // ADC 4 -> Channel 5
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 56)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 56)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 56)) = 0;
    // ADC 4 -> Channel 6
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 58)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 58)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 58)) = 0;
    // ADC 4 -> Channel 7
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 60)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 60)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 60)) = 0;
    // ADC 4 -> Channel 8
    *((int16_t*) ((lod_infos[lod_index].min_buffer) + 62)) = 0x7FFF;
    *((int16_t*) ((lod_infos[lod_index].max_buffer) + 62)) = -0x8000;
    *((int16_t*) ((lod_infos[lod_index].avg_buffer) + 62)) = 0;
    // Dummy -> A
    *((uint64_t*) ((lod_infos[lod_index].min_buffer) + 64)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].max_buffer) + 64)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].avg_buffer) + 64)) = 0;
    // Dummy -> B
    *((uint64_t*) ((lod_infos[lod_index].min_buffer) + 72)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].max_buffer) + 72)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].avg_buffer) + 72)) = 0;
    // Dummy -> C
    *((uint64_t*) ((lod_infos[lod_index].min_buffer) + 80)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].max_buffer) + 80)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].avg_buffer) + 80)) = 0;
    // Dummy -> D
    *((uint64_t*) ((lod_infos[lod_index].min_buffer) + 88)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].max_buffer) + 88)) = 0;
    *((uint64_t*) ((lod_infos[lod_index].avg_buffer) + 88)) = 0;
    // Dummy -> W
    *((uint8_t*) ((lod_infos[lod_index].min_buffer) + 96)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].max_buffer) + 96)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].avg_buffer) + 96)) = 0;
    // Dummy -> X
    *((uint8_t*) ((lod_infos[lod_index].min_buffer) + 97)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].max_buffer) + 97)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].avg_buffer) + 97)) = 0;
    // Diagnostics -> Error Count
    *((uint8_t*) ((lod_infos[lod_index].min_buffer) + 98)) = 0xFF;
    *((uint8_t*) ((lod_infos[lod_index].max_buffer) + 98)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].avg_buffer) + 98)) = 0;
    // Diagnostics -> Last Error Cause
    *((uint8_t*) ((lod_infos[lod_index].min_buffer) + 99)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].max_buffer) + 99)) = 0;
    *((uint8_t*) ((lod_infos[lod_index].avg_buffer) + 99)) = 0;

}

void commit_lod(int lod_index) {
    volatile struct LodInfo *this_lod = &lod_infos[lod_index];
    // If this is not the highest-level LOD, then update the next LOD's min, max, and avg.
    if (lod_index < NUM_AUX_LODS - 1) {
        volatile struct LodInfo *next_lod = &lod_infos[lod_index + 1];
        // ADC 1 -> Channel 1
        *((int16_t*) ((next_lod->min_buffer) + 0)) = *((int16_t*) ((this_lod->min_buffer) + 0)) < *((int16_t*) ((next_lod->min_buffer) + 0)) ? *((int16_t*) ((this_lod->min_buffer) + 0)) : *((int16_t*) ((next_lod->min_buffer) + 0));
        *((int16_t*) ((next_lod->max_buffer) + 0)) = *((int16_t*) ((this_lod->max_buffer) + 0)) > *((int16_t*) ((next_lod->max_buffer) + 0)) ? *((int16_t*) ((this_lod->max_buffer) + 0)) : *((int16_t*) ((next_lod->max_buffer) + 0));
        *((int16_t*) ((next_lod->avg_buffer) + 0)) += *((int16_t*) ((this_lod->avg_buffer) + 0)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 2
        *((int16_t*) ((next_lod->min_buffer) + 2)) = *((int16_t*) ((this_lod->min_buffer) + 2)) < *((int16_t*) ((next_lod->min_buffer) + 2)) ? *((int16_t*) ((this_lod->min_buffer) + 2)) : *((int16_t*) ((next_lod->min_buffer) + 2));
        *((int16_t*) ((next_lod->max_buffer) + 2)) = *((int16_t*) ((this_lod->max_buffer) + 2)) > *((int16_t*) ((next_lod->max_buffer) + 2)) ? *((int16_t*) ((this_lod->max_buffer) + 2)) : *((int16_t*) ((next_lod->max_buffer) + 2));
        *((int16_t*) ((next_lod->avg_buffer) + 2)) += *((int16_t*) ((this_lod->avg_buffer) + 2)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 3
        *((int16_t*) ((next_lod->min_buffer) + 4)) = *((int16_t*) ((this_lod->min_buffer) + 4)) < *((int16_t*) ((next_lod->min_buffer) + 4)) ? *((int16_t*) ((this_lod->min_buffer) + 4)) : *((int16_t*) ((next_lod->min_buffer) + 4));
        *((int16_t*) ((next_lod->max_buffer) + 4)) = *((int16_t*) ((this_lod->max_buffer) + 4)) > *((int16_t*) ((next_lod->max_buffer) + 4)) ? *((int16_t*) ((this_lod->max_buffer) + 4)) : *((int16_t*) ((next_lod->max_buffer) + 4));
        *((int16_t*) ((next_lod->avg_buffer) + 4)) += *((int16_t*) ((this_lod->avg_buffer) + 4)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 4
        *((int16_t*) ((next_lod->min_buffer) + 6)) = *((int16_t*) ((this_lod->min_buffer) + 6)) < *((int16_t*) ((next_lod->min_buffer) + 6)) ? *((int16_t*) ((this_lod->min_buffer) + 6)) : *((int16_t*) ((next_lod->min_buffer) + 6));
        *((int16_t*) ((next_lod->max_buffer) + 6)) = *((int16_t*) ((this_lod->max_buffer) + 6)) > *((int16_t*) ((next_lod->max_buffer) + 6)) ? *((int16_t*) ((this_lod->max_buffer) + 6)) : *((int16_t*) ((next_lod->max_buffer) + 6));
        *((int16_t*) ((next_lod->avg_buffer) + 6)) += *((int16_t*) ((this_lod->avg_buffer) + 6)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 5
        *((int16_t*) ((next_lod->min_buffer) + 8)) = *((int16_t*) ((this_lod->min_buffer) + 8)) < *((int16_t*) ((next_lod->min_buffer) + 8)) ? *((int16_t*) ((this_lod->min_buffer) + 8)) : *((int16_t*) ((next_lod->min_buffer) + 8));
        *((int16_t*) ((next_lod->max_buffer) + 8)) = *((int16_t*) ((this_lod->max_buffer) + 8)) > *((int16_t*) ((next_lod->max_buffer) + 8)) ? *((int16_t*) ((this_lod->max_buffer) + 8)) : *((int16_t*) ((next_lod->max_buffer) + 8));
        *((int16_t*) ((next_lod->avg_buffer) + 8)) += *((int16_t*) ((this_lod->avg_buffer) + 8)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 6
        *((int16_t*) ((next_lod->min_buffer) + 10)) = *((int16_t*) ((this_lod->min_buffer) + 10)) < *((int16_t*) ((next_lod->min_buffer) + 10)) ? *((int16_t*) ((this_lod->min_buffer) + 10)) : *((int16_t*) ((next_lod->min_buffer) + 10));
        *((int16_t*) ((next_lod->max_buffer) + 10)) = *((int16_t*) ((this_lod->max_buffer) + 10)) > *((int16_t*) ((next_lod->max_buffer) + 10)) ? *((int16_t*) ((this_lod->max_buffer) + 10)) : *((int16_t*) ((next_lod->max_buffer) + 10));
        *((int16_t*) ((next_lod->avg_buffer) + 10)) += *((int16_t*) ((this_lod->avg_buffer) + 10)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 7
        *((int16_t*) ((next_lod->min_buffer) + 12)) = *((int16_t*) ((this_lod->min_buffer) + 12)) < *((int16_t*) ((next_lod->min_buffer) + 12)) ? *((int16_t*) ((this_lod->min_buffer) + 12)) : *((int16_t*) ((next_lod->min_buffer) + 12));
        *((int16_t*) ((next_lod->max_buffer) + 12)) = *((int16_t*) ((this_lod->max_buffer) + 12)) > *((int16_t*) ((next_lod->max_buffer) + 12)) ? *((int16_t*) ((this_lod->max_buffer) + 12)) : *((int16_t*) ((next_lod->max_buffer) + 12));
        *((int16_t*) ((next_lod->avg_buffer) + 12)) += *((int16_t*) ((this_lod->avg_buffer) + 12)) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 8
        *((int16_t*) ((next_lod->min_buffer) + 14)) = *((int16_t*) ((this_lod->min_buffer) + 14)) < *((int16_t*) ((next_lod->min_buffer) + 14)) ? *((int16_t*) ((this_lod->min_buffer) + 14)) : *((int16_t*) ((next_lod->min_buffer) + 14));
        *((int16_t*) ((next_lod->max_buffer) + 14)) = *((int16_t*) ((this_lod->max_buffer) + 14)) > *((int16_t*) ((next_lod->max_buffer) + 14)) ? *((int16_t*) ((this_lod->max_buffer) + 14)) : *((int16_t*) ((next_lod->max_buffer) + 14));
        *((int16_t*) ((next_lod->avg_buffer) + 14)) += *((int16_t*) ((this_lod->avg_buffer) + 14)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 1
        *((int16_t*) ((next_lod->min_buffer) + 16)) = *((int16_t*) ((this_lod->min_buffer) + 16)) < *((int16_t*) ((next_lod->min_buffer) + 16)) ? *((int16_t*) ((this_lod->min_buffer) + 16)) : *((int16_t*) ((next_lod->min_buffer) + 16));
        *((int16_t*) ((next_lod->max_buffer) + 16)) = *((int16_t*) ((this_lod->max_buffer) + 16)) > *((int16_t*) ((next_lod->max_buffer) + 16)) ? *((int16_t*) ((this_lod->max_buffer) + 16)) : *((int16_t*) ((next_lod->max_buffer) + 16));
        *((int16_t*) ((next_lod->avg_buffer) + 16)) += *((int16_t*) ((this_lod->avg_buffer) + 16)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 2
        *((int16_t*) ((next_lod->min_buffer) + 18)) = *((int16_t*) ((this_lod->min_buffer) + 18)) < *((int16_t*) ((next_lod->min_buffer) + 18)) ? *((int16_t*) ((this_lod->min_buffer) + 18)) : *((int16_t*) ((next_lod->min_buffer) + 18));
        *((int16_t*) ((next_lod->max_buffer) + 18)) = *((int16_t*) ((this_lod->max_buffer) + 18)) > *((int16_t*) ((next_lod->max_buffer) + 18)) ? *((int16_t*) ((this_lod->max_buffer) + 18)) : *((int16_t*) ((next_lod->max_buffer) + 18));
        *((int16_t*) ((next_lod->avg_buffer) + 18)) += *((int16_t*) ((this_lod->avg_buffer) + 18)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 3
        *((int16_t*) ((next_lod->min_buffer) + 20)) = *((int16_t*) ((this_lod->min_buffer) + 20)) < *((int16_t*) ((next_lod->min_buffer) + 20)) ? *((int16_t*) ((this_lod->min_buffer) + 20)) : *((int16_t*) ((next_lod->min_buffer) + 20));
        *((int16_t*) ((next_lod->max_buffer) + 20)) = *((int16_t*) ((this_lod->max_buffer) + 20)) > *((int16_t*) ((next_lod->max_buffer) + 20)) ? *((int16_t*) ((this_lod->max_buffer) + 20)) : *((int16_t*) ((next_lod->max_buffer) + 20));
        *((int16_t*) ((next_lod->avg_buffer) + 20)) += *((int16_t*) ((this_lod->avg_buffer) + 20)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 4
        *((int16_t*) ((next_lod->min_buffer) + 22)) = *((int16_t*) ((this_lod->min_buffer) + 22)) < *((int16_t*) ((next_lod->min_buffer) + 22)) ? *((int16_t*) ((this_lod->min_buffer) + 22)) : *((int16_t*) ((next_lod->min_buffer) + 22));
        *((int16_t*) ((next_lod->max_buffer) + 22)) = *((int16_t*) ((this_lod->max_buffer) + 22)) > *((int16_t*) ((next_lod->max_buffer) + 22)) ? *((int16_t*) ((this_lod->max_buffer) + 22)) : *((int16_t*) ((next_lod->max_buffer) + 22));
        *((int16_t*) ((next_lod->avg_buffer) + 22)) += *((int16_t*) ((this_lod->avg_buffer) + 22)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 5
        *((int16_t*) ((next_lod->min_buffer) + 24)) = *((int16_t*) ((this_lod->min_buffer) + 24)) < *((int16_t*) ((next_lod->min_buffer) + 24)) ? *((int16_t*) ((this_lod->min_buffer) + 24)) : *((int16_t*) ((next_lod->min_buffer) + 24));
        *((int16_t*) ((next_lod->max_buffer) + 24)) = *((int16_t*) ((this_lod->max_buffer) + 24)) > *((int16_t*) ((next_lod->max_buffer) + 24)) ? *((int16_t*) ((this_lod->max_buffer) + 24)) : *((int16_t*) ((next_lod->max_buffer) + 24));
        *((int16_t*) ((next_lod->avg_buffer) + 24)) += *((int16_t*) ((this_lod->avg_buffer) + 24)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 6
        *((int16_t*) ((next_lod->min_buffer) + 26)) = *((int16_t*) ((this_lod->min_buffer) + 26)) < *((int16_t*) ((next_lod->min_buffer) + 26)) ? *((int16_t*) ((this_lod->min_buffer) + 26)) : *((int16_t*) ((next_lod->min_buffer) + 26));
        *((int16_t*) ((next_lod->max_buffer) + 26)) = *((int16_t*) ((this_lod->max_buffer) + 26)) > *((int16_t*) ((next_lod->max_buffer) + 26)) ? *((int16_t*) ((this_lod->max_buffer) + 26)) : *((int16_t*) ((next_lod->max_buffer) + 26));
        *((int16_t*) ((next_lod->avg_buffer) + 26)) += *((int16_t*) ((this_lod->avg_buffer) + 26)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 7
        *((int16_t*) ((next_lod->min_buffer) + 28)) = *((int16_t*) ((this_lod->min_buffer) + 28)) < *((int16_t*) ((next_lod->min_buffer) + 28)) ? *((int16_t*) ((this_lod->min_buffer) + 28)) : *((int16_t*) ((next_lod->min_buffer) + 28));
        *((int16_t*) ((next_lod->max_buffer) + 28)) = *((int16_t*) ((this_lod->max_buffer) + 28)) > *((int16_t*) ((next_lod->max_buffer) + 28)) ? *((int16_t*) ((this_lod->max_buffer) + 28)) : *((int16_t*) ((next_lod->max_buffer) + 28));
        *((int16_t*) ((next_lod->avg_buffer) + 28)) += *((int16_t*) ((this_lod->avg_buffer) + 28)) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 8
        *((int16_t*) ((next_lod->min_buffer) + 30)) = *((int16_t*) ((this_lod->min_buffer) + 30)) < *((int16_t*) ((next_lod->min_buffer) + 30)) ? *((int16_t*) ((this_lod->min_buffer) + 30)) : *((int16_t*) ((next_lod->min_buffer) + 30));
        *((int16_t*) ((next_lod->max_buffer) + 30)) = *((int16_t*) ((this_lod->max_buffer) + 30)) > *((int16_t*) ((next_lod->max_buffer) + 30)) ? *((int16_t*) ((this_lod->max_buffer) + 30)) : *((int16_t*) ((next_lod->max_buffer) + 30));
        *((int16_t*) ((next_lod->avg_buffer) + 30)) += *((int16_t*) ((this_lod->avg_buffer) + 30)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 1
        *((int16_t*) ((next_lod->min_buffer) + 32)) = *((int16_t*) ((this_lod->min_buffer) + 32)) < *((int16_t*) ((next_lod->min_buffer) + 32)) ? *((int16_t*) ((this_lod->min_buffer) + 32)) : *((int16_t*) ((next_lod->min_buffer) + 32));
        *((int16_t*) ((next_lod->max_buffer) + 32)) = *((int16_t*) ((this_lod->max_buffer) + 32)) > *((int16_t*) ((next_lod->max_buffer) + 32)) ? *((int16_t*) ((this_lod->max_buffer) + 32)) : *((int16_t*) ((next_lod->max_buffer) + 32));
        *((int16_t*) ((next_lod->avg_buffer) + 32)) += *((int16_t*) ((this_lod->avg_buffer) + 32)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 2
        *((int16_t*) ((next_lod->min_buffer) + 34)) = *((int16_t*) ((this_lod->min_buffer) + 34)) < *((int16_t*) ((next_lod->min_buffer) + 34)) ? *((int16_t*) ((this_lod->min_buffer) + 34)) : *((int16_t*) ((next_lod->min_buffer) + 34));
        *((int16_t*) ((next_lod->max_buffer) + 34)) = *((int16_t*) ((this_lod->max_buffer) + 34)) > *((int16_t*) ((next_lod->max_buffer) + 34)) ? *((int16_t*) ((this_lod->max_buffer) + 34)) : *((int16_t*) ((next_lod->max_buffer) + 34));
        *((int16_t*) ((next_lod->avg_buffer) + 34)) += *((int16_t*) ((this_lod->avg_buffer) + 34)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 3
        *((int16_t*) ((next_lod->min_buffer) + 36)) = *((int16_t*) ((this_lod->min_buffer) + 36)) < *((int16_t*) ((next_lod->min_buffer) + 36)) ? *((int16_t*) ((this_lod->min_buffer) + 36)) : *((int16_t*) ((next_lod->min_buffer) + 36));
        *((int16_t*) ((next_lod->max_buffer) + 36)) = *((int16_t*) ((this_lod->max_buffer) + 36)) > *((int16_t*) ((next_lod->max_buffer) + 36)) ? *((int16_t*) ((this_lod->max_buffer) + 36)) : *((int16_t*) ((next_lod->max_buffer) + 36));
        *((int16_t*) ((next_lod->avg_buffer) + 36)) += *((int16_t*) ((this_lod->avg_buffer) + 36)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 4
        *((int16_t*) ((next_lod->min_buffer) + 38)) = *((int16_t*) ((this_lod->min_buffer) + 38)) < *((int16_t*) ((next_lod->min_buffer) + 38)) ? *((int16_t*) ((this_lod->min_buffer) + 38)) : *((int16_t*) ((next_lod->min_buffer) + 38));
        *((int16_t*) ((next_lod->max_buffer) + 38)) = *((int16_t*) ((this_lod->max_buffer) + 38)) > *((int16_t*) ((next_lod->max_buffer) + 38)) ? *((int16_t*) ((this_lod->max_buffer) + 38)) : *((int16_t*) ((next_lod->max_buffer) + 38));
        *((int16_t*) ((next_lod->avg_buffer) + 38)) += *((int16_t*) ((this_lod->avg_buffer) + 38)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 5
        *((int16_t*) ((next_lod->min_buffer) + 40)) = *((int16_t*) ((this_lod->min_buffer) + 40)) < *((int16_t*) ((next_lod->min_buffer) + 40)) ? *((int16_t*) ((this_lod->min_buffer) + 40)) : *((int16_t*) ((next_lod->min_buffer) + 40));
        *((int16_t*) ((next_lod->max_buffer) + 40)) = *((int16_t*) ((this_lod->max_buffer) + 40)) > *((int16_t*) ((next_lod->max_buffer) + 40)) ? *((int16_t*) ((this_lod->max_buffer) + 40)) : *((int16_t*) ((next_lod->max_buffer) + 40));
        *((int16_t*) ((next_lod->avg_buffer) + 40)) += *((int16_t*) ((this_lod->avg_buffer) + 40)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 6
        *((int16_t*) ((next_lod->min_buffer) + 42)) = *((int16_t*) ((this_lod->min_buffer) + 42)) < *((int16_t*) ((next_lod->min_buffer) + 42)) ? *((int16_t*) ((this_lod->min_buffer) + 42)) : *((int16_t*) ((next_lod->min_buffer) + 42));
        *((int16_t*) ((next_lod->max_buffer) + 42)) = *((int16_t*) ((this_lod->max_buffer) + 42)) > *((int16_t*) ((next_lod->max_buffer) + 42)) ? *((int16_t*) ((this_lod->max_buffer) + 42)) : *((int16_t*) ((next_lod->max_buffer) + 42));
        *((int16_t*) ((next_lod->avg_buffer) + 42)) += *((int16_t*) ((this_lod->avg_buffer) + 42)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 7
        *((int16_t*) ((next_lod->min_buffer) + 44)) = *((int16_t*) ((this_lod->min_buffer) + 44)) < *((int16_t*) ((next_lod->min_buffer) + 44)) ? *((int16_t*) ((this_lod->min_buffer) + 44)) : *((int16_t*) ((next_lod->min_buffer) + 44));
        *((int16_t*) ((next_lod->max_buffer) + 44)) = *((int16_t*) ((this_lod->max_buffer) + 44)) > *((int16_t*) ((next_lod->max_buffer) + 44)) ? *((int16_t*) ((this_lod->max_buffer) + 44)) : *((int16_t*) ((next_lod->max_buffer) + 44));
        *((int16_t*) ((next_lod->avg_buffer) + 44)) += *((int16_t*) ((this_lod->avg_buffer) + 44)) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 8
        *((int16_t*) ((next_lod->min_buffer) + 46)) = *((int16_t*) ((this_lod->min_buffer) + 46)) < *((int16_t*) ((next_lod->min_buffer) + 46)) ? *((int16_t*) ((this_lod->min_buffer) + 46)) : *((int16_t*) ((next_lod->min_buffer) + 46));
        *((int16_t*) ((next_lod->max_buffer) + 46)) = *((int16_t*) ((this_lod->max_buffer) + 46)) > *((int16_t*) ((next_lod->max_buffer) + 46)) ? *((int16_t*) ((this_lod->max_buffer) + 46)) : *((int16_t*) ((next_lod->max_buffer) + 46));
        *((int16_t*) ((next_lod->avg_buffer) + 46)) += *((int16_t*) ((this_lod->avg_buffer) + 46)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 1
        *((int16_t*) ((next_lod->min_buffer) + 48)) = *((int16_t*) ((this_lod->min_buffer) + 48)) < *((int16_t*) ((next_lod->min_buffer) + 48)) ? *((int16_t*) ((this_lod->min_buffer) + 48)) : *((int16_t*) ((next_lod->min_buffer) + 48));
        *((int16_t*) ((next_lod->max_buffer) + 48)) = *((int16_t*) ((this_lod->max_buffer) + 48)) > *((int16_t*) ((next_lod->max_buffer) + 48)) ? *((int16_t*) ((this_lod->max_buffer) + 48)) : *((int16_t*) ((next_lod->max_buffer) + 48));
        *((int16_t*) ((next_lod->avg_buffer) + 48)) += *((int16_t*) ((this_lod->avg_buffer) + 48)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 2
        *((int16_t*) ((next_lod->min_buffer) + 50)) = *((int16_t*) ((this_lod->min_buffer) + 50)) < *((int16_t*) ((next_lod->min_buffer) + 50)) ? *((int16_t*) ((this_lod->min_buffer) + 50)) : *((int16_t*) ((next_lod->min_buffer) + 50));
        *((int16_t*) ((next_lod->max_buffer) + 50)) = *((int16_t*) ((this_lod->max_buffer) + 50)) > *((int16_t*) ((next_lod->max_buffer) + 50)) ? *((int16_t*) ((this_lod->max_buffer) + 50)) : *((int16_t*) ((next_lod->max_buffer) + 50));
        *((int16_t*) ((next_lod->avg_buffer) + 50)) += *((int16_t*) ((this_lod->avg_buffer) + 50)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 3
        *((int16_t*) ((next_lod->min_buffer) + 52)) = *((int16_t*) ((this_lod->min_buffer) + 52)) < *((int16_t*) ((next_lod->min_buffer) + 52)) ? *((int16_t*) ((this_lod->min_buffer) + 52)) : *((int16_t*) ((next_lod->min_buffer) + 52));
        *((int16_t*) ((next_lod->max_buffer) + 52)) = *((int16_t*) ((this_lod->max_buffer) + 52)) > *((int16_t*) ((next_lod->max_buffer) + 52)) ? *((int16_t*) ((this_lod->max_buffer) + 52)) : *((int16_t*) ((next_lod->max_buffer) + 52));
        *((int16_t*) ((next_lod->avg_buffer) + 52)) += *((int16_t*) ((this_lod->avg_buffer) + 52)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 4
        *((int16_t*) ((next_lod->min_buffer) + 54)) = *((int16_t*) ((this_lod->min_buffer) + 54)) < *((int16_t*) ((next_lod->min_buffer) + 54)) ? *((int16_t*) ((this_lod->min_buffer) + 54)) : *((int16_t*) ((next_lod->min_buffer) + 54));
        *((int16_t*) ((next_lod->max_buffer) + 54)) = *((int16_t*) ((this_lod->max_buffer) + 54)) > *((int16_t*) ((next_lod->max_buffer) + 54)) ? *((int16_t*) ((this_lod->max_buffer) + 54)) : *((int16_t*) ((next_lod->max_buffer) + 54));
        *((int16_t*) ((next_lod->avg_buffer) + 54)) += *((int16_t*) ((this_lod->avg_buffer) + 54)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 5
        *((int16_t*) ((next_lod->min_buffer) + 56)) = *((int16_t*) ((this_lod->min_buffer) + 56)) < *((int16_t*) ((next_lod->min_buffer) + 56)) ? *((int16_t*) ((this_lod->min_buffer) + 56)) : *((int16_t*) ((next_lod->min_buffer) + 56));
        *((int16_t*) ((next_lod->max_buffer) + 56)) = *((int16_t*) ((this_lod->max_buffer) + 56)) > *((int16_t*) ((next_lod->max_buffer) + 56)) ? *((int16_t*) ((this_lod->max_buffer) + 56)) : *((int16_t*) ((next_lod->max_buffer) + 56));
        *((int16_t*) ((next_lod->avg_buffer) + 56)) += *((int16_t*) ((this_lod->avg_buffer) + 56)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 6
        *((int16_t*) ((next_lod->min_buffer) + 58)) = *((int16_t*) ((this_lod->min_buffer) + 58)) < *((int16_t*) ((next_lod->min_buffer) + 58)) ? *((int16_t*) ((this_lod->min_buffer) + 58)) : *((int16_t*) ((next_lod->min_buffer) + 58));
        *((int16_t*) ((next_lod->max_buffer) + 58)) = *((int16_t*) ((this_lod->max_buffer) + 58)) > *((int16_t*) ((next_lod->max_buffer) + 58)) ? *((int16_t*) ((this_lod->max_buffer) + 58)) : *((int16_t*) ((next_lod->max_buffer) + 58));
        *((int16_t*) ((next_lod->avg_buffer) + 58)) += *((int16_t*) ((this_lod->avg_buffer) + 58)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 7
        *((int16_t*) ((next_lod->min_buffer) + 60)) = *((int16_t*) ((this_lod->min_buffer) + 60)) < *((int16_t*) ((next_lod->min_buffer) + 60)) ? *((int16_t*) ((this_lod->min_buffer) + 60)) : *((int16_t*) ((next_lod->min_buffer) + 60));
        *((int16_t*) ((next_lod->max_buffer) + 60)) = *((int16_t*) ((this_lod->max_buffer) + 60)) > *((int16_t*) ((next_lod->max_buffer) + 60)) ? *((int16_t*) ((this_lod->max_buffer) + 60)) : *((int16_t*) ((next_lod->max_buffer) + 60));
        *((int16_t*) ((next_lod->avg_buffer) + 60)) += *((int16_t*) ((this_lod->avg_buffer) + 60)) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 8
        *((int16_t*) ((next_lod->min_buffer) + 62)) = *((int16_t*) ((this_lod->min_buffer) + 62)) < *((int16_t*) ((next_lod->min_buffer) + 62)) ? *((int16_t*) ((this_lod->min_buffer) + 62)) : *((int16_t*) ((next_lod->min_buffer) + 62));
        *((int16_t*) ((next_lod->max_buffer) + 62)) = *((int16_t*) ((this_lod->max_buffer) + 62)) > *((int16_t*) ((next_lod->max_buffer) + 62)) ? *((int16_t*) ((this_lod->max_buffer) + 62)) : *((int16_t*) ((next_lod->max_buffer) + 62));
        *((int16_t*) ((next_lod->avg_buffer) + 62)) += *((int16_t*) ((this_lod->avg_buffer) + 62)) / LOD_SAMPLE_INTERVAL;
        // Dummy -> A
        *((uint64_t*) ((next_lod->min_buffer) + 64)) = 0;
        *((uint64_t*) ((next_lod->max_buffer) + 64)) = 0;
        *((uint64_t*) ((next_lod->avg_buffer) + 64)) = 0;
        // Dummy -> B
        *((uint64_t*) ((next_lod->min_buffer) + 72)) = 0;
        *((uint64_t*) ((next_lod->max_buffer) + 72)) = 0;
        *((uint64_t*) ((next_lod->avg_buffer) + 72)) = 0;
        // Dummy -> C
        *((uint64_t*) ((next_lod->min_buffer) + 80)) = 0;
        *((uint64_t*) ((next_lod->max_buffer) + 80)) = 0;
        *((uint64_t*) ((next_lod->avg_buffer) + 80)) = 0;
        // Dummy -> D
        *((uint64_t*) ((next_lod->min_buffer) + 88)) = 0;
        *((uint64_t*) ((next_lod->max_buffer) + 88)) = 0;
        *((uint64_t*) ((next_lod->avg_buffer) + 88)) = 0;
        // Dummy -> W
        *((uint8_t*) ((next_lod->min_buffer) + 96)) = 0;
        *((uint8_t*) ((next_lod->max_buffer) + 96)) = 0;
        *((uint8_t*) ((next_lod->avg_buffer) + 96)) = 0;
        // Dummy -> X
        *((uint8_t*) ((next_lod->min_buffer) + 97)) = 0;
        *((uint8_t*) ((next_lod->max_buffer) + 97)) = 0;
        *((uint8_t*) ((next_lod->avg_buffer) + 97)) = 0;
        // Diagnostics -> Error Count
        *((uint8_t*) ((next_lod->min_buffer) + 98)) = *((uint8_t*) ((this_lod->min_buffer) + 98)) < *((uint8_t*) ((next_lod->min_buffer) + 98)) ? *((uint8_t*) ((this_lod->min_buffer) + 98)) : *((uint8_t*) ((next_lod->min_buffer) + 98));
        *((uint8_t*) ((next_lod->max_buffer) + 98)) = *((uint8_t*) ((this_lod->max_buffer) + 98)) > *((uint8_t*) ((next_lod->max_buffer) + 98)) ? *((uint8_t*) ((this_lod->max_buffer) + 98)) : *((uint8_t*) ((next_lod->max_buffer) + 98));
        *((uint8_t*) ((next_lod->avg_buffer) + 98)) += *((uint8_t*) ((this_lod->avg_buffer) + 98)) / LOD_SAMPLE_INTERVAL;
        // Diagnostics -> Last Error Cause
        *((uint8_t*) ((next_lod->min_buffer) + 99)) = *((uint8_t*) ((this_lod->min_buffer) + 99));
        *((uint8_t*) ((next_lod->max_buffer) + 99)) = *((uint8_t*) ((this_lod->max_buffer) + 99));
        *((uint8_t*) ((next_lod->avg_buffer) + 99)) += *((uint8_t*) ((this_lod->avg_buffer) + 99));

        next_lod->progress += 1;
        if (next_lod->progress == LOD_SAMPLE_INTERVAL) {
            commit_lod(lod_index + 1);
        }
    }
    // Write new values to the file buffer.
    memcpy(
        &this_lod->file_buffer[this_lod->fbuf_write_index],
        this_lod->min_buffer,
        FRAME_SIZE
    );
    memcpy(
        &this_lod->file_buffer[this_lod->fbuf_write_index + FRAME_SIZE],
        this_lod->max_buffer,
        FRAME_SIZE
    );
    memcpy(
        &this_lod->file_buffer[this_lod->fbuf_write_index + 2 * FRAME_SIZE],
        this_lod->avg_buffer,
        FRAME_SIZE
    );
    this_lod->fbuf_write_index = (this_lod->fbuf_write_index + 3 * FRAME_SIZE) % FILE_BUFFER_SIZE;
    // Reset the buffer to a state where new values can be written to it.
    reset_lod_buffer(lod_index);
}

void update_lods() {
    // Update the first LOD with the new data...
    volatile char *incoming_data = &primary_file_buffer[pbuf_write_index];
    // ADC 1 -> Channel 1
    *((int16_t*) ((lod_infos[0].min_buffer) + 0)) = *((int16_t*) ((incoming_data) + 0)) < *((int16_t*) ((lod_infos[0].min_buffer) + 0)) ? *((int16_t*) ((incoming_data) + 0)) : *((int16_t*) ((lod_infos[0].min_buffer) + 0));
    *((int16_t*) ((lod_infos[0].max_buffer) + 0)) = *((int16_t*) ((incoming_data) + 0)) > *((int16_t*) ((lod_infos[0].max_buffer) + 0)) ? *((int16_t*) ((incoming_data) + 0)) : *((int16_t*) ((lod_infos[0].max_buffer) + 0));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 0)) += *((int16_t*) ((incoming_data) + 0)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 2
    *((int16_t*) ((lod_infos[0].min_buffer) + 2)) = *((int16_t*) ((incoming_data) + 2)) < *((int16_t*) ((lod_infos[0].min_buffer) + 2)) ? *((int16_t*) ((incoming_data) + 2)) : *((int16_t*) ((lod_infos[0].min_buffer) + 2));
    *((int16_t*) ((lod_infos[0].max_buffer) + 2)) = *((int16_t*) ((incoming_data) + 2)) > *((int16_t*) ((lod_infos[0].max_buffer) + 2)) ? *((int16_t*) ((incoming_data) + 2)) : *((int16_t*) ((lod_infos[0].max_buffer) + 2));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 2)) += *((int16_t*) ((incoming_data) + 2)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 3
    *((int16_t*) ((lod_infos[0].min_buffer) + 4)) = *((int16_t*) ((incoming_data) + 4)) < *((int16_t*) ((lod_infos[0].min_buffer) + 4)) ? *((int16_t*) ((incoming_data) + 4)) : *((int16_t*) ((lod_infos[0].min_buffer) + 4));
    *((int16_t*) ((lod_infos[0].max_buffer) + 4)) = *((int16_t*) ((incoming_data) + 4)) > *((int16_t*) ((lod_infos[0].max_buffer) + 4)) ? *((int16_t*) ((incoming_data) + 4)) : *((int16_t*) ((lod_infos[0].max_buffer) + 4));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 4)) += *((int16_t*) ((incoming_data) + 4)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 4
    *((int16_t*) ((lod_infos[0].min_buffer) + 6)) = *((int16_t*) ((incoming_data) + 6)) < *((int16_t*) ((lod_infos[0].min_buffer) + 6)) ? *((int16_t*) ((incoming_data) + 6)) : *((int16_t*) ((lod_infos[0].min_buffer) + 6));
    *((int16_t*) ((lod_infos[0].max_buffer) + 6)) = *((int16_t*) ((incoming_data) + 6)) > *((int16_t*) ((lod_infos[0].max_buffer) + 6)) ? *((int16_t*) ((incoming_data) + 6)) : *((int16_t*) ((lod_infos[0].max_buffer) + 6));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 6)) += *((int16_t*) ((incoming_data) + 6)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 5
    *((int16_t*) ((lod_infos[0].min_buffer) + 8)) = *((int16_t*) ((incoming_data) + 8)) < *((int16_t*) ((lod_infos[0].min_buffer) + 8)) ? *((int16_t*) ((incoming_data) + 8)) : *((int16_t*) ((lod_infos[0].min_buffer) + 8));
    *((int16_t*) ((lod_infos[0].max_buffer) + 8)) = *((int16_t*) ((incoming_data) + 8)) > *((int16_t*) ((lod_infos[0].max_buffer) + 8)) ? *((int16_t*) ((incoming_data) + 8)) : *((int16_t*) ((lod_infos[0].max_buffer) + 8));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 8)) += *((int16_t*) ((incoming_data) + 8)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 6
    *((int16_t*) ((lod_infos[0].min_buffer) + 10)) = *((int16_t*) ((incoming_data) + 10)) < *((int16_t*) ((lod_infos[0].min_buffer) + 10)) ? *((int16_t*) ((incoming_data) + 10)) : *((int16_t*) ((lod_infos[0].min_buffer) + 10));
    *((int16_t*) ((lod_infos[0].max_buffer) + 10)) = *((int16_t*) ((incoming_data) + 10)) > *((int16_t*) ((lod_infos[0].max_buffer) + 10)) ? *((int16_t*) ((incoming_data) + 10)) : *((int16_t*) ((lod_infos[0].max_buffer) + 10));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 10)) += *((int16_t*) ((incoming_data) + 10)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 7
    *((int16_t*) ((lod_infos[0].min_buffer) + 12)) = *((int16_t*) ((incoming_data) + 12)) < *((int16_t*) ((lod_infos[0].min_buffer) + 12)) ? *((int16_t*) ((incoming_data) + 12)) : *((int16_t*) ((lod_infos[0].min_buffer) + 12));
    *((int16_t*) ((lod_infos[0].max_buffer) + 12)) = *((int16_t*) ((incoming_data) + 12)) > *((int16_t*) ((lod_infos[0].max_buffer) + 12)) ? *((int16_t*) ((incoming_data) + 12)) : *((int16_t*) ((lod_infos[0].max_buffer) + 12));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 12)) += *((int16_t*) ((incoming_data) + 12)) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 8
    *((int16_t*) ((lod_infos[0].min_buffer) + 14)) = *((int16_t*) ((incoming_data) + 14)) < *((int16_t*) ((lod_infos[0].min_buffer) + 14)) ? *((int16_t*) ((incoming_data) + 14)) : *((int16_t*) ((lod_infos[0].min_buffer) + 14));
    *((int16_t*) ((lod_infos[0].max_buffer) + 14)) = *((int16_t*) ((incoming_data) + 14)) > *((int16_t*) ((lod_infos[0].max_buffer) + 14)) ? *((int16_t*) ((incoming_data) + 14)) : *((int16_t*) ((lod_infos[0].max_buffer) + 14));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 14)) += *((int16_t*) ((incoming_data) + 14)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 1
    *((int16_t*) ((lod_infos[0].min_buffer) + 16)) = *((int16_t*) ((incoming_data) + 16)) < *((int16_t*) ((lod_infos[0].min_buffer) + 16)) ? *((int16_t*) ((incoming_data) + 16)) : *((int16_t*) ((lod_infos[0].min_buffer) + 16));
    *((int16_t*) ((lod_infos[0].max_buffer) + 16)) = *((int16_t*) ((incoming_data) + 16)) > *((int16_t*) ((lod_infos[0].max_buffer) + 16)) ? *((int16_t*) ((incoming_data) + 16)) : *((int16_t*) ((lod_infos[0].max_buffer) + 16));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 16)) += *((int16_t*) ((incoming_data) + 16)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 2
    *((int16_t*) ((lod_infos[0].min_buffer) + 18)) = *((int16_t*) ((incoming_data) + 18)) < *((int16_t*) ((lod_infos[0].min_buffer) + 18)) ? *((int16_t*) ((incoming_data) + 18)) : *((int16_t*) ((lod_infos[0].min_buffer) + 18));
    *((int16_t*) ((lod_infos[0].max_buffer) + 18)) = *((int16_t*) ((incoming_data) + 18)) > *((int16_t*) ((lod_infos[0].max_buffer) + 18)) ? *((int16_t*) ((incoming_data) + 18)) : *((int16_t*) ((lod_infos[0].max_buffer) + 18));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 18)) += *((int16_t*) ((incoming_data) + 18)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 3
    *((int16_t*) ((lod_infos[0].min_buffer) + 20)) = *((int16_t*) ((incoming_data) + 20)) < *((int16_t*) ((lod_infos[0].min_buffer) + 20)) ? *((int16_t*) ((incoming_data) + 20)) : *((int16_t*) ((lod_infos[0].min_buffer) + 20));
    *((int16_t*) ((lod_infos[0].max_buffer) + 20)) = *((int16_t*) ((incoming_data) + 20)) > *((int16_t*) ((lod_infos[0].max_buffer) + 20)) ? *((int16_t*) ((incoming_data) + 20)) : *((int16_t*) ((lod_infos[0].max_buffer) + 20));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 20)) += *((int16_t*) ((incoming_data) + 20)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 4
    *((int16_t*) ((lod_infos[0].min_buffer) + 22)) = *((int16_t*) ((incoming_data) + 22)) < *((int16_t*) ((lod_infos[0].min_buffer) + 22)) ? *((int16_t*) ((incoming_data) + 22)) : *((int16_t*) ((lod_infos[0].min_buffer) + 22));
    *((int16_t*) ((lod_infos[0].max_buffer) + 22)) = *((int16_t*) ((incoming_data) + 22)) > *((int16_t*) ((lod_infos[0].max_buffer) + 22)) ? *((int16_t*) ((incoming_data) + 22)) : *((int16_t*) ((lod_infos[0].max_buffer) + 22));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 22)) += *((int16_t*) ((incoming_data) + 22)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 5
    *((int16_t*) ((lod_infos[0].min_buffer) + 24)) = *((int16_t*) ((incoming_data) + 24)) < *((int16_t*) ((lod_infos[0].min_buffer) + 24)) ? *((int16_t*) ((incoming_data) + 24)) : *((int16_t*) ((lod_infos[0].min_buffer) + 24));
    *((int16_t*) ((lod_infos[0].max_buffer) + 24)) = *((int16_t*) ((incoming_data) + 24)) > *((int16_t*) ((lod_infos[0].max_buffer) + 24)) ? *((int16_t*) ((incoming_data) + 24)) : *((int16_t*) ((lod_infos[0].max_buffer) + 24));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 24)) += *((int16_t*) ((incoming_data) + 24)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 6
    *((int16_t*) ((lod_infos[0].min_buffer) + 26)) = *((int16_t*) ((incoming_data) + 26)) < *((int16_t*) ((lod_infos[0].min_buffer) + 26)) ? *((int16_t*) ((incoming_data) + 26)) : *((int16_t*) ((lod_infos[0].min_buffer) + 26));
    *((int16_t*) ((lod_infos[0].max_buffer) + 26)) = *((int16_t*) ((incoming_data) + 26)) > *((int16_t*) ((lod_infos[0].max_buffer) + 26)) ? *((int16_t*) ((incoming_data) + 26)) : *((int16_t*) ((lod_infos[0].max_buffer) + 26));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 26)) += *((int16_t*) ((incoming_data) + 26)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 7
    *((int16_t*) ((lod_infos[0].min_buffer) + 28)) = *((int16_t*) ((incoming_data) + 28)) < *((int16_t*) ((lod_infos[0].min_buffer) + 28)) ? *((int16_t*) ((incoming_data) + 28)) : *((int16_t*) ((lod_infos[0].min_buffer) + 28));
    *((int16_t*) ((lod_infos[0].max_buffer) + 28)) = *((int16_t*) ((incoming_data) + 28)) > *((int16_t*) ((lod_infos[0].max_buffer) + 28)) ? *((int16_t*) ((incoming_data) + 28)) : *((int16_t*) ((lod_infos[0].max_buffer) + 28));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 28)) += *((int16_t*) ((incoming_data) + 28)) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 8
    *((int16_t*) ((lod_infos[0].min_buffer) + 30)) = *((int16_t*) ((incoming_data) + 30)) < *((int16_t*) ((lod_infos[0].min_buffer) + 30)) ? *((int16_t*) ((incoming_data) + 30)) : *((int16_t*) ((lod_infos[0].min_buffer) + 30));
    *((int16_t*) ((lod_infos[0].max_buffer) + 30)) = *((int16_t*) ((incoming_data) + 30)) > *((int16_t*) ((lod_infos[0].max_buffer) + 30)) ? *((int16_t*) ((incoming_data) + 30)) : *((int16_t*) ((lod_infos[0].max_buffer) + 30));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 30)) += *((int16_t*) ((incoming_data) + 30)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 1
    *((int16_t*) ((lod_infos[0].min_buffer) + 32)) = *((int16_t*) ((incoming_data) + 32)) < *((int16_t*) ((lod_infos[0].min_buffer) + 32)) ? *((int16_t*) ((incoming_data) + 32)) : *((int16_t*) ((lod_infos[0].min_buffer) + 32));
    *((int16_t*) ((lod_infos[0].max_buffer) + 32)) = *((int16_t*) ((incoming_data) + 32)) > *((int16_t*) ((lod_infos[0].max_buffer) + 32)) ? *((int16_t*) ((incoming_data) + 32)) : *((int16_t*) ((lod_infos[0].max_buffer) + 32));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 32)) += *((int16_t*) ((incoming_data) + 32)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 2
    *((int16_t*) ((lod_infos[0].min_buffer) + 34)) = *((int16_t*) ((incoming_data) + 34)) < *((int16_t*) ((lod_infos[0].min_buffer) + 34)) ? *((int16_t*) ((incoming_data) + 34)) : *((int16_t*) ((lod_infos[0].min_buffer) + 34));
    *((int16_t*) ((lod_infos[0].max_buffer) + 34)) = *((int16_t*) ((incoming_data) + 34)) > *((int16_t*) ((lod_infos[0].max_buffer) + 34)) ? *((int16_t*) ((incoming_data) + 34)) : *((int16_t*) ((lod_infos[0].max_buffer) + 34));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 34)) += *((int16_t*) ((incoming_data) + 34)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 3
    *((int16_t*) ((lod_infos[0].min_buffer) + 36)) = *((int16_t*) ((incoming_data) + 36)) < *((int16_t*) ((lod_infos[0].min_buffer) + 36)) ? *((int16_t*) ((incoming_data) + 36)) : *((int16_t*) ((lod_infos[0].min_buffer) + 36));
    *((int16_t*) ((lod_infos[0].max_buffer) + 36)) = *((int16_t*) ((incoming_data) + 36)) > *((int16_t*) ((lod_infos[0].max_buffer) + 36)) ? *((int16_t*) ((incoming_data) + 36)) : *((int16_t*) ((lod_infos[0].max_buffer) + 36));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 36)) += *((int16_t*) ((incoming_data) + 36)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 4
    *((int16_t*) ((lod_infos[0].min_buffer) + 38)) = *((int16_t*) ((incoming_data) + 38)) < *((int16_t*) ((lod_infos[0].min_buffer) + 38)) ? *((int16_t*) ((incoming_data) + 38)) : *((int16_t*) ((lod_infos[0].min_buffer) + 38));
    *((int16_t*) ((lod_infos[0].max_buffer) + 38)) = *((int16_t*) ((incoming_data) + 38)) > *((int16_t*) ((lod_infos[0].max_buffer) + 38)) ? *((int16_t*) ((incoming_data) + 38)) : *((int16_t*) ((lod_infos[0].max_buffer) + 38));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 38)) += *((int16_t*) ((incoming_data) + 38)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 5
    *((int16_t*) ((lod_infos[0].min_buffer) + 40)) = *((int16_t*) ((incoming_data) + 40)) < *((int16_t*) ((lod_infos[0].min_buffer) + 40)) ? *((int16_t*) ((incoming_data) + 40)) : *((int16_t*) ((lod_infos[0].min_buffer) + 40));
    *((int16_t*) ((lod_infos[0].max_buffer) + 40)) = *((int16_t*) ((incoming_data) + 40)) > *((int16_t*) ((lod_infos[0].max_buffer) + 40)) ? *((int16_t*) ((incoming_data) + 40)) : *((int16_t*) ((lod_infos[0].max_buffer) + 40));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 40)) += *((int16_t*) ((incoming_data) + 40)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 6
    *((int16_t*) ((lod_infos[0].min_buffer) + 42)) = *((int16_t*) ((incoming_data) + 42)) < *((int16_t*) ((lod_infos[0].min_buffer) + 42)) ? *((int16_t*) ((incoming_data) + 42)) : *((int16_t*) ((lod_infos[0].min_buffer) + 42));
    *((int16_t*) ((lod_infos[0].max_buffer) + 42)) = *((int16_t*) ((incoming_data) + 42)) > *((int16_t*) ((lod_infos[0].max_buffer) + 42)) ? *((int16_t*) ((incoming_data) + 42)) : *((int16_t*) ((lod_infos[0].max_buffer) + 42));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 42)) += *((int16_t*) ((incoming_data) + 42)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 7
    *((int16_t*) ((lod_infos[0].min_buffer) + 44)) = *((int16_t*) ((incoming_data) + 44)) < *((int16_t*) ((lod_infos[0].min_buffer) + 44)) ? *((int16_t*) ((incoming_data) + 44)) : *((int16_t*) ((lod_infos[0].min_buffer) + 44));
    *((int16_t*) ((lod_infos[0].max_buffer) + 44)) = *((int16_t*) ((incoming_data) + 44)) > *((int16_t*) ((lod_infos[0].max_buffer) + 44)) ? *((int16_t*) ((incoming_data) + 44)) : *((int16_t*) ((lod_infos[0].max_buffer) + 44));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 44)) += *((int16_t*) ((incoming_data) + 44)) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 8
    *((int16_t*) ((lod_infos[0].min_buffer) + 46)) = *((int16_t*) ((incoming_data) + 46)) < *((int16_t*) ((lod_infos[0].min_buffer) + 46)) ? *((int16_t*) ((incoming_data) + 46)) : *((int16_t*) ((lod_infos[0].min_buffer) + 46));
    *((int16_t*) ((lod_infos[0].max_buffer) + 46)) = *((int16_t*) ((incoming_data) + 46)) > *((int16_t*) ((lod_infos[0].max_buffer) + 46)) ? *((int16_t*) ((incoming_data) + 46)) : *((int16_t*) ((lod_infos[0].max_buffer) + 46));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 46)) += *((int16_t*) ((incoming_data) + 46)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 1
    *((int16_t*) ((lod_infos[0].min_buffer) + 48)) = *((int16_t*) ((incoming_data) + 48)) < *((int16_t*) ((lod_infos[0].min_buffer) + 48)) ? *((int16_t*) ((incoming_data) + 48)) : *((int16_t*) ((lod_infos[0].min_buffer) + 48));
    *((int16_t*) ((lod_infos[0].max_buffer) + 48)) = *((int16_t*) ((incoming_data) + 48)) > *((int16_t*) ((lod_infos[0].max_buffer) + 48)) ? *((int16_t*) ((incoming_data) + 48)) : *((int16_t*) ((lod_infos[0].max_buffer) + 48));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 48)) += *((int16_t*) ((incoming_data) + 48)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 2
    *((int16_t*) ((lod_infos[0].min_buffer) + 50)) = *((int16_t*) ((incoming_data) + 50)) < *((int16_t*) ((lod_infos[0].min_buffer) + 50)) ? *((int16_t*) ((incoming_data) + 50)) : *((int16_t*) ((lod_infos[0].min_buffer) + 50));
    *((int16_t*) ((lod_infos[0].max_buffer) + 50)) = *((int16_t*) ((incoming_data) + 50)) > *((int16_t*) ((lod_infos[0].max_buffer) + 50)) ? *((int16_t*) ((incoming_data) + 50)) : *((int16_t*) ((lod_infos[0].max_buffer) + 50));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 50)) += *((int16_t*) ((incoming_data) + 50)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 3
    *((int16_t*) ((lod_infos[0].min_buffer) + 52)) = *((int16_t*) ((incoming_data) + 52)) < *((int16_t*) ((lod_infos[0].min_buffer) + 52)) ? *((int16_t*) ((incoming_data) + 52)) : *((int16_t*) ((lod_infos[0].min_buffer) + 52));
    *((int16_t*) ((lod_infos[0].max_buffer) + 52)) = *((int16_t*) ((incoming_data) + 52)) > *((int16_t*) ((lod_infos[0].max_buffer) + 52)) ? *((int16_t*) ((incoming_data) + 52)) : *((int16_t*) ((lod_infos[0].max_buffer) + 52));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 52)) += *((int16_t*) ((incoming_data) + 52)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 4
    *((int16_t*) ((lod_infos[0].min_buffer) + 54)) = *((int16_t*) ((incoming_data) + 54)) < *((int16_t*) ((lod_infos[0].min_buffer) + 54)) ? *((int16_t*) ((incoming_data) + 54)) : *((int16_t*) ((lod_infos[0].min_buffer) + 54));
    *((int16_t*) ((lod_infos[0].max_buffer) + 54)) = *((int16_t*) ((incoming_data) + 54)) > *((int16_t*) ((lod_infos[0].max_buffer) + 54)) ? *((int16_t*) ((incoming_data) + 54)) : *((int16_t*) ((lod_infos[0].max_buffer) + 54));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 54)) += *((int16_t*) ((incoming_data) + 54)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 5
    *((int16_t*) ((lod_infos[0].min_buffer) + 56)) = *((int16_t*) ((incoming_data) + 56)) < *((int16_t*) ((lod_infos[0].min_buffer) + 56)) ? *((int16_t*) ((incoming_data) + 56)) : *((int16_t*) ((lod_infos[0].min_buffer) + 56));
    *((int16_t*) ((lod_infos[0].max_buffer) + 56)) = *((int16_t*) ((incoming_data) + 56)) > *((int16_t*) ((lod_infos[0].max_buffer) + 56)) ? *((int16_t*) ((incoming_data) + 56)) : *((int16_t*) ((lod_infos[0].max_buffer) + 56));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 56)) += *((int16_t*) ((incoming_data) + 56)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 6
    *((int16_t*) ((lod_infos[0].min_buffer) + 58)) = *((int16_t*) ((incoming_data) + 58)) < *((int16_t*) ((lod_infos[0].min_buffer) + 58)) ? *((int16_t*) ((incoming_data) + 58)) : *((int16_t*) ((lod_infos[0].min_buffer) + 58));
    *((int16_t*) ((lod_infos[0].max_buffer) + 58)) = *((int16_t*) ((incoming_data) + 58)) > *((int16_t*) ((lod_infos[0].max_buffer) + 58)) ? *((int16_t*) ((incoming_data) + 58)) : *((int16_t*) ((lod_infos[0].max_buffer) + 58));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 58)) += *((int16_t*) ((incoming_data) + 58)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 7
    *((int16_t*) ((lod_infos[0].min_buffer) + 60)) = *((int16_t*) ((incoming_data) + 60)) < *((int16_t*) ((lod_infos[0].min_buffer) + 60)) ? *((int16_t*) ((incoming_data) + 60)) : *((int16_t*) ((lod_infos[0].min_buffer) + 60));
    *((int16_t*) ((lod_infos[0].max_buffer) + 60)) = *((int16_t*) ((incoming_data) + 60)) > *((int16_t*) ((lod_infos[0].max_buffer) + 60)) ? *((int16_t*) ((incoming_data) + 60)) : *((int16_t*) ((lod_infos[0].max_buffer) + 60));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 60)) += *((int16_t*) ((incoming_data) + 60)) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 8
    *((int16_t*) ((lod_infos[0].min_buffer) + 62)) = *((int16_t*) ((incoming_data) + 62)) < *((int16_t*) ((lod_infos[0].min_buffer) + 62)) ? *((int16_t*) ((incoming_data) + 62)) : *((int16_t*) ((lod_infos[0].min_buffer) + 62));
    *((int16_t*) ((lod_infos[0].max_buffer) + 62)) = *((int16_t*) ((incoming_data) + 62)) > *((int16_t*) ((lod_infos[0].max_buffer) + 62)) ? *((int16_t*) ((incoming_data) + 62)) : *((int16_t*) ((lod_infos[0].max_buffer) + 62));
    *((int16_t*) ((lod_infos[0].avg_buffer) + 62)) += *((int16_t*) ((incoming_data) + 62)) / LOD_SAMPLE_INTERVAL;
    // Dummy -> A
    *((uint64_t*) ((lod_infos[0].min_buffer) + 64)) = 0;
    *((uint64_t*) ((lod_infos[0].max_buffer) + 64)) = 0;
    *((uint64_t*) ((lod_infos[0].avg_buffer) + 64)) = 0;
    // Dummy -> B
    *((uint64_t*) ((lod_infos[0].min_buffer) + 72)) = 0;
    *((uint64_t*) ((lod_infos[0].max_buffer) + 72)) = 0;
    *((uint64_t*) ((lod_infos[0].avg_buffer) + 72)) = 0;
    // Dummy -> C
    *((uint64_t*) ((lod_infos[0].min_buffer) + 80)) = 0;
    *((uint64_t*) ((lod_infos[0].max_buffer) + 80)) = 0;
    *((uint64_t*) ((lod_infos[0].avg_buffer) + 80)) = 0;
    // Dummy -> D
    *((uint64_t*) ((lod_infos[0].min_buffer) + 88)) = 0;
    *((uint64_t*) ((lod_infos[0].max_buffer) + 88)) = 0;
    *((uint64_t*) ((lod_infos[0].avg_buffer) + 88)) = 0;
    // Dummy -> W
    *((uint8_t*) ((lod_infos[0].min_buffer) + 96)) = 0;
    *((uint8_t*) ((lod_infos[0].max_buffer) + 96)) = 0;
    *((uint8_t*) ((lod_infos[0].avg_buffer) + 96)) = 0;
    // Dummy -> X
    *((uint8_t*) ((lod_infos[0].min_buffer) + 97)) = 0;
    *((uint8_t*) ((lod_infos[0].max_buffer) + 97)) = 0;
    *((uint8_t*) ((lod_infos[0].avg_buffer) + 97)) = 0;
    // Diagnostics -> Error Count
    *((uint8_t*) ((lod_infos[0].min_buffer) + 98)) = *((uint8_t*) ((incoming_data) + 98)) < *((uint8_t*) ((lod_infos[0].min_buffer) + 98)) ? *((uint8_t*) ((incoming_data) + 98)) : *((uint8_t*) ((lod_infos[0].min_buffer) + 98));
    *((uint8_t*) ((lod_infos[0].max_buffer) + 98)) = *((uint8_t*) ((incoming_data) + 98)) > *((uint8_t*) ((lod_infos[0].max_buffer) + 98)) ? *((uint8_t*) ((incoming_data) + 98)) : *((uint8_t*) ((lod_infos[0].max_buffer) + 98));
    *((uint8_t*) ((lod_infos[0].avg_buffer) + 98)) += *((uint8_t*) ((incoming_data) + 98)) / LOD_SAMPLE_INTERVAL;
    // Diagnostics -> Last Error Cause
    *((uint8_t*) ((lod_infos[0].min_buffer) + 99)) = *((uint8_t*) ((incoming_data) + 99));
    *((uint8_t*) ((lod_infos[0].max_buffer) + 99)) = *((uint8_t*) ((incoming_data) + 99));
    *((uint8_t*) ((lod_infos[0].avg_buffer) + 99)) += *((uint8_t*) ((incoming_data) + 99));

    lod_infos[0].progress += 1;
    // If we have written enough samples to the first LOD...
    if (lod_infos[0].progress == LOD_SAMPLE_INTERVAL) {
        // Save the parsed_formatrmation and propogate it up to higher LODs
        // as necessary.
        commit_lod(0);
    }
}
