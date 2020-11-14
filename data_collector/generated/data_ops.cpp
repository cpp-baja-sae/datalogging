// Do not make changes to this file, it was auto-generated based on the contents
// of ./data_format.json. You may instead change that file
// and then run ./generate_code.py to update the contents of this file.

#include <stdint.h>
#include <string.h>

// Resets an LOD buffer as if it had never had any data written to it.
void resetLodBuffer(int lodIndex) {
    lodBuffers[lodIndex].progress = 0;
    // ADC 1 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 0) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 0) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 0) = 0;
    // ADC 1 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 2) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 2) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 2) = 0;
    // ADC 1 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 4) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 4) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 4) = 0;
    // ADC 1 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 6) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 6) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 6) = 0;
    // ADC 1 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 8) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 8) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 8) = 0;
    // ADC 1 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 10) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 10) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 10) = 0;
    // ADC 1 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 12) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 12) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 12) = 0;
    // ADC 1 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 14) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 14) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 14) = 0;
    // ADC 2 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 16) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 16) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 16) = 0;
    // ADC 2 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 18) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 18) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 18) = 0;
    // ADC 2 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 20) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 20) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 20) = 0;
    // ADC 2 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 22) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 22) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 22) = 0;
    // ADC 2 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 24) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 24) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 24) = 0;
    // ADC 2 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 26) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 26) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 26) = 0;
    // ADC 2 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 28) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 28) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 28) = 0;
    // ADC 2 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 30) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 30) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 30) = 0;
    // ADC 3 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 32) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 32) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 32) = 0;
    // ADC 3 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 34) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 34) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 34) = 0;
    // ADC 3 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 36) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 36) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 36) = 0;
    // ADC 3 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 38) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 38) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 38) = 0;
    // ADC 3 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 40) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 40) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 40) = 0;
    // ADC 3 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 42) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 42) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 42) = 0;
    // ADC 3 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 44) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 44) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 44) = 0;
    // ADC 3 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 46) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 46) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 46) = 0;
    // ADC 4 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 48) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 48) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 48) = 0;
    // ADC 4 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 50) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 50) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 50) = 0;
    // ADC 4 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 52) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 52) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 52) = 0;
    // ADC 4 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 54) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 54) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 54) = 0;
    // ADC 4 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 56) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 56) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 56) = 0;
    // ADC 4 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 58) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 58) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 58) = 0;
    // ADC 4 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 60) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 60) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 60) = 0;
    // ADC 4 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].minBuffer + 62) = 0x7FFF;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].maxBuffer + 62) = -0x8000;
    *reinterpret_cast<int16_t*>(lodBuffers[lodIndex].avgBuffer + 62) = 0;
    // Dummy -> A
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].minBuffer + 64) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].maxBuffer + 64) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].avgBuffer + 64) = 0;
    // Dummy -> B
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].minBuffer + 72) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].maxBuffer + 72) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].avgBuffer + 72) = 0;
    // Dummy -> C
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].minBuffer + 80) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].maxBuffer + 80) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].avgBuffer + 80) = 0;
    // Dummy -> D
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].minBuffer + 88) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].maxBuffer + 88) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[lodIndex].avgBuffer + 88) = 0;
    // Dummy -> W
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].minBuffer + 96) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].maxBuffer + 96) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].avgBuffer + 96) = 0;
    // Dummy -> X
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].minBuffer + 97) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].maxBuffer + 97) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].avgBuffer + 97) = 0;
    // Diagnostics -> Error Count
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].minBuffer + 98) = 0xFF;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].maxBuffer + 98) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].avgBuffer + 98) = 0;
    // Diagnostics -> Last Error Cause
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].minBuffer + 99) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].maxBuffer + 99) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[lodIndex].avgBuffer + 99) = 0;

}

// Called when an LOD buffer becomes full. It propogates the recorded values
// to the next highest LOD (if one exists), saves the contents into the 
// appropriate file buffer, and clears the original buffer. so that more 
// data can be written to it.
void commitLod(int lodIndex) {
    LodBuffer *thisLod = &lodBuffers[lodIndex];
    // If this is not the highest-level LOD, then update the next LOD's min, max, and avg.
    if (lodIndex < NUM_LOW_RES_LODS - 1) {
        LodBuffer *nextLod = &lodBuffers[lodIndex + 1];
        // ADC 1 -> Channel 1
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 0) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 0) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 0) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 0) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 0);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 0) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 0) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 0) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 0) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 0);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 0) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 0) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 2
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 2) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 2) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 2) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 2) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 2);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 2) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 2) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 2) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 2) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 2);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 2) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 2) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 3
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 4) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 4) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 4) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 4) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 4);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 4) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 4) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 4) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 4) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 4);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 4) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 4) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 4
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 6) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 6) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 6) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 6) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 6);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 6) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 6) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 6) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 6) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 6);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 6) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 6) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 5
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 8) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 8) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 8) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 8) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 8);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 8) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 8) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 8) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 8) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 8);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 8) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 8) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 6
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 10) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 10) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 10) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 10) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 10);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 10) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 10) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 10) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 10) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 10);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 10) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 10) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 7
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 12) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 12) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 12) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 12) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 12);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 12) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 12) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 12) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 12) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 12);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 12) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 12) / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 8
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 14) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 14) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 14) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 14) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 14);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 14) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 14) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 14) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 14) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 14);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 14) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 14) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 1
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 16) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 16) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 16) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 16) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 16);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 16) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 16) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 16) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 16) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 16);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 16) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 16) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 2
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 18) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 18) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 18) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 18) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 18);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 18) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 18) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 18) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 18) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 18);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 18) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 18) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 3
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 20) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 20) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 20) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 20) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 20);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 20) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 20) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 20) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 20) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 20);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 20) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 20) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 4
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 22) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 22) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 22) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 22) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 22);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 22) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 22) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 22) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 22) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 22);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 22) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 22) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 5
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 24) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 24) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 24) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 24) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 24);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 24) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 24) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 24) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 24) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 24);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 24) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 24) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 6
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 26) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 26) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 26) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 26) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 26);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 26) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 26) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 26) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 26) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 26);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 26) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 26) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 7
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 28) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 28) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 28) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 28) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 28);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 28) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 28) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 28) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 28) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 28);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 28) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 28) / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 8
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 30) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 30) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 30) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 30) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 30);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 30) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 30) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 30) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 30) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 30);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 30) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 30) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 1
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 32) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 32) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 32) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 32) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 32);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 32) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 32) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 32) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 32) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 32);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 32) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 32) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 2
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 34) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 34) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 34) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 34) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 34);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 34) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 34) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 34) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 34) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 34);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 34) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 34) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 3
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 36) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 36) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 36) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 36) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 36);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 36) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 36) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 36) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 36) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 36);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 36) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 36) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 4
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 38) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 38) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 38) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 38) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 38);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 38) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 38) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 38) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 38) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 38);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 38) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 38) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 5
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 40) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 40) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 40) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 40) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 40);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 40) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 40) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 40) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 40) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 40);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 40) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 40) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 6
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 42) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 42) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 42) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 42) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 42);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 42) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 42) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 42) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 42) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 42);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 42) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 42) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 7
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 44) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 44) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 44) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 44) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 44);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 44) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 44) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 44) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 44) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 44);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 44) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 44) / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 8
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 46) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 46) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 46) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 46) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 46);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 46) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 46) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 46) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 46) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 46);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 46) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 46) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 1
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 48) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 48) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 48) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 48) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 48);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 48) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 48) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 48) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 48) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 48);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 48) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 48) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 2
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 50) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 50) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 50) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 50) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 50);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 50) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 50) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 50) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 50) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 50);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 50) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 50) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 3
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 52) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 52) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 52) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 52) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 52);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 52) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 52) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 52) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 52) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 52);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 52) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 52) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 4
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 54) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 54) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 54) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 54) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 54);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 54) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 54) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 54) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 54) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 54);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 54) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 54) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 5
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 56) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 56) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 56) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 56) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 56);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 56) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 56) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 56) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 56) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 56);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 56) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 56) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 6
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 58) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 58) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 58) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 58) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 58);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 58) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 58) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 58) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 58) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 58);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 58) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 58) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 7
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 60) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 60) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 60) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 60) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 60);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 60) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 60) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 60) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 60) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 60);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 60) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 60) / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 8
        *reinterpret_cast<int16_t*>(nextLod->minBuffer + 62) = *reinterpret_cast<int16_t*>(thisLod->minBuffer + 62) < *reinterpret_cast<int16_t*>(nextLod->minBuffer + 62) ? *reinterpret_cast<int16_t*>(thisLod->minBuffer + 62) : *reinterpret_cast<int16_t*>(nextLod->minBuffer + 62);
        *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 62) = *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 62) > *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 62) ? *reinterpret_cast<int16_t*>(thisLod->maxBuffer + 62) : *reinterpret_cast<int16_t*>(nextLod->maxBuffer + 62);
        *reinterpret_cast<int16_t*>(nextLod->avgBuffer + 62) += *reinterpret_cast<int16_t*>(thisLod->avgBuffer + 62) / LOD_SAMPLE_INTERVAL;
        // Dummy -> A
        *reinterpret_cast<uint64_t*>(nextLod->minBuffer + 64) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->maxBuffer + 64) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->avgBuffer + 64) = 0;
        // Dummy -> B
        *reinterpret_cast<uint64_t*>(nextLod->minBuffer + 72) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->maxBuffer + 72) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->avgBuffer + 72) = 0;
        // Dummy -> C
        *reinterpret_cast<uint64_t*>(nextLod->minBuffer + 80) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->maxBuffer + 80) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->avgBuffer + 80) = 0;
        // Dummy -> D
        *reinterpret_cast<uint64_t*>(nextLod->minBuffer + 88) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->maxBuffer + 88) = 0;
        *reinterpret_cast<uint64_t*>(nextLod->avgBuffer + 88) = 0;
        // Dummy -> W
        *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 96) = 0;
        *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 96) = 0;
        *reinterpret_cast<uint8_t*>(nextLod->avgBuffer + 96) = 0;
        // Dummy -> X
        *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 97) = 0;
        *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 97) = 0;
        *reinterpret_cast<uint8_t*>(nextLod->avgBuffer + 97) = 0;
        // Diagnostics -> Error Count
        *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 98) = *reinterpret_cast<uint8_t*>(thisLod->minBuffer + 98) < *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 98) ? *reinterpret_cast<uint8_t*>(thisLod->minBuffer + 98) : *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 98);
        *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 98) = *reinterpret_cast<uint8_t*>(thisLod->maxBuffer + 98) > *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 98) ? *reinterpret_cast<uint8_t*>(thisLod->maxBuffer + 98) : *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 98);
        *reinterpret_cast<uint8_t*>(nextLod->avgBuffer + 98) += *reinterpret_cast<uint8_t*>(thisLod->avgBuffer + 98) / LOD_SAMPLE_INTERVAL;
        // Diagnostics -> Last Error Cause
        *reinterpret_cast<uint8_t*>(nextLod->minBuffer + 99) = *reinterpret_cast<uint8_t*>(thisLod->minBuffer + 99);
        *reinterpret_cast<uint8_t*>(nextLod->maxBuffer + 99) = *reinterpret_cast<uint8_t*>(thisLod->maxBuffer + 99);
        *reinterpret_cast<uint8_t*>(nextLod->avgBuffer + 99) += *reinterpret_cast<uint8_t*>(thisLod->avgBuffer + 99);

        nextLod->progress += 1;
        if (nextLod->progress == LOD_SAMPLE_INTERVAL) {
            commitLod(lodIndex + 1);
        }
    }
    // Write new values to the file buffer.
    thisLod->fileBuffer.append(thisLod->minBuffer, FRAME_SIZE);
    thisLod->fileBuffer.append(thisLod->maxBuffer, FRAME_SIZE);
    thisLod->fileBuffer.append(thisLod->avgBuffer, FRAME_SIZE);
    // Reset the buffer to a state where new values can be written to it.
    resetLodBuffer(lodIndex);
}

// Call this to incorporate the given data into all the LOD buffers.
void updateLods(char *incomingData) {
    // Update the first LOD with the new data...
    // ADC 1 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 0) = *reinterpret_cast<int16_t*>(incomingData + 0) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 0) ? *reinterpret_cast<int16_t*>(incomingData + 0) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 0);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 0) = *reinterpret_cast<int16_t*>(incomingData + 0) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 0) ? *reinterpret_cast<int16_t*>(incomingData + 0) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 0);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 0) += *reinterpret_cast<int16_t*>(incomingData + 0) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 2) = *reinterpret_cast<int16_t*>(incomingData + 2) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 2) ? *reinterpret_cast<int16_t*>(incomingData + 2) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 2);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 2) = *reinterpret_cast<int16_t*>(incomingData + 2) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 2) ? *reinterpret_cast<int16_t*>(incomingData + 2) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 2);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 2) += *reinterpret_cast<int16_t*>(incomingData + 2) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 4) = *reinterpret_cast<int16_t*>(incomingData + 4) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 4) ? *reinterpret_cast<int16_t*>(incomingData + 4) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 4);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 4) = *reinterpret_cast<int16_t*>(incomingData + 4) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 4) ? *reinterpret_cast<int16_t*>(incomingData + 4) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 4);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 4) += *reinterpret_cast<int16_t*>(incomingData + 4) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 6) = *reinterpret_cast<int16_t*>(incomingData + 6) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 6) ? *reinterpret_cast<int16_t*>(incomingData + 6) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 6);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 6) = *reinterpret_cast<int16_t*>(incomingData + 6) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 6) ? *reinterpret_cast<int16_t*>(incomingData + 6) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 6);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 6) += *reinterpret_cast<int16_t*>(incomingData + 6) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 8) = *reinterpret_cast<int16_t*>(incomingData + 8) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 8) ? *reinterpret_cast<int16_t*>(incomingData + 8) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 8);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 8) = *reinterpret_cast<int16_t*>(incomingData + 8) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 8) ? *reinterpret_cast<int16_t*>(incomingData + 8) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 8);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 8) += *reinterpret_cast<int16_t*>(incomingData + 8) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 10) = *reinterpret_cast<int16_t*>(incomingData + 10) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 10) ? *reinterpret_cast<int16_t*>(incomingData + 10) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 10);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 10) = *reinterpret_cast<int16_t*>(incomingData + 10) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 10) ? *reinterpret_cast<int16_t*>(incomingData + 10) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 10);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 10) += *reinterpret_cast<int16_t*>(incomingData + 10) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 12) = *reinterpret_cast<int16_t*>(incomingData + 12) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 12) ? *reinterpret_cast<int16_t*>(incomingData + 12) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 12);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 12) = *reinterpret_cast<int16_t*>(incomingData + 12) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 12) ? *reinterpret_cast<int16_t*>(incomingData + 12) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 12);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 12) += *reinterpret_cast<int16_t*>(incomingData + 12) / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 14) = *reinterpret_cast<int16_t*>(incomingData + 14) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 14) ? *reinterpret_cast<int16_t*>(incomingData + 14) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 14);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 14) = *reinterpret_cast<int16_t*>(incomingData + 14) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 14) ? *reinterpret_cast<int16_t*>(incomingData + 14) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 14);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 14) += *reinterpret_cast<int16_t*>(incomingData + 14) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 16) = *reinterpret_cast<int16_t*>(incomingData + 16) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 16) ? *reinterpret_cast<int16_t*>(incomingData + 16) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 16);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 16) = *reinterpret_cast<int16_t*>(incomingData + 16) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 16) ? *reinterpret_cast<int16_t*>(incomingData + 16) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 16);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 16) += *reinterpret_cast<int16_t*>(incomingData + 16) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 18) = *reinterpret_cast<int16_t*>(incomingData + 18) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 18) ? *reinterpret_cast<int16_t*>(incomingData + 18) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 18);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 18) = *reinterpret_cast<int16_t*>(incomingData + 18) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 18) ? *reinterpret_cast<int16_t*>(incomingData + 18) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 18);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 18) += *reinterpret_cast<int16_t*>(incomingData + 18) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 20) = *reinterpret_cast<int16_t*>(incomingData + 20) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 20) ? *reinterpret_cast<int16_t*>(incomingData + 20) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 20);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 20) = *reinterpret_cast<int16_t*>(incomingData + 20) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 20) ? *reinterpret_cast<int16_t*>(incomingData + 20) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 20);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 20) += *reinterpret_cast<int16_t*>(incomingData + 20) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 22) = *reinterpret_cast<int16_t*>(incomingData + 22) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 22) ? *reinterpret_cast<int16_t*>(incomingData + 22) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 22);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 22) = *reinterpret_cast<int16_t*>(incomingData + 22) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 22) ? *reinterpret_cast<int16_t*>(incomingData + 22) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 22);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 22) += *reinterpret_cast<int16_t*>(incomingData + 22) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 24) = *reinterpret_cast<int16_t*>(incomingData + 24) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 24) ? *reinterpret_cast<int16_t*>(incomingData + 24) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 24);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 24) = *reinterpret_cast<int16_t*>(incomingData + 24) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 24) ? *reinterpret_cast<int16_t*>(incomingData + 24) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 24);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 24) += *reinterpret_cast<int16_t*>(incomingData + 24) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 26) = *reinterpret_cast<int16_t*>(incomingData + 26) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 26) ? *reinterpret_cast<int16_t*>(incomingData + 26) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 26);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 26) = *reinterpret_cast<int16_t*>(incomingData + 26) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 26) ? *reinterpret_cast<int16_t*>(incomingData + 26) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 26);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 26) += *reinterpret_cast<int16_t*>(incomingData + 26) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 28) = *reinterpret_cast<int16_t*>(incomingData + 28) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 28) ? *reinterpret_cast<int16_t*>(incomingData + 28) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 28);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 28) = *reinterpret_cast<int16_t*>(incomingData + 28) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 28) ? *reinterpret_cast<int16_t*>(incomingData + 28) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 28);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 28) += *reinterpret_cast<int16_t*>(incomingData + 28) / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 30) = *reinterpret_cast<int16_t*>(incomingData + 30) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 30) ? *reinterpret_cast<int16_t*>(incomingData + 30) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 30);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 30) = *reinterpret_cast<int16_t*>(incomingData + 30) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 30) ? *reinterpret_cast<int16_t*>(incomingData + 30) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 30);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 30) += *reinterpret_cast<int16_t*>(incomingData + 30) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 32) = *reinterpret_cast<int16_t*>(incomingData + 32) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 32) ? *reinterpret_cast<int16_t*>(incomingData + 32) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 32);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 32) = *reinterpret_cast<int16_t*>(incomingData + 32) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 32) ? *reinterpret_cast<int16_t*>(incomingData + 32) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 32);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 32) += *reinterpret_cast<int16_t*>(incomingData + 32) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 34) = *reinterpret_cast<int16_t*>(incomingData + 34) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 34) ? *reinterpret_cast<int16_t*>(incomingData + 34) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 34);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 34) = *reinterpret_cast<int16_t*>(incomingData + 34) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 34) ? *reinterpret_cast<int16_t*>(incomingData + 34) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 34);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 34) += *reinterpret_cast<int16_t*>(incomingData + 34) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 36) = *reinterpret_cast<int16_t*>(incomingData + 36) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 36) ? *reinterpret_cast<int16_t*>(incomingData + 36) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 36);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 36) = *reinterpret_cast<int16_t*>(incomingData + 36) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 36) ? *reinterpret_cast<int16_t*>(incomingData + 36) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 36);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 36) += *reinterpret_cast<int16_t*>(incomingData + 36) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 38) = *reinterpret_cast<int16_t*>(incomingData + 38) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 38) ? *reinterpret_cast<int16_t*>(incomingData + 38) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 38);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 38) = *reinterpret_cast<int16_t*>(incomingData + 38) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 38) ? *reinterpret_cast<int16_t*>(incomingData + 38) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 38);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 38) += *reinterpret_cast<int16_t*>(incomingData + 38) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 40) = *reinterpret_cast<int16_t*>(incomingData + 40) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 40) ? *reinterpret_cast<int16_t*>(incomingData + 40) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 40);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 40) = *reinterpret_cast<int16_t*>(incomingData + 40) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 40) ? *reinterpret_cast<int16_t*>(incomingData + 40) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 40);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 40) += *reinterpret_cast<int16_t*>(incomingData + 40) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 42) = *reinterpret_cast<int16_t*>(incomingData + 42) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 42) ? *reinterpret_cast<int16_t*>(incomingData + 42) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 42);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 42) = *reinterpret_cast<int16_t*>(incomingData + 42) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 42) ? *reinterpret_cast<int16_t*>(incomingData + 42) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 42);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 42) += *reinterpret_cast<int16_t*>(incomingData + 42) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 44) = *reinterpret_cast<int16_t*>(incomingData + 44) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 44) ? *reinterpret_cast<int16_t*>(incomingData + 44) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 44);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 44) = *reinterpret_cast<int16_t*>(incomingData + 44) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 44) ? *reinterpret_cast<int16_t*>(incomingData + 44) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 44);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 44) += *reinterpret_cast<int16_t*>(incomingData + 44) / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 46) = *reinterpret_cast<int16_t*>(incomingData + 46) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 46) ? *reinterpret_cast<int16_t*>(incomingData + 46) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 46);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 46) = *reinterpret_cast<int16_t*>(incomingData + 46) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 46) ? *reinterpret_cast<int16_t*>(incomingData + 46) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 46);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 46) += *reinterpret_cast<int16_t*>(incomingData + 46) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 1
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 48) = *reinterpret_cast<int16_t*>(incomingData + 48) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 48) ? *reinterpret_cast<int16_t*>(incomingData + 48) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 48);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 48) = *reinterpret_cast<int16_t*>(incomingData + 48) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 48) ? *reinterpret_cast<int16_t*>(incomingData + 48) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 48);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 48) += *reinterpret_cast<int16_t*>(incomingData + 48) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 2
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 50) = *reinterpret_cast<int16_t*>(incomingData + 50) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 50) ? *reinterpret_cast<int16_t*>(incomingData + 50) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 50);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 50) = *reinterpret_cast<int16_t*>(incomingData + 50) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 50) ? *reinterpret_cast<int16_t*>(incomingData + 50) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 50);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 50) += *reinterpret_cast<int16_t*>(incomingData + 50) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 3
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 52) = *reinterpret_cast<int16_t*>(incomingData + 52) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 52) ? *reinterpret_cast<int16_t*>(incomingData + 52) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 52);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 52) = *reinterpret_cast<int16_t*>(incomingData + 52) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 52) ? *reinterpret_cast<int16_t*>(incomingData + 52) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 52);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 52) += *reinterpret_cast<int16_t*>(incomingData + 52) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 4
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 54) = *reinterpret_cast<int16_t*>(incomingData + 54) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 54) ? *reinterpret_cast<int16_t*>(incomingData + 54) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 54);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 54) = *reinterpret_cast<int16_t*>(incomingData + 54) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 54) ? *reinterpret_cast<int16_t*>(incomingData + 54) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 54);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 54) += *reinterpret_cast<int16_t*>(incomingData + 54) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 5
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 56) = *reinterpret_cast<int16_t*>(incomingData + 56) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 56) ? *reinterpret_cast<int16_t*>(incomingData + 56) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 56);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 56) = *reinterpret_cast<int16_t*>(incomingData + 56) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 56) ? *reinterpret_cast<int16_t*>(incomingData + 56) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 56);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 56) += *reinterpret_cast<int16_t*>(incomingData + 56) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 6
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 58) = *reinterpret_cast<int16_t*>(incomingData + 58) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 58) ? *reinterpret_cast<int16_t*>(incomingData + 58) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 58);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 58) = *reinterpret_cast<int16_t*>(incomingData + 58) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 58) ? *reinterpret_cast<int16_t*>(incomingData + 58) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 58);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 58) += *reinterpret_cast<int16_t*>(incomingData + 58) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 7
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 60) = *reinterpret_cast<int16_t*>(incomingData + 60) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 60) ? *reinterpret_cast<int16_t*>(incomingData + 60) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 60);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 60) = *reinterpret_cast<int16_t*>(incomingData + 60) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 60) ? *reinterpret_cast<int16_t*>(incomingData + 60) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 60);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 60) += *reinterpret_cast<int16_t*>(incomingData + 60) / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 8
    *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 62) = *reinterpret_cast<int16_t*>(incomingData + 62) < *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 62) ? *reinterpret_cast<int16_t*>(incomingData + 62) : *reinterpret_cast<int16_t*>(lodBuffers[0].minBuffer + 62);
    *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 62) = *reinterpret_cast<int16_t*>(incomingData + 62) > *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 62) ? *reinterpret_cast<int16_t*>(incomingData + 62) : *reinterpret_cast<int16_t*>(lodBuffers[0].maxBuffer + 62);
    *reinterpret_cast<int16_t*>(lodBuffers[0].avgBuffer + 62) += *reinterpret_cast<int16_t*>(incomingData + 62) / LOD_SAMPLE_INTERVAL;
    // Dummy -> A
    *reinterpret_cast<uint64_t*>(lodBuffers[0].minBuffer + 64) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].maxBuffer + 64) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].avgBuffer + 64) = 0;
    // Dummy -> B
    *reinterpret_cast<uint64_t*>(lodBuffers[0].minBuffer + 72) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].maxBuffer + 72) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].avgBuffer + 72) = 0;
    // Dummy -> C
    *reinterpret_cast<uint64_t*>(lodBuffers[0].minBuffer + 80) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].maxBuffer + 80) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].avgBuffer + 80) = 0;
    // Dummy -> D
    *reinterpret_cast<uint64_t*>(lodBuffers[0].minBuffer + 88) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].maxBuffer + 88) = 0;
    *reinterpret_cast<uint64_t*>(lodBuffers[0].avgBuffer + 88) = 0;
    // Dummy -> W
    *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 96) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 96) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[0].avgBuffer + 96) = 0;
    // Dummy -> X
    *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 97) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 97) = 0;
    *reinterpret_cast<uint8_t*>(lodBuffers[0].avgBuffer + 97) = 0;
    // Diagnostics -> Error Count
    *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 98) = *reinterpret_cast<uint8_t*>(incomingData + 98) < *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 98) ? *reinterpret_cast<uint8_t*>(incomingData + 98) : *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 98);
    *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 98) = *reinterpret_cast<uint8_t*>(incomingData + 98) > *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 98) ? *reinterpret_cast<uint8_t*>(incomingData + 98) : *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 98);
    *reinterpret_cast<uint8_t*>(lodBuffers[0].avgBuffer + 98) += *reinterpret_cast<uint8_t*>(incomingData + 98) / LOD_SAMPLE_INTERVAL;
    // Diagnostics -> Last Error Cause
    *reinterpret_cast<uint8_t*>(lodBuffers[0].minBuffer + 99) = *reinterpret_cast<uint8_t*>(incomingData + 99);
    *reinterpret_cast<uint8_t*>(lodBuffers[0].maxBuffer + 99) = *reinterpret_cast<uint8_t*>(incomingData + 99);
    *reinterpret_cast<uint8_t*>(lodBuffers[0].avgBuffer + 99) += *reinterpret_cast<uint8_t*>(incomingData + 99);

    lodBuffers[0].progress += 1;
    // If we have written enough samples to the first LOD...
    if (lodBuffers[0].progress == LOD_SAMPLE_INTERVAL) {
        // Save the parsed_formatrmation and propogate it up to higher LODs
        // as necessary.
        commitLod(0);
    }
}
