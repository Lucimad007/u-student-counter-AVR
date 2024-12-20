#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA

void keypad_init(void);
char scan_keypad(void);
void num_to_string(unsigned int num, char* buffer);

#endif /* KEYPAD_H_ */