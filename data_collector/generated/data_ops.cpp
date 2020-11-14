// Do not make changes to this file, it was auto-generated based on the contents
// of ./data_format.json. You may instead change that file
// and then run ./generate_code.py to update the contents of this file.

#include <stdint.h>
#include <string.h>

// Resets an LOD buffer as if it had never had any data written to it.
void resetLodBuffer(int lodIndex) {
    lodBuffers[lodIndex].progress = 0;
    // ADC 1 -> Channel 1
    lodBuffers[lodIndex].minBuffer.adcReadings[0][0] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][0] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][0] = 0;
    // ADC 1 -> Channel 2
    lodBuffers[lodIndex].minBuffer.adcReadings[0][1] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][1] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][1] = 0;
    // ADC 1 -> Channel 3
    lodBuffers[lodIndex].minBuffer.adcReadings[0][2] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][2] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][2] = 0;
    // ADC 1 -> Channel 4
    lodBuffers[lodIndex].minBuffer.adcReadings[0][3] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][3] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][3] = 0;
    // ADC 1 -> Channel 5
    lodBuffers[lodIndex].minBuffer.adcReadings[0][4] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][4] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][4] = 0;
    // ADC 1 -> Channel 6
    lodBuffers[lodIndex].minBuffer.adcReadings[0][5] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][5] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][5] = 0;
    // ADC 1 -> Channel 7
    lodBuffers[lodIndex].minBuffer.adcReadings[0][6] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][6] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][6] = 0;
    // ADC 1 -> Channel 8
    lodBuffers[lodIndex].minBuffer.adcReadings[0][7] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[0][7] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[0][7] = 0;
    // ADC 2 -> Channel 1
    lodBuffers[lodIndex].minBuffer.adcReadings[1][0] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][0] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][0] = 0;
    // ADC 2 -> Channel 2
    lodBuffers[lodIndex].minBuffer.adcReadings[1][1] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][1] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][1] = 0;
    // ADC 2 -> Channel 3
    lodBuffers[lodIndex].minBuffer.adcReadings[1][2] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][2] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][2] = 0;
    // ADC 2 -> Channel 4
    lodBuffers[lodIndex].minBuffer.adcReadings[1][3] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][3] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][3] = 0;
    // ADC 2 -> Channel 5
    lodBuffers[lodIndex].minBuffer.adcReadings[1][4] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][4] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][4] = 0;
    // ADC 2 -> Channel 6
    lodBuffers[lodIndex].minBuffer.adcReadings[1][5] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][5] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][5] = 0;
    // ADC 2 -> Channel 7
    lodBuffers[lodIndex].minBuffer.adcReadings[1][6] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][6] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][6] = 0;
    // ADC 2 -> Channel 8
    lodBuffers[lodIndex].minBuffer.adcReadings[1][7] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[1][7] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[1][7] = 0;
    // ADC 3 -> Channel 1
    lodBuffers[lodIndex].minBuffer.adcReadings[2][0] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][0] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][0] = 0;
    // ADC 3 -> Channel 2
    lodBuffers[lodIndex].minBuffer.adcReadings[2][1] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][1] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][1] = 0;
    // ADC 3 -> Channel 3
    lodBuffers[lodIndex].minBuffer.adcReadings[2][2] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][2] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][2] = 0;
    // ADC 3 -> Channel 4
    lodBuffers[lodIndex].minBuffer.adcReadings[2][3] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][3] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][3] = 0;
    // ADC 3 -> Channel 5
    lodBuffers[lodIndex].minBuffer.adcReadings[2][4] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][4] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][4] = 0;
    // ADC 3 -> Channel 6
    lodBuffers[lodIndex].minBuffer.adcReadings[2][5] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][5] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][5] = 0;
    // ADC 3 -> Channel 7
    lodBuffers[lodIndex].minBuffer.adcReadings[2][6] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][6] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][6] = 0;
    // ADC 3 -> Channel 8
    lodBuffers[lodIndex].minBuffer.adcReadings[2][7] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[2][7] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[2][7] = 0;
    // ADC 4 -> Channel 1
    lodBuffers[lodIndex].minBuffer.adcReadings[3][0] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][0] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][0] = 0;
    // ADC 4 -> Channel 2
    lodBuffers[lodIndex].minBuffer.adcReadings[3][1] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][1] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][1] = 0;
    // ADC 4 -> Channel 3
    lodBuffers[lodIndex].minBuffer.adcReadings[3][2] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][2] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][2] = 0;
    // ADC 4 -> Channel 4
    lodBuffers[lodIndex].minBuffer.adcReadings[3][3] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][3] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][3] = 0;
    // ADC 4 -> Channel 5
    lodBuffers[lodIndex].minBuffer.adcReadings[3][4] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][4] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][4] = 0;
    // ADC 4 -> Channel 6
    lodBuffers[lodIndex].minBuffer.adcReadings[3][5] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][5] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][5] = 0;
    // ADC 4 -> Channel 7
    lodBuffers[lodIndex].minBuffer.adcReadings[3][6] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][6] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][6] = 0;
    // ADC 4 -> Channel 8
    lodBuffers[lodIndex].minBuffer.adcReadings[3][7] = 0x7FFF;
    lodBuffers[lodIndex].maxBuffer.adcReadings[3][7] = -0x8000;
    lodBuffers[lodIndex].avgBuffer.adcReadings[3][7] = 0;
    // Diagnostics -> Error Count
    lodBuffers[lodIndex].minBuffer.errorCount = 0xFF;
    lodBuffers[lodIndex].maxBuffer.errorCount = 0;
    lodBuffers[lodIndex].avgBuffer.errorCount = 0;
    // Diagnostics -> Last Error Cause
    lodBuffers[lodIndex].minBuffer.lastErrorCode = 0;
    lodBuffers[lodIndex].maxBuffer.lastErrorCode = 0;
    lodBuffers[lodIndex].avgBuffer.lastErrorCode = 0;

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
        nextLod->minBuffer.adcReadings[0][0] = thisLod->minBuffer.adcReadings[0][0] < nextLod->minBuffer.adcReadings[0][0] ? thisLod->minBuffer.adcReadings[0][0] : nextLod->minBuffer.adcReadings[0][0];
        nextLod->maxBuffer.adcReadings[0][0] = thisLod->maxBuffer.adcReadings[0][0] > nextLod->maxBuffer.adcReadings[0][0] ? thisLod->maxBuffer.adcReadings[0][0] : nextLod->maxBuffer.adcReadings[0][0];
        nextLod->avgBuffer.adcReadings[0][0] += thisLod->avgBuffer.adcReadings[0][0] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 2
        nextLod->minBuffer.adcReadings[0][1] = thisLod->minBuffer.adcReadings[0][1] < nextLod->minBuffer.adcReadings[0][1] ? thisLod->minBuffer.adcReadings[0][1] : nextLod->minBuffer.adcReadings[0][1];
        nextLod->maxBuffer.adcReadings[0][1] = thisLod->maxBuffer.adcReadings[0][1] > nextLod->maxBuffer.adcReadings[0][1] ? thisLod->maxBuffer.adcReadings[0][1] : nextLod->maxBuffer.adcReadings[0][1];
        nextLod->avgBuffer.adcReadings[0][1] += thisLod->avgBuffer.adcReadings[0][1] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 3
        nextLod->minBuffer.adcReadings[0][2] = thisLod->minBuffer.adcReadings[0][2] < nextLod->minBuffer.adcReadings[0][2] ? thisLod->minBuffer.adcReadings[0][2] : nextLod->minBuffer.adcReadings[0][2];
        nextLod->maxBuffer.adcReadings[0][2] = thisLod->maxBuffer.adcReadings[0][2] > nextLod->maxBuffer.adcReadings[0][2] ? thisLod->maxBuffer.adcReadings[0][2] : nextLod->maxBuffer.adcReadings[0][2];
        nextLod->avgBuffer.adcReadings[0][2] += thisLod->avgBuffer.adcReadings[0][2] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 4
        nextLod->minBuffer.adcReadings[0][3] = thisLod->minBuffer.adcReadings[0][3] < nextLod->minBuffer.adcReadings[0][3] ? thisLod->minBuffer.adcReadings[0][3] : nextLod->minBuffer.adcReadings[0][3];
        nextLod->maxBuffer.adcReadings[0][3] = thisLod->maxBuffer.adcReadings[0][3] > nextLod->maxBuffer.adcReadings[0][3] ? thisLod->maxBuffer.adcReadings[0][3] : nextLod->maxBuffer.adcReadings[0][3];
        nextLod->avgBuffer.adcReadings[0][3] += thisLod->avgBuffer.adcReadings[0][3] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 5
        nextLod->minBuffer.adcReadings[0][4] = thisLod->minBuffer.adcReadings[0][4] < nextLod->minBuffer.adcReadings[0][4] ? thisLod->minBuffer.adcReadings[0][4] : nextLod->minBuffer.adcReadings[0][4];
        nextLod->maxBuffer.adcReadings[0][4] = thisLod->maxBuffer.adcReadings[0][4] > nextLod->maxBuffer.adcReadings[0][4] ? thisLod->maxBuffer.adcReadings[0][4] : nextLod->maxBuffer.adcReadings[0][4];
        nextLod->avgBuffer.adcReadings[0][4] += thisLod->avgBuffer.adcReadings[0][4] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 6
        nextLod->minBuffer.adcReadings[0][5] = thisLod->minBuffer.adcReadings[0][5] < nextLod->minBuffer.adcReadings[0][5] ? thisLod->minBuffer.adcReadings[0][5] : nextLod->minBuffer.adcReadings[0][5];
        nextLod->maxBuffer.adcReadings[0][5] = thisLod->maxBuffer.adcReadings[0][5] > nextLod->maxBuffer.adcReadings[0][5] ? thisLod->maxBuffer.adcReadings[0][5] : nextLod->maxBuffer.adcReadings[0][5];
        nextLod->avgBuffer.adcReadings[0][5] += thisLod->avgBuffer.adcReadings[0][5] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 7
        nextLod->minBuffer.adcReadings[0][6] = thisLod->minBuffer.adcReadings[0][6] < nextLod->minBuffer.adcReadings[0][6] ? thisLod->minBuffer.adcReadings[0][6] : nextLod->minBuffer.adcReadings[0][6];
        nextLod->maxBuffer.adcReadings[0][6] = thisLod->maxBuffer.adcReadings[0][6] > nextLod->maxBuffer.adcReadings[0][6] ? thisLod->maxBuffer.adcReadings[0][6] : nextLod->maxBuffer.adcReadings[0][6];
        nextLod->avgBuffer.adcReadings[0][6] += thisLod->avgBuffer.adcReadings[0][6] / LOD_SAMPLE_INTERVAL;
        // ADC 1 -> Channel 8
        nextLod->minBuffer.adcReadings[0][7] = thisLod->minBuffer.adcReadings[0][7] < nextLod->minBuffer.adcReadings[0][7] ? thisLod->minBuffer.adcReadings[0][7] : nextLod->minBuffer.adcReadings[0][7];
        nextLod->maxBuffer.adcReadings[0][7] = thisLod->maxBuffer.adcReadings[0][7] > nextLod->maxBuffer.adcReadings[0][7] ? thisLod->maxBuffer.adcReadings[0][7] : nextLod->maxBuffer.adcReadings[0][7];
        nextLod->avgBuffer.adcReadings[0][7] += thisLod->avgBuffer.adcReadings[0][7] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 1
        nextLod->minBuffer.adcReadings[1][0] = thisLod->minBuffer.adcReadings[1][0] < nextLod->minBuffer.adcReadings[1][0] ? thisLod->minBuffer.adcReadings[1][0] : nextLod->minBuffer.adcReadings[1][0];
        nextLod->maxBuffer.adcReadings[1][0] = thisLod->maxBuffer.adcReadings[1][0] > nextLod->maxBuffer.adcReadings[1][0] ? thisLod->maxBuffer.adcReadings[1][0] : nextLod->maxBuffer.adcReadings[1][0];
        nextLod->avgBuffer.adcReadings[1][0] += thisLod->avgBuffer.adcReadings[1][0] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 2
        nextLod->minBuffer.adcReadings[1][1] = thisLod->minBuffer.adcReadings[1][1] < nextLod->minBuffer.adcReadings[1][1] ? thisLod->minBuffer.adcReadings[1][1] : nextLod->minBuffer.adcReadings[1][1];
        nextLod->maxBuffer.adcReadings[1][1] = thisLod->maxBuffer.adcReadings[1][1] > nextLod->maxBuffer.adcReadings[1][1] ? thisLod->maxBuffer.adcReadings[1][1] : nextLod->maxBuffer.adcReadings[1][1];
        nextLod->avgBuffer.adcReadings[1][1] += thisLod->avgBuffer.adcReadings[1][1] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 3
        nextLod->minBuffer.adcReadings[1][2] = thisLod->minBuffer.adcReadings[1][2] < nextLod->minBuffer.adcReadings[1][2] ? thisLod->minBuffer.adcReadings[1][2] : nextLod->minBuffer.adcReadings[1][2];
        nextLod->maxBuffer.adcReadings[1][2] = thisLod->maxBuffer.adcReadings[1][2] > nextLod->maxBuffer.adcReadings[1][2] ? thisLod->maxBuffer.adcReadings[1][2] : nextLod->maxBuffer.adcReadings[1][2];
        nextLod->avgBuffer.adcReadings[1][2] += thisLod->avgBuffer.adcReadings[1][2] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 4
        nextLod->minBuffer.adcReadings[1][3] = thisLod->minBuffer.adcReadings[1][3] < nextLod->minBuffer.adcReadings[1][3] ? thisLod->minBuffer.adcReadings[1][3] : nextLod->minBuffer.adcReadings[1][3];
        nextLod->maxBuffer.adcReadings[1][3] = thisLod->maxBuffer.adcReadings[1][3] > nextLod->maxBuffer.adcReadings[1][3] ? thisLod->maxBuffer.adcReadings[1][3] : nextLod->maxBuffer.adcReadings[1][3];
        nextLod->avgBuffer.adcReadings[1][3] += thisLod->avgBuffer.adcReadings[1][3] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 5
        nextLod->minBuffer.adcReadings[1][4] = thisLod->minBuffer.adcReadings[1][4] < nextLod->minBuffer.adcReadings[1][4] ? thisLod->minBuffer.adcReadings[1][4] : nextLod->minBuffer.adcReadings[1][4];
        nextLod->maxBuffer.adcReadings[1][4] = thisLod->maxBuffer.adcReadings[1][4] > nextLod->maxBuffer.adcReadings[1][4] ? thisLod->maxBuffer.adcReadings[1][4] : nextLod->maxBuffer.adcReadings[1][4];
        nextLod->avgBuffer.adcReadings[1][4] += thisLod->avgBuffer.adcReadings[1][4] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 6
        nextLod->minBuffer.adcReadings[1][5] = thisLod->minBuffer.adcReadings[1][5] < nextLod->minBuffer.adcReadings[1][5] ? thisLod->minBuffer.adcReadings[1][5] : nextLod->minBuffer.adcReadings[1][5];
        nextLod->maxBuffer.adcReadings[1][5] = thisLod->maxBuffer.adcReadings[1][5] > nextLod->maxBuffer.adcReadings[1][5] ? thisLod->maxBuffer.adcReadings[1][5] : nextLod->maxBuffer.adcReadings[1][5];
        nextLod->avgBuffer.adcReadings[1][5] += thisLod->avgBuffer.adcReadings[1][5] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 7
        nextLod->minBuffer.adcReadings[1][6] = thisLod->minBuffer.adcReadings[1][6] < nextLod->minBuffer.adcReadings[1][6] ? thisLod->minBuffer.adcReadings[1][6] : nextLod->minBuffer.adcReadings[1][6];
        nextLod->maxBuffer.adcReadings[1][6] = thisLod->maxBuffer.adcReadings[1][6] > nextLod->maxBuffer.adcReadings[1][6] ? thisLod->maxBuffer.adcReadings[1][6] : nextLod->maxBuffer.adcReadings[1][6];
        nextLod->avgBuffer.adcReadings[1][6] += thisLod->avgBuffer.adcReadings[1][6] / LOD_SAMPLE_INTERVAL;
        // ADC 2 -> Channel 8
        nextLod->minBuffer.adcReadings[1][7] = thisLod->minBuffer.adcReadings[1][7] < nextLod->minBuffer.adcReadings[1][7] ? thisLod->minBuffer.adcReadings[1][7] : nextLod->minBuffer.adcReadings[1][7];
        nextLod->maxBuffer.adcReadings[1][7] = thisLod->maxBuffer.adcReadings[1][7] > nextLod->maxBuffer.adcReadings[1][7] ? thisLod->maxBuffer.adcReadings[1][7] : nextLod->maxBuffer.adcReadings[1][7];
        nextLod->avgBuffer.adcReadings[1][7] += thisLod->avgBuffer.adcReadings[1][7] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 1
        nextLod->minBuffer.adcReadings[2][0] = thisLod->minBuffer.adcReadings[2][0] < nextLod->minBuffer.adcReadings[2][0] ? thisLod->minBuffer.adcReadings[2][0] : nextLod->minBuffer.adcReadings[2][0];
        nextLod->maxBuffer.adcReadings[2][0] = thisLod->maxBuffer.adcReadings[2][0] > nextLod->maxBuffer.adcReadings[2][0] ? thisLod->maxBuffer.adcReadings[2][0] : nextLod->maxBuffer.adcReadings[2][0];
        nextLod->avgBuffer.adcReadings[2][0] += thisLod->avgBuffer.adcReadings[2][0] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 2
        nextLod->minBuffer.adcReadings[2][1] = thisLod->minBuffer.adcReadings[2][1] < nextLod->minBuffer.adcReadings[2][1] ? thisLod->minBuffer.adcReadings[2][1] : nextLod->minBuffer.adcReadings[2][1];
        nextLod->maxBuffer.adcReadings[2][1] = thisLod->maxBuffer.adcReadings[2][1] > nextLod->maxBuffer.adcReadings[2][1] ? thisLod->maxBuffer.adcReadings[2][1] : nextLod->maxBuffer.adcReadings[2][1];
        nextLod->avgBuffer.adcReadings[2][1] += thisLod->avgBuffer.adcReadings[2][1] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 3
        nextLod->minBuffer.adcReadings[2][2] = thisLod->minBuffer.adcReadings[2][2] < nextLod->minBuffer.adcReadings[2][2] ? thisLod->minBuffer.adcReadings[2][2] : nextLod->minBuffer.adcReadings[2][2];
        nextLod->maxBuffer.adcReadings[2][2] = thisLod->maxBuffer.adcReadings[2][2] > nextLod->maxBuffer.adcReadings[2][2] ? thisLod->maxBuffer.adcReadings[2][2] : nextLod->maxBuffer.adcReadings[2][2];
        nextLod->avgBuffer.adcReadings[2][2] += thisLod->avgBuffer.adcReadings[2][2] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 4
        nextLod->minBuffer.adcReadings[2][3] = thisLod->minBuffer.adcReadings[2][3] < nextLod->minBuffer.adcReadings[2][3] ? thisLod->minBuffer.adcReadings[2][3] : nextLod->minBuffer.adcReadings[2][3];
        nextLod->maxBuffer.adcReadings[2][3] = thisLod->maxBuffer.adcReadings[2][3] > nextLod->maxBuffer.adcReadings[2][3] ? thisLod->maxBuffer.adcReadings[2][3] : nextLod->maxBuffer.adcReadings[2][3];
        nextLod->avgBuffer.adcReadings[2][3] += thisLod->avgBuffer.adcReadings[2][3] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 5
        nextLod->minBuffer.adcReadings[2][4] = thisLod->minBuffer.adcReadings[2][4] < nextLod->minBuffer.adcReadings[2][4] ? thisLod->minBuffer.adcReadings[2][4] : nextLod->minBuffer.adcReadings[2][4];
        nextLod->maxBuffer.adcReadings[2][4] = thisLod->maxBuffer.adcReadings[2][4] > nextLod->maxBuffer.adcReadings[2][4] ? thisLod->maxBuffer.adcReadings[2][4] : nextLod->maxBuffer.adcReadings[2][4];
        nextLod->avgBuffer.adcReadings[2][4] += thisLod->avgBuffer.adcReadings[2][4] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 6
        nextLod->minBuffer.adcReadings[2][5] = thisLod->minBuffer.adcReadings[2][5] < nextLod->minBuffer.adcReadings[2][5] ? thisLod->minBuffer.adcReadings[2][5] : nextLod->minBuffer.adcReadings[2][5];
        nextLod->maxBuffer.adcReadings[2][5] = thisLod->maxBuffer.adcReadings[2][5] > nextLod->maxBuffer.adcReadings[2][5] ? thisLod->maxBuffer.adcReadings[2][5] : nextLod->maxBuffer.adcReadings[2][5];
        nextLod->avgBuffer.adcReadings[2][5] += thisLod->avgBuffer.adcReadings[2][5] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 7
        nextLod->minBuffer.adcReadings[2][6] = thisLod->minBuffer.adcReadings[2][6] < nextLod->minBuffer.adcReadings[2][6] ? thisLod->minBuffer.adcReadings[2][6] : nextLod->minBuffer.adcReadings[2][6];
        nextLod->maxBuffer.adcReadings[2][6] = thisLod->maxBuffer.adcReadings[2][6] > nextLod->maxBuffer.adcReadings[2][6] ? thisLod->maxBuffer.adcReadings[2][6] : nextLod->maxBuffer.adcReadings[2][6];
        nextLod->avgBuffer.adcReadings[2][6] += thisLod->avgBuffer.adcReadings[2][6] / LOD_SAMPLE_INTERVAL;
        // ADC 3 -> Channel 8
        nextLod->minBuffer.adcReadings[2][7] = thisLod->minBuffer.adcReadings[2][7] < nextLod->minBuffer.adcReadings[2][7] ? thisLod->minBuffer.adcReadings[2][7] : nextLod->minBuffer.adcReadings[2][7];
        nextLod->maxBuffer.adcReadings[2][7] = thisLod->maxBuffer.adcReadings[2][7] > nextLod->maxBuffer.adcReadings[2][7] ? thisLod->maxBuffer.adcReadings[2][7] : nextLod->maxBuffer.adcReadings[2][7];
        nextLod->avgBuffer.adcReadings[2][7] += thisLod->avgBuffer.adcReadings[2][7] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 1
        nextLod->minBuffer.adcReadings[3][0] = thisLod->minBuffer.adcReadings[3][0] < nextLod->minBuffer.adcReadings[3][0] ? thisLod->minBuffer.adcReadings[3][0] : nextLod->minBuffer.adcReadings[3][0];
        nextLod->maxBuffer.adcReadings[3][0] = thisLod->maxBuffer.adcReadings[3][0] > nextLod->maxBuffer.adcReadings[3][0] ? thisLod->maxBuffer.adcReadings[3][0] : nextLod->maxBuffer.adcReadings[3][0];
        nextLod->avgBuffer.adcReadings[3][0] += thisLod->avgBuffer.adcReadings[3][0] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 2
        nextLod->minBuffer.adcReadings[3][1] = thisLod->minBuffer.adcReadings[3][1] < nextLod->minBuffer.adcReadings[3][1] ? thisLod->minBuffer.adcReadings[3][1] : nextLod->minBuffer.adcReadings[3][1];
        nextLod->maxBuffer.adcReadings[3][1] = thisLod->maxBuffer.adcReadings[3][1] > nextLod->maxBuffer.adcReadings[3][1] ? thisLod->maxBuffer.adcReadings[3][1] : nextLod->maxBuffer.adcReadings[3][1];
        nextLod->avgBuffer.adcReadings[3][1] += thisLod->avgBuffer.adcReadings[3][1] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 3
        nextLod->minBuffer.adcReadings[3][2] = thisLod->minBuffer.adcReadings[3][2] < nextLod->minBuffer.adcReadings[3][2] ? thisLod->minBuffer.adcReadings[3][2] : nextLod->minBuffer.adcReadings[3][2];
        nextLod->maxBuffer.adcReadings[3][2] = thisLod->maxBuffer.adcReadings[3][2] > nextLod->maxBuffer.adcReadings[3][2] ? thisLod->maxBuffer.adcReadings[3][2] : nextLod->maxBuffer.adcReadings[3][2];
        nextLod->avgBuffer.adcReadings[3][2] += thisLod->avgBuffer.adcReadings[3][2] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 4
        nextLod->minBuffer.adcReadings[3][3] = thisLod->minBuffer.adcReadings[3][3] < nextLod->minBuffer.adcReadings[3][3] ? thisLod->minBuffer.adcReadings[3][3] : nextLod->minBuffer.adcReadings[3][3];
        nextLod->maxBuffer.adcReadings[3][3] = thisLod->maxBuffer.adcReadings[3][3] > nextLod->maxBuffer.adcReadings[3][3] ? thisLod->maxBuffer.adcReadings[3][3] : nextLod->maxBuffer.adcReadings[3][3];
        nextLod->avgBuffer.adcReadings[3][3] += thisLod->avgBuffer.adcReadings[3][3] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 5
        nextLod->minBuffer.adcReadings[3][4] = thisLod->minBuffer.adcReadings[3][4] < nextLod->minBuffer.adcReadings[3][4] ? thisLod->minBuffer.adcReadings[3][4] : nextLod->minBuffer.adcReadings[3][4];
        nextLod->maxBuffer.adcReadings[3][4] = thisLod->maxBuffer.adcReadings[3][4] > nextLod->maxBuffer.adcReadings[3][4] ? thisLod->maxBuffer.adcReadings[3][4] : nextLod->maxBuffer.adcReadings[3][4];
        nextLod->avgBuffer.adcReadings[3][4] += thisLod->avgBuffer.adcReadings[3][4] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 6
        nextLod->minBuffer.adcReadings[3][5] = thisLod->minBuffer.adcReadings[3][5] < nextLod->minBuffer.adcReadings[3][5] ? thisLod->minBuffer.adcReadings[3][5] : nextLod->minBuffer.adcReadings[3][5];
        nextLod->maxBuffer.adcReadings[3][5] = thisLod->maxBuffer.adcReadings[3][5] > nextLod->maxBuffer.adcReadings[3][5] ? thisLod->maxBuffer.adcReadings[3][5] : nextLod->maxBuffer.adcReadings[3][5];
        nextLod->avgBuffer.adcReadings[3][5] += thisLod->avgBuffer.adcReadings[3][5] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 7
        nextLod->minBuffer.adcReadings[3][6] = thisLod->minBuffer.adcReadings[3][6] < nextLod->minBuffer.adcReadings[3][6] ? thisLod->minBuffer.adcReadings[3][6] : nextLod->minBuffer.adcReadings[3][6];
        nextLod->maxBuffer.adcReadings[3][6] = thisLod->maxBuffer.adcReadings[3][6] > nextLod->maxBuffer.adcReadings[3][6] ? thisLod->maxBuffer.adcReadings[3][6] : nextLod->maxBuffer.adcReadings[3][6];
        nextLod->avgBuffer.adcReadings[3][6] += thisLod->avgBuffer.adcReadings[3][6] / LOD_SAMPLE_INTERVAL;
        // ADC 4 -> Channel 8
        nextLod->minBuffer.adcReadings[3][7] = thisLod->minBuffer.adcReadings[3][7] < nextLod->minBuffer.adcReadings[3][7] ? thisLod->minBuffer.adcReadings[3][7] : nextLod->minBuffer.adcReadings[3][7];
        nextLod->maxBuffer.adcReadings[3][7] = thisLod->maxBuffer.adcReadings[3][7] > nextLod->maxBuffer.adcReadings[3][7] ? thisLod->maxBuffer.adcReadings[3][7] : nextLod->maxBuffer.adcReadings[3][7];
        nextLod->avgBuffer.adcReadings[3][7] += thisLod->avgBuffer.adcReadings[3][7] / LOD_SAMPLE_INTERVAL;
        // Diagnostics -> Error Count
        nextLod->minBuffer.errorCount = thisLod->minBuffer.errorCount < nextLod->minBuffer.errorCount ? thisLod->minBuffer.errorCount : nextLod->minBuffer.errorCount;
        nextLod->maxBuffer.errorCount = thisLod->maxBuffer.errorCount > nextLod->maxBuffer.errorCount ? thisLod->maxBuffer.errorCount : nextLod->maxBuffer.errorCount;
        nextLod->avgBuffer.errorCount += thisLod->avgBuffer.errorCount / LOD_SAMPLE_INTERVAL;
        // Diagnostics -> Last Error Cause
        nextLod->minBuffer.lastErrorCode = thisLod->minBuffer.lastErrorCode;
        nextLod->maxBuffer.lastErrorCode = thisLod->maxBuffer.lastErrorCode;
        nextLod->avgBuffer.lastErrorCode += thisLod->avgBuffer.lastErrorCode;

        nextLod->progress += 1;
        if (nextLod->progress == LOD_SAMPLE_INTERVAL) {
            commitLod(lodIndex + 1);
        }
    }
    // Write new values to the file buffer.
    thisLod->fileBuffer.append(thisLod->minBuffer);
    thisLod->fileBuffer.append(thisLod->maxBuffer);
    thisLod->fileBuffer.append(thisLod->avgBuffer);
    // Reset the buffer to a state where new values can be written to it.
    resetLodBuffer(lodIndex);
}

// Call this to incorporate the given data into all the LOD buffers.
void updateLods(DataFrame &incomingData) {
    // Update the first LOD with the new data...
    // ADC 1 -> Channel 1
    lodBuffers[0].minBuffer.adcReadings[0][0] = incomingData.adcReadings[0][0] < lodBuffers[0].minBuffer.adcReadings[0][0] ? incomingData.adcReadings[0][0] : lodBuffers[0].minBuffer.adcReadings[0][0];
    lodBuffers[0].maxBuffer.adcReadings[0][0] = incomingData.adcReadings[0][0] > lodBuffers[0].maxBuffer.adcReadings[0][0] ? incomingData.adcReadings[0][0] : lodBuffers[0].maxBuffer.adcReadings[0][0];
    lodBuffers[0].avgBuffer.adcReadings[0][0] += incomingData.adcReadings[0][0] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 2
    lodBuffers[0].minBuffer.adcReadings[0][1] = incomingData.adcReadings[0][1] < lodBuffers[0].minBuffer.adcReadings[0][1] ? incomingData.adcReadings[0][1] : lodBuffers[0].minBuffer.adcReadings[0][1];
    lodBuffers[0].maxBuffer.adcReadings[0][1] = incomingData.adcReadings[0][1] > lodBuffers[0].maxBuffer.adcReadings[0][1] ? incomingData.adcReadings[0][1] : lodBuffers[0].maxBuffer.adcReadings[0][1];
    lodBuffers[0].avgBuffer.adcReadings[0][1] += incomingData.adcReadings[0][1] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 3
    lodBuffers[0].minBuffer.adcReadings[0][2] = incomingData.adcReadings[0][2] < lodBuffers[0].minBuffer.adcReadings[0][2] ? incomingData.adcReadings[0][2] : lodBuffers[0].minBuffer.adcReadings[0][2];
    lodBuffers[0].maxBuffer.adcReadings[0][2] = incomingData.adcReadings[0][2] > lodBuffers[0].maxBuffer.adcReadings[0][2] ? incomingData.adcReadings[0][2] : lodBuffers[0].maxBuffer.adcReadings[0][2];
    lodBuffers[0].avgBuffer.adcReadings[0][2] += incomingData.adcReadings[0][2] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 4
    lodBuffers[0].minBuffer.adcReadings[0][3] = incomingData.adcReadings[0][3] < lodBuffers[0].minBuffer.adcReadings[0][3] ? incomingData.adcReadings[0][3] : lodBuffers[0].minBuffer.adcReadings[0][3];
    lodBuffers[0].maxBuffer.adcReadings[0][3] = incomingData.adcReadings[0][3] > lodBuffers[0].maxBuffer.adcReadings[0][3] ? incomingData.adcReadings[0][3] : lodBuffers[0].maxBuffer.adcReadings[0][3];
    lodBuffers[0].avgBuffer.adcReadings[0][3] += incomingData.adcReadings[0][3] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 5
    lodBuffers[0].minBuffer.adcReadings[0][4] = incomingData.adcReadings[0][4] < lodBuffers[0].minBuffer.adcReadings[0][4] ? incomingData.adcReadings[0][4] : lodBuffers[0].minBuffer.adcReadings[0][4];
    lodBuffers[0].maxBuffer.adcReadings[0][4] = incomingData.adcReadings[0][4] > lodBuffers[0].maxBuffer.adcReadings[0][4] ? incomingData.adcReadings[0][4] : lodBuffers[0].maxBuffer.adcReadings[0][4];
    lodBuffers[0].avgBuffer.adcReadings[0][4] += incomingData.adcReadings[0][4] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 6
    lodBuffers[0].minBuffer.adcReadings[0][5] = incomingData.adcReadings[0][5] < lodBuffers[0].minBuffer.adcReadings[0][5] ? incomingData.adcReadings[0][5] : lodBuffers[0].minBuffer.adcReadings[0][5];
    lodBuffers[0].maxBuffer.adcReadings[0][5] = incomingData.adcReadings[0][5] > lodBuffers[0].maxBuffer.adcReadings[0][5] ? incomingData.adcReadings[0][5] : lodBuffers[0].maxBuffer.adcReadings[0][5];
    lodBuffers[0].avgBuffer.adcReadings[0][5] += incomingData.adcReadings[0][5] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 7
    lodBuffers[0].minBuffer.adcReadings[0][6] = incomingData.adcReadings[0][6] < lodBuffers[0].minBuffer.adcReadings[0][6] ? incomingData.adcReadings[0][6] : lodBuffers[0].minBuffer.adcReadings[0][6];
    lodBuffers[0].maxBuffer.adcReadings[0][6] = incomingData.adcReadings[0][6] > lodBuffers[0].maxBuffer.adcReadings[0][6] ? incomingData.adcReadings[0][6] : lodBuffers[0].maxBuffer.adcReadings[0][6];
    lodBuffers[0].avgBuffer.adcReadings[0][6] += incomingData.adcReadings[0][6] / LOD_SAMPLE_INTERVAL;
    // ADC 1 -> Channel 8
    lodBuffers[0].minBuffer.adcReadings[0][7] = incomingData.adcReadings[0][7] < lodBuffers[0].minBuffer.adcReadings[0][7] ? incomingData.adcReadings[0][7] : lodBuffers[0].minBuffer.adcReadings[0][7];
    lodBuffers[0].maxBuffer.adcReadings[0][7] = incomingData.adcReadings[0][7] > lodBuffers[0].maxBuffer.adcReadings[0][7] ? incomingData.adcReadings[0][7] : lodBuffers[0].maxBuffer.adcReadings[0][7];
    lodBuffers[0].avgBuffer.adcReadings[0][7] += incomingData.adcReadings[0][7] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 1
    lodBuffers[0].minBuffer.adcReadings[1][0] = incomingData.adcReadings[1][0] < lodBuffers[0].minBuffer.adcReadings[1][0] ? incomingData.adcReadings[1][0] : lodBuffers[0].minBuffer.adcReadings[1][0];
    lodBuffers[0].maxBuffer.adcReadings[1][0] = incomingData.adcReadings[1][0] > lodBuffers[0].maxBuffer.adcReadings[1][0] ? incomingData.adcReadings[1][0] : lodBuffers[0].maxBuffer.adcReadings[1][0];
    lodBuffers[0].avgBuffer.adcReadings[1][0] += incomingData.adcReadings[1][0] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 2
    lodBuffers[0].minBuffer.adcReadings[1][1] = incomingData.adcReadings[1][1] < lodBuffers[0].minBuffer.adcReadings[1][1] ? incomingData.adcReadings[1][1] : lodBuffers[0].minBuffer.adcReadings[1][1];
    lodBuffers[0].maxBuffer.adcReadings[1][1] = incomingData.adcReadings[1][1] > lodBuffers[0].maxBuffer.adcReadings[1][1] ? incomingData.adcReadings[1][1] : lodBuffers[0].maxBuffer.adcReadings[1][1];
    lodBuffers[0].avgBuffer.adcReadings[1][1] += incomingData.adcReadings[1][1] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 3
    lodBuffers[0].minBuffer.adcReadings[1][2] = incomingData.adcReadings[1][2] < lodBuffers[0].minBuffer.adcReadings[1][2] ? incomingData.adcReadings[1][2] : lodBuffers[0].minBuffer.adcReadings[1][2];
    lodBuffers[0].maxBuffer.adcReadings[1][2] = incomingData.adcReadings[1][2] > lodBuffers[0].maxBuffer.adcReadings[1][2] ? incomingData.adcReadings[1][2] : lodBuffers[0].maxBuffer.adcReadings[1][2];
    lodBuffers[0].avgBuffer.adcReadings[1][2] += incomingData.adcReadings[1][2] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 4
    lodBuffers[0].minBuffer.adcReadings[1][3] = incomingData.adcReadings[1][3] < lodBuffers[0].minBuffer.adcReadings[1][3] ? incomingData.adcReadings[1][3] : lodBuffers[0].minBuffer.adcReadings[1][3];
    lodBuffers[0].maxBuffer.adcReadings[1][3] = incomingData.adcReadings[1][3] > lodBuffers[0].maxBuffer.adcReadings[1][3] ? incomingData.adcReadings[1][3] : lodBuffers[0].maxBuffer.adcReadings[1][3];
    lodBuffers[0].avgBuffer.adcReadings[1][3] += incomingData.adcReadings[1][3] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 5
    lodBuffers[0].minBuffer.adcReadings[1][4] = incomingData.adcReadings[1][4] < lodBuffers[0].minBuffer.adcReadings[1][4] ? incomingData.adcReadings[1][4] : lodBuffers[0].minBuffer.adcReadings[1][4];
    lodBuffers[0].maxBuffer.adcReadings[1][4] = incomingData.adcReadings[1][4] > lodBuffers[0].maxBuffer.adcReadings[1][4] ? incomingData.adcReadings[1][4] : lodBuffers[0].maxBuffer.adcReadings[1][4];
    lodBuffers[0].avgBuffer.adcReadings[1][4] += incomingData.adcReadings[1][4] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 6
    lodBuffers[0].minBuffer.adcReadings[1][5] = incomingData.adcReadings[1][5] < lodBuffers[0].minBuffer.adcReadings[1][5] ? incomingData.adcReadings[1][5] : lodBuffers[0].minBuffer.adcReadings[1][5];
    lodBuffers[0].maxBuffer.adcReadings[1][5] = incomingData.adcReadings[1][5] > lodBuffers[0].maxBuffer.adcReadings[1][5] ? incomingData.adcReadings[1][5] : lodBuffers[0].maxBuffer.adcReadings[1][5];
    lodBuffers[0].avgBuffer.adcReadings[1][5] += incomingData.adcReadings[1][5] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 7
    lodBuffers[0].minBuffer.adcReadings[1][6] = incomingData.adcReadings[1][6] < lodBuffers[0].minBuffer.adcReadings[1][6] ? incomingData.adcReadings[1][6] : lodBuffers[0].minBuffer.adcReadings[1][6];
    lodBuffers[0].maxBuffer.adcReadings[1][6] = incomingData.adcReadings[1][6] > lodBuffers[0].maxBuffer.adcReadings[1][6] ? incomingData.adcReadings[1][6] : lodBuffers[0].maxBuffer.adcReadings[1][6];
    lodBuffers[0].avgBuffer.adcReadings[1][6] += incomingData.adcReadings[1][6] / LOD_SAMPLE_INTERVAL;
    // ADC 2 -> Channel 8
    lodBuffers[0].minBuffer.adcReadings[1][7] = incomingData.adcReadings[1][7] < lodBuffers[0].minBuffer.adcReadings[1][7] ? incomingData.adcReadings[1][7] : lodBuffers[0].minBuffer.adcReadings[1][7];
    lodBuffers[0].maxBuffer.adcReadings[1][7] = incomingData.adcReadings[1][7] > lodBuffers[0].maxBuffer.adcReadings[1][7] ? incomingData.adcReadings[1][7] : lodBuffers[0].maxBuffer.adcReadings[1][7];
    lodBuffers[0].avgBuffer.adcReadings[1][7] += incomingData.adcReadings[1][7] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 1
    lodBuffers[0].minBuffer.adcReadings[2][0] = incomingData.adcReadings[2][0] < lodBuffers[0].minBuffer.adcReadings[2][0] ? incomingData.adcReadings[2][0] : lodBuffers[0].minBuffer.adcReadings[2][0];
    lodBuffers[0].maxBuffer.adcReadings[2][0] = incomingData.adcReadings[2][0] > lodBuffers[0].maxBuffer.adcReadings[2][0] ? incomingData.adcReadings[2][0] : lodBuffers[0].maxBuffer.adcReadings[2][0];
    lodBuffers[0].avgBuffer.adcReadings[2][0] += incomingData.adcReadings[2][0] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 2
    lodBuffers[0].minBuffer.adcReadings[2][1] = incomingData.adcReadings[2][1] < lodBuffers[0].minBuffer.adcReadings[2][1] ? incomingData.adcReadings[2][1] : lodBuffers[0].minBuffer.adcReadings[2][1];
    lodBuffers[0].maxBuffer.adcReadings[2][1] = incomingData.adcReadings[2][1] > lodBuffers[0].maxBuffer.adcReadings[2][1] ? incomingData.adcReadings[2][1] : lodBuffers[0].maxBuffer.adcReadings[2][1];
    lodBuffers[0].avgBuffer.adcReadings[2][1] += incomingData.adcReadings[2][1] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 3
    lodBuffers[0].minBuffer.adcReadings[2][2] = incomingData.adcReadings[2][2] < lodBuffers[0].minBuffer.adcReadings[2][2] ? incomingData.adcReadings[2][2] : lodBuffers[0].minBuffer.adcReadings[2][2];
    lodBuffers[0].maxBuffer.adcReadings[2][2] = incomingData.adcReadings[2][2] > lodBuffers[0].maxBuffer.adcReadings[2][2] ? incomingData.adcReadings[2][2] : lodBuffers[0].maxBuffer.adcReadings[2][2];
    lodBuffers[0].avgBuffer.adcReadings[2][2] += incomingData.adcReadings[2][2] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 4
    lodBuffers[0].minBuffer.adcReadings[2][3] = incomingData.adcReadings[2][3] < lodBuffers[0].minBuffer.adcReadings[2][3] ? incomingData.adcReadings[2][3] : lodBuffers[0].minBuffer.adcReadings[2][3];
    lodBuffers[0].maxBuffer.adcReadings[2][3] = incomingData.adcReadings[2][3] > lodBuffers[0].maxBuffer.adcReadings[2][3] ? incomingData.adcReadings[2][3] : lodBuffers[0].maxBuffer.adcReadings[2][3];
    lodBuffers[0].avgBuffer.adcReadings[2][3] += incomingData.adcReadings[2][3] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 5
    lodBuffers[0].minBuffer.adcReadings[2][4] = incomingData.adcReadings[2][4] < lodBuffers[0].minBuffer.adcReadings[2][4] ? incomingData.adcReadings[2][4] : lodBuffers[0].minBuffer.adcReadings[2][4];
    lodBuffers[0].maxBuffer.adcReadings[2][4] = incomingData.adcReadings[2][4] > lodBuffers[0].maxBuffer.adcReadings[2][4] ? incomingData.adcReadings[2][4] : lodBuffers[0].maxBuffer.adcReadings[2][4];
    lodBuffers[0].avgBuffer.adcReadings[2][4] += incomingData.adcReadings[2][4] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 6
    lodBuffers[0].minBuffer.adcReadings[2][5] = incomingData.adcReadings[2][5] < lodBuffers[0].minBuffer.adcReadings[2][5] ? incomingData.adcReadings[2][5] : lodBuffers[0].minBuffer.adcReadings[2][5];
    lodBuffers[0].maxBuffer.adcReadings[2][5] = incomingData.adcReadings[2][5] > lodBuffers[0].maxBuffer.adcReadings[2][5] ? incomingData.adcReadings[2][5] : lodBuffers[0].maxBuffer.adcReadings[2][5];
    lodBuffers[0].avgBuffer.adcReadings[2][5] += incomingData.adcReadings[2][5] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 7
    lodBuffers[0].minBuffer.adcReadings[2][6] = incomingData.adcReadings[2][6] < lodBuffers[0].minBuffer.adcReadings[2][6] ? incomingData.adcReadings[2][6] : lodBuffers[0].minBuffer.adcReadings[2][6];
    lodBuffers[0].maxBuffer.adcReadings[2][6] = incomingData.adcReadings[2][6] > lodBuffers[0].maxBuffer.adcReadings[2][6] ? incomingData.adcReadings[2][6] : lodBuffers[0].maxBuffer.adcReadings[2][6];
    lodBuffers[0].avgBuffer.adcReadings[2][6] += incomingData.adcReadings[2][6] / LOD_SAMPLE_INTERVAL;
    // ADC 3 -> Channel 8
    lodBuffers[0].minBuffer.adcReadings[2][7] = incomingData.adcReadings[2][7] < lodBuffers[0].minBuffer.adcReadings[2][7] ? incomingData.adcReadings[2][7] : lodBuffers[0].minBuffer.adcReadings[2][7];
    lodBuffers[0].maxBuffer.adcReadings[2][7] = incomingData.adcReadings[2][7] > lodBuffers[0].maxBuffer.adcReadings[2][7] ? incomingData.adcReadings[2][7] : lodBuffers[0].maxBuffer.adcReadings[2][7];
    lodBuffers[0].avgBuffer.adcReadings[2][7] += incomingData.adcReadings[2][7] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 1
    lodBuffers[0].minBuffer.adcReadings[3][0] = incomingData.adcReadings[3][0] < lodBuffers[0].minBuffer.adcReadings[3][0] ? incomingData.adcReadings[3][0] : lodBuffers[0].minBuffer.adcReadings[3][0];
    lodBuffers[0].maxBuffer.adcReadings[3][0] = incomingData.adcReadings[3][0] > lodBuffers[0].maxBuffer.adcReadings[3][0] ? incomingData.adcReadings[3][0] : lodBuffers[0].maxBuffer.adcReadings[3][0];
    lodBuffers[0].avgBuffer.adcReadings[3][0] += incomingData.adcReadings[3][0] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 2
    lodBuffers[0].minBuffer.adcReadings[3][1] = incomingData.adcReadings[3][1] < lodBuffers[0].minBuffer.adcReadings[3][1] ? incomingData.adcReadings[3][1] : lodBuffers[0].minBuffer.adcReadings[3][1];
    lodBuffers[0].maxBuffer.adcReadings[3][1] = incomingData.adcReadings[3][1] > lodBuffers[0].maxBuffer.adcReadings[3][1] ? incomingData.adcReadings[3][1] : lodBuffers[0].maxBuffer.adcReadings[3][1];
    lodBuffers[0].avgBuffer.adcReadings[3][1] += incomingData.adcReadings[3][1] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 3
    lodBuffers[0].minBuffer.adcReadings[3][2] = incomingData.adcReadings[3][2] < lodBuffers[0].minBuffer.adcReadings[3][2] ? incomingData.adcReadings[3][2] : lodBuffers[0].minBuffer.adcReadings[3][2];
    lodBuffers[0].maxBuffer.adcReadings[3][2] = incomingData.adcReadings[3][2] > lodBuffers[0].maxBuffer.adcReadings[3][2] ? incomingData.adcReadings[3][2] : lodBuffers[0].maxBuffer.adcReadings[3][2];
    lodBuffers[0].avgBuffer.adcReadings[3][2] += incomingData.adcReadings[3][2] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 4
    lodBuffers[0].minBuffer.adcReadings[3][3] = incomingData.adcReadings[3][3] < lodBuffers[0].minBuffer.adcReadings[3][3] ? incomingData.adcReadings[3][3] : lodBuffers[0].minBuffer.adcReadings[3][3];
    lodBuffers[0].maxBuffer.adcReadings[3][3] = incomingData.adcReadings[3][3] > lodBuffers[0].maxBuffer.adcReadings[3][3] ? incomingData.adcReadings[3][3] : lodBuffers[0].maxBuffer.adcReadings[3][3];
    lodBuffers[0].avgBuffer.adcReadings[3][3] += incomingData.adcReadings[3][3] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 5
    lodBuffers[0].minBuffer.adcReadings[3][4] = incomingData.adcReadings[3][4] < lodBuffers[0].minBuffer.adcReadings[3][4] ? incomingData.adcReadings[3][4] : lodBuffers[0].minBuffer.adcReadings[3][4];
    lodBuffers[0].maxBuffer.adcReadings[3][4] = incomingData.adcReadings[3][4] > lodBuffers[0].maxBuffer.adcReadings[3][4] ? incomingData.adcReadings[3][4] : lodBuffers[0].maxBuffer.adcReadings[3][4];
    lodBuffers[0].avgBuffer.adcReadings[3][4] += incomingData.adcReadings[3][4] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 6
    lodBuffers[0].minBuffer.adcReadings[3][5] = incomingData.adcReadings[3][5] < lodBuffers[0].minBuffer.adcReadings[3][5] ? incomingData.adcReadings[3][5] : lodBuffers[0].minBuffer.adcReadings[3][5];
    lodBuffers[0].maxBuffer.adcReadings[3][5] = incomingData.adcReadings[3][5] > lodBuffers[0].maxBuffer.adcReadings[3][5] ? incomingData.adcReadings[3][5] : lodBuffers[0].maxBuffer.adcReadings[3][5];
    lodBuffers[0].avgBuffer.adcReadings[3][5] += incomingData.adcReadings[3][5] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 7
    lodBuffers[0].minBuffer.adcReadings[3][6] = incomingData.adcReadings[3][6] < lodBuffers[0].minBuffer.adcReadings[3][6] ? incomingData.adcReadings[3][6] : lodBuffers[0].minBuffer.adcReadings[3][6];
    lodBuffers[0].maxBuffer.adcReadings[3][6] = incomingData.adcReadings[3][6] > lodBuffers[0].maxBuffer.adcReadings[3][6] ? incomingData.adcReadings[3][6] : lodBuffers[0].maxBuffer.adcReadings[3][6];
    lodBuffers[0].avgBuffer.adcReadings[3][6] += incomingData.adcReadings[3][6] / LOD_SAMPLE_INTERVAL;
    // ADC 4 -> Channel 8
    lodBuffers[0].minBuffer.adcReadings[3][7] = incomingData.adcReadings[3][7] < lodBuffers[0].minBuffer.adcReadings[3][7] ? incomingData.adcReadings[3][7] : lodBuffers[0].minBuffer.adcReadings[3][7];
    lodBuffers[0].maxBuffer.adcReadings[3][7] = incomingData.adcReadings[3][7] > lodBuffers[0].maxBuffer.adcReadings[3][7] ? incomingData.adcReadings[3][7] : lodBuffers[0].maxBuffer.adcReadings[3][7];
    lodBuffers[0].avgBuffer.adcReadings[3][7] += incomingData.adcReadings[3][7] / LOD_SAMPLE_INTERVAL;
    // Diagnostics -> Error Count
    lodBuffers[0].minBuffer.errorCount = incomingData.errorCount < lodBuffers[0].minBuffer.errorCount ? incomingData.errorCount : lodBuffers[0].minBuffer.errorCount;
    lodBuffers[0].maxBuffer.errorCount = incomingData.errorCount > lodBuffers[0].maxBuffer.errorCount ? incomingData.errorCount : lodBuffers[0].maxBuffer.errorCount;
    lodBuffers[0].avgBuffer.errorCount += incomingData.errorCount / LOD_SAMPLE_INTERVAL;
    // Diagnostics -> Last Error Cause
    lodBuffers[0].minBuffer.lastErrorCode = incomingData.lastErrorCode;
    lodBuffers[0].maxBuffer.lastErrorCode = incomingData.lastErrorCode;
    lodBuffers[0].avgBuffer.lastErrorCode += incomingData.lastErrorCode;

    lodBuffers[0].progress += 1;
    // If we have written enough samples to the first LOD...
    if (lodBuffers[0].progress == LOD_SAMPLE_INTERVAL) {
        // Save the parsed_formatrmation and propogate it up to higher LODs
        // as necessary.
        commitLod(0);
    }
}
