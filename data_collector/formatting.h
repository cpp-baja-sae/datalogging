#ifndef FORMATTING_H_
#define FORMATTING_H_

// This file and formatting.ino are responsible for taking new data from
// tasks.ino and formatting it into the multiple different resolutions we have,
// then storing that data into individual files. It uses the code auto-generated
// in data_ops.cpp for the actual resolution scaling operations.

/**
 * This function sets up data necessary for formatting the extra LODs from
 * incoming data created by tasks.ino.
 */
void initialFormattingSetup();

/**
 * Starts recording incoming data to the specified slot. If a datalog already
 * exists there, it will be overwritten. If another datalog is currently being
 * written to, endCurrentDatalog() will automatically be called.
 */
void beginNewDatalog(int slot);

/**
 * -1 if no datalog is currently being recorded, otherwise the slot it is being
 * recorded to.
 */
extern int currentDatalog;

/**
 * Stops recording the current datalog. Does nothing if no datalog is being
 * recorded.
 */
void endCurrentDatalog();

/**
 * Regularly call this function to format and send new data created by tasks.ino
 * to the individual files for each LOD.
 */
void handleNewData();

#endif /* FORMATTING_H_ */