#ifndef SERIAL_COMMANDS_H_
#define SERIAL_COMMANDS_H_

/**
 * This function checks if any commands have been sent over the radio or USB
 * port and responds to them appropriately. If a request for a file has been
 * sent, the task interrupt will be temporarily disabled for max transfer
 * speed.
 */
void handleWaitingCommands();

#endif /* SERIAL_COMMANDS_H_ */