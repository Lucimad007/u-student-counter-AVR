#include "keypad.h"


char keypad[4][3] = {
	{'7', '8', '9'},
	{'4', '5', '6'},
	{'1', '2', '3'},
	{'o', '0', '='}
};

// Function to convert an unsigned integer to a string representation
void num_to_string(unsigned int number, char* strBuffer) {
	int index = 0; // Initialize buffer index
	if (number == 0) {
		strBuffer[index++] = '0'; // Handle zero case
	}

	// Extract digits from the number
	while (number > 0) {
		strBuffer[index++] = (number % 10) + '0'; // Convert digit to character
		number /= 10; // Reduce number
	}
	strBuffer[index] = '\0'; // Null-terminate the string

	// Reverse the string to get the correct representation
	for (int j = 0, k = index - 1; j < k; j++, k--) {
		char tempChar = strBuffer[j];
		strBuffer[j] = strBuffer[k];
		strBuffer[k] = tempChar;
	}
}

// Function to initialize the keypad port configuration
void keypad_init(void) {
	KEYPAD_PORT_DIR = 0xF0; // Set A0 to A3 as input, A4 to A7 as output
	KEYPAD_PORT_OUT = 0xFF; // Set all output pins high
}

// Function to scan the keypad and return the pressed key
char scan_keypad(void) {
	unsigned char colStatus, rowStatus;

	// Wait until all keys are released
	do {
		KEYPAD_PORT_OUT = KEYPAD_PORT_OUT & 0x0F; // Clear output for rows
		colStatus = KEYPAD_PORT_IN & 0x0F; // Read input for columns
	} while (colStatus != 0x0F); // Continue until all keys are released

	// Wait for a key press
	do {
		do {
			_delay_us(2); // Debounce delay
			colStatus = KEYPAD_PORT_IN & 0x0F; // Read input for columns
		} while (colStatus != 0x0F); // Wait for release
		_delay_us(2); // Debounce delay
		colStatus = KEYPAD_PORT_IN & 0x0F; // Read input again
	} while (colStatus != 0x0F); // Wait for release

	// Check each row to find which button is pressed
	while (1) {
		KEYPAD_PORT_OUT = 0xEF; // Activate first row
		colStatus = KEYPAD_PORT_IN & 0x0F; // Check input
		if (colStatus != 0x0F) {
			rowStatus = 0; // First row detected
			break; // Exit the loop
		}
		KEYPAD_PORT_OUT = 0xDF; // Activate second row
		colStatus = KEYPAD_PORT_IN & 0x0F; // Check input
		if (colStatus != 0x0F) {
			rowStatus = 1; // Second row detected
			break; // Exit the loop
		}
		KEYPAD_PORT_OUT = 0xBF; // Activate third row
		colStatus = KEYPAD_PORT_IN & 0x0F; // Check input
		if (colStatus != 0x0F) {
			rowStatus = 2; // Third row detected
			break; // Exit the loop
		}
		KEYPAD_PORT_OUT = 0x7F; // Activate fourth row
		colStatus = KEYPAD_PORT_IN & 0x0F; // Check input
		if (colStatus != 0x0F) {
			rowStatus = 3; // Fourth row detected
			break; // Exit the loop
		}
	}

	// Determine which key was pressed in the active row
	if (colStatus == 0x0E) {
		return keypad[rowStatus][0]; // First column
	}
	if (colStatus == 0x0D) {
		return keypad[rowStatus][1]; // Second column
	}
	if (colStatus == 0x0B) {
		return keypad[rowStatus][2]; // Third column
	}
	return keypad[rowStatus][3]; // Fourth column
}
