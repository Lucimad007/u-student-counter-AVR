/*
 * keypad.h
 *
 *  Created on: May 1, 2019
 *      Author: Mahmoud 10
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*KEYPAD NUMBER OF ROWS AND COLUMNS CONFIGURATIONS*/
#define N_col 3
#define N_row 4

/* KEYPAD PORT CONFIGURATION */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

/* getting the pressed keypad key */
uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
