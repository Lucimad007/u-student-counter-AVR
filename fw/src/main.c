#include "micro_config.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "usart.h"
#include "ultrasonic.h"
#include "eeprom.h"

#define STUDENT_NUMBER_LENGTH 8

uint16 EEPROM_START_ADDRESS = 0;


int StudentCount = 0;
long int StudentCodes[100];

typedef enum {
	STATE_MAIN_MENU,
	STATE_ATTENDANCE_INIT,
	STATE_STUDENT_MANAGEMENT,
	STATE_VIEW_PRESENT,
	STATE_TEMPERATURE_MONITOR,
	STATE_RETRIEVE_STUDENT_DATA,
	STATE_TRAFFIC_MONITOR
} State;

typedef enum{
	ATTEND_READY,
	SUBMIT_CODE,
	NONE
} AttendInitSubMenu;

typedef enum{
	FIRST_MENU,
	SECOND_MENU,
	THIRD_MENU
} MenuNumber;

// global variables
State currentState = STATE_MAIN_MENU;
MenuNumber menuNumber = FIRST_MENU;
AttendInitSubMenu attendInitSubeMenu = NONE;
int choice = '0';




// display menus
void displayGuideMenu(void);
void displayFirstMainMenu(void);
void displaySecondMainMenu(void);
void displayThirdMainMenu(void);
void displayAttendInitMenu(void);
void displayStudentManagementMenu(void);

// state machine
void handleAttendanceInit(void);
void handleSubmitCode(void);
void handleStudentManagement(void);
void handleViewPresentStudents(void);
void handleTemperatureMonitor(void);
void handleRetrieveStudentData(void);
void handleTrafficMonitor(void);

void loadStudentCodesFromEEPROM(void);
void saveStudentNumberInEEPROM(void);
int CheckStudentNumberValidation(long int StudentNum);

bool areEqual(char* str1, char* str2, unsigned char minLength);

#include "micro_config.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "usart.h"
#include "ultrasonic.h"
#include "eeprom.h"
#include "rfid.h"

#define STUDENT_NUMBER_LENGTH 8

uint16 EEPROM_START_ADDRESS = 0;

int StudentCount = 0;
long int StudentCodes[100];

typedef enum {
	STATE_MAIN_MENU,
	STATE_ATTENDANCE_INIT,
	STATE_STUDENT_MANAGEMENT,
	STATE_VIEW_PRESENT,
	STATE_TEMPERATURE_MONITOR,
	STATE_RETRIEVE_STUDENT_DATA,
	STATE_TRAFFIC_MONITOR
} State;

State currentState = STATE_MAIN_MENU;

//int main(void) {
	//USART_init(MYUBRR);
	//HCSR04Init();
	//LCD_Init();
	//RFID_Init(); // Initialize RFID system
//
	//while (1) {
		//char rfid_data[15];
		//RFID_Read(rfid_data); // Read RFID tag
		//// Add RFID validation and logic here
	//}
//
	//return 0;
//}


int main(void) {
	
	USART_init(MYUBRR);
	HCSR04Init();
	
	LCD_Init();
	keypad_init();
	displayGuideMenu();
	scan_keypad();
	displayFirstMainMenu();

	while (1) {
		char ch = scan_keypad();
		choice = ch - '0';
		if (ch == '=') {
			displayGuideMenu();
			// Wait for another key press before resuming the state logic
			_delay_ms(200); // Debounce delay
			continue; // Skip the state logic and resume
		}
		if (ch == '=') {
			displayGuideMenu();
			// Wait for another key press before resuming the state logic
			_delay_ms(200); // Debounce delay
			continue; // Skip the state logic and resume
		}
		switch (currentState) {
			case STATE_MAIN_MENU:
			switch (menuNumber)
			{
				case FIRST_MENU:
				switch (choice)
				{
					case 1:
					currentState = STATE_ATTENDANCE_INIT;
					displayAttendInitMenu();
					break;
					case 2:
					currentState = STATE_STUDENT_MANAGEMENT;
					displayStudentManagementMenu();
					handleStudentManagement();
					currentState = STATE_MAIN_MENU;
					menuNumber = FIRST_MENU;
					displayFirstMainMenu();
					break;
					case 9:
					menuNumber = SECOND_MENU;
					displaySecondMainMenu();
					break;
				}
				break;
				case SECOND_MENU:
				switch (choice)
				{
					case 3:
					currentState = STATE_VIEW_PRESENT;
					handleViewPresentStudents();
					break;
					case 4:
					currentState = STATE_TEMPERATURE_MONITOR;
					handleTemperatureMonitor();
					break;
					case 7:
					menuNumber = FIRST_MENU;
					displayFirstMainMenu();
					break;
					case 9:
					menuNumber = THIRD_MENU;
					displayThirdMainMenu();
					break;
				}
				break;
				case THIRD_MENU:
				switch (choice)
				{
					case 5:
					currentState = STATE_RETRIEVE_STUDENT_DATA;
					handleRetrieveStudentData();
					break;
					case 6:
					currentState = STATE_TRAFFIC_MONITOR;
					handleTrafficMonitor();
					break;
					case 7:
					menuNumber = SECOND_MENU;
					displaySecondMainMenu();
					break;
				}
				break;
			}
			break;
			

			case STATE_ATTENDANCE_INIT:
			switch (choice)
			{
				case 1:
				handleSubmitCode();
				currentState = STATE_ATTENDANCE_INIT;	// just to explicitly show it
				displayAttendInitMenu();
				break;
				case 2:
				currentState = STATE_MAIN_MENU;
				menuNumber = FIRST_MENU;
				displayFirstMainMenu();
				break;
			}
			break;

			case STATE_STUDENT_MANAGEMENT:
			currentState = STATE_MAIN_MENU;
			break;

			case STATE_VIEW_PRESENT:
			// pressing any key is ok
			currentState = STATE_MAIN_MENU;
			menuNumber = FIRST_MENU;
			displayFirstMainMenu();
			break;

			case STATE_TEMPERATURE_MONITOR:
			currentState = STATE_MAIN_MENU;
			menuNumber = FIRST_MENU;
			displayFirstMainMenu();
			break;
			case STATE_RETRIEVE_STUDENT_DATA:
			currentState = STATE_MAIN_MENU;
			menuNumber = FIRST_MENU;
			displayFirstMainMenu();
			break;
			case STATE_TRAFFIC_MONITOR:
			currentState = STATE_MAIN_MENU;
			menuNumber = FIRST_MENU;
			displayFirstMainMenu();
			break;

			
		}
	}
	return 0;
}

void displayGuideMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0, 0, "7:=BACK  9:=NEXT");
	LCD_String_xy(1, 0, "press any key...");
}


void displayFirstMainMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0,0, "1.Attend init");    // Attendance is too long
	LCD_String_xy(1,0, "2.student mgmnt");
}

void displaySecondMainMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0,0, "3.View Presents");
	LCD_String_xy(1,0, "4.Temperature");
}

void displayThirdMainMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0,0, "5.student data");
	LCD_String_xy(1,0, "6.Trafic monitor"); // I know Traffic has 2 'f's but it is too long !
}

void displayAttendInitMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0,0, "Attendance Ready");
	LCD_String_xy(1,0, "1.submit  2.exit");
}

void displayStudentManagementMenu(void)
{
	LCD_Clear();
	LCD_String_xy(0,0, "Search Student:");
}

void handleAttendanceInit(void)
{
	switch (attendInitSubeMenu)
	{
		case ATTEND_READY:
		if(choice == 1)
		{
			handleSubmitCode();
			currentState = STATE_MAIN_MENU;
			attendInitSubeMenu = NONE;
			displayFirstMainMenu();
		}
		else if(choice == 2)
		{
			// exit
			currentState = STATE_MAIN_MENU;
			attendInitSubeMenu = NONE;
			displayFirstMainMenu();
		}
		break;
		case NONE:
		if(choice == 1)
		attendInitSubeMenu = ATTEND_READY;
		break;
	}
}

void handleSubmitCode(void)
{
	char key;
	long int tmpStudentCode=0,StudentCode=0;
	LCD_Clear();
	LCD_String_xy(0,0,NULL);
	LCD_String("Student Number:");
	LCD_String_xy(1,0,NULL);
	char buffer[STUDENT_NUMBER_LENGTH+1];
	unsigned char index = 0;
	unsigned char chars = 0;
	while (chars < (STUDENT_NUMBER_LENGTH + 1))
	{
		key=scan_keypad();
		if(key!='o'){
			tmpStudentCode=tmpStudentCode*10 + (key-'0');
			buffer[index++] = key;
			LCD_Char(key);
		}
		else{
			break;
		}
		chars++;
	}
	buffer[index] = '\0';
	_delay_ms(200);
	if(CheckStudentNumberValidation(tmpStudentCode)){
		char temp[STUDENT_NUMBER_LENGTH+1];
		temp[STUDENT_NUMBER_LENGTH] = '\0';
		for(unsigned char i = 0; i < StudentCount; i++)
		{
			EEPROM_ReadString(i * STUDENT_NUMBER_LENGTH, temp, STUDENT_NUMBER_LENGTH);
			if(areEqual(buffer, temp, STUDENT_NUMBER_LENGTH))
			{
				LCD_Clear();
				buzzer_init();
				_delay_ms(1000);
				small_beep(100);
				LCD_String_xy(0, 0, "already taken!");
				_delay_ms(500);
				return;
			}
		}
		EEPROM_WriteString(StudentCount * STUDENT_NUMBER_LENGTH, buffer);
		StudentCode=tmpStudentCode;
		StudentCodes[StudentCount]=StudentCode;
		StudentCount++;
		LCD_Clear();
		LCD_String_xy(0,0,"Code Accepted!");
		_delay_ms(1000);
	}
	else{
		LCD_Clear();
		LCD_String_xy(0, 0, "Not Accepted!");
		buzzer_init();
		_delay_ms(100);
		small_beep(100);
		buzzer_stop();
		return -1;
	}
}

void handleStudentManagement(void)
{
	char key;
	long int StudentNumber=0;
	LCD_String_xy(1, 0, NULL);
	char buffer[STUDENT_NUMBER_LENGTH+1];
	unsigned char index = 0;
	unsigned char chars = 0;
	while (chars < (STUDENT_NUMBER_LENGTH + 1))
	{
		key=scan_keypad();
		if(key!='o'){
			StudentNumber=StudentNumber*10 + (key-'0');
			buffer[index++] = key;
			LCD_Char(key);
		}
		else{
			break;
		}
	}
	buffer[index] = '\0';
	_delay_ms(200);
	char temp[STUDENT_NUMBER_LENGTH+1];
	temp[STUDENT_NUMBER_LENGTH] = '\0';
	for(unsigned char i = 0; i < StudentCount; i++)
	{
		EEPROM_ReadString(i * STUDENT_NUMBER_LENGTH, temp, STUDENT_NUMBER_LENGTH);
		if(areEqual(buffer, temp, STUDENT_NUMBER_LENGTH))
		{
			LCD_Clear();
			LCD_String_xy(0, 0, "Student Found!");
			_delay_ms(500);
			return;
		}
	}
	LCD_Clear();
	LCD_String_xy(0, 0, "Student");
	LCD_String_xy(1, 0, "Not Found!");
	_delay_ms(1000);
	return;
}

void handleViewPresentStudents(void)
{
	int Scroller=0;
	char key;
	LCD_Clear();
	char str[16];
	sprintf(str, "Presents: %d", StudentCount);
	LCD_String_xy(0, 0, str);
	_delay_ms(100);

	if(StudentCount == 0)
	{
		LCD_String_xy(1,0, "No Students.");
		return;
	}

	// here we have at least 1 student displayed by default
	char buff[STUDENT_NUMBER_LENGTH];
	EEPROM_ReadString(Scroller * STUDENT_NUMBER_LENGTH, buff, STUDENT_NUMBER_LENGTH);
	LCD_String_xy(1, 0, buff);

	while(1){
		key=scan_keypad();
		if(key=='9'){
			Scroller=(Scroller+1) >= StudentCount ? Scroller : (Scroller+1);
		}
		else if(key=='7'){
			Scroller=(Scroller-1) < 0 ? 0 : (Scroller-1);
		}
		else if(key=='o'){
			break;
		}
		char buff[8];
		EEPROM_ReadString(Scroller * STUDENT_NUMBER_LENGTH, buff, STUDENT_NUMBER_LENGTH);
		LCD_String_xy(1, 0, buff);

	}
}

void handleTemperatureMonitor(void)
{
	char Temperature[10];
	float celsius;
	_delay_ms(100);
	//Buzzer_Init();
	//_delay_ms(100);
	LCD_Init();
	_delay_ms(100);
	ADC_Init();
	_delay_ms(100);
	while(1)
	{
		// char c = scan_keypad_nonblock();
		// if(c == '1')
		// 	break;
		//Buzzer_Beep();
		//_delay_ms(1000);
		LCD_String_xy(0,0,"Temperature");
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);
		sprintf(Temperature,"%d%cC  ", (int)celsius, degree_sysmbol);/* convert integer value to ASCII string */
		LCD_String_xy(1,0,Temperature);/* send string data for printing */
		_delay_ms(1000);
		memset(Temperature,0,10);
	}
}

void handleRetrieveStudentData(void)
{
	if(StudentCount == 0)
	{
		LCD_Clear();
		LCD_String_xy(0, 0, "No students");
		LCD_String_xy(1, 0, "to retrieve!");
		return;
	}
	unsigned char i;
	for(i = 0; i < StudentCount; i++)
	{
		char buff[STUDENT_NUMBER_LENGTH];
		EEPROM_ReadString(i * STUDENT_NUMBER_LENGTH, buff, STUDENT_NUMBER_LENGTH);
		UART_SendString(buff);
		_delay_ms(500);
	}
	LCD_Clear();
	LCD_String_xy(0, 0, "Done!");
}

void handleTrafficMonitor(void)
{
	uint16_t pulseWidth;
	int distance;
	uint8 count = -1, prev_count = -1;
	LCD_String_xy(0, 0, "Count: 0");
	while(1){
		_delay_ms(100);
		HCSR04Trigger();
		pulseWidth = GetPulseWidth();
		if(pulseWidth==US_ERROR){
			LCD_Clear();
			LCD_String("Error: Echo timeout");
			_delay_ms(300);
		}
		else if(pulseWidth ==US_NO_OBSTACLE){
			LCD_Clear();
			LCD_String("No Obstacle Detected");
			_delay_ms(300);
		}
		else{
			distance = (int)((pulseWidth * 0.034 / 2) + 0.5);
			if (distance < 6) {
				count++;  // Increment count if distance is below threshold
			}

			// Update count on LCD only if it changes
			if (count != prev_count) {
				prev_count = count;
				char buff[16];
				sprintf(buff, "Count: %d", count);
				LCD_Clear();
				LCD_String_xy(0, 0, buff);
			}
		}
	}
}

void loadStudentCodesFromEEPROM(void) {
	EEPROM_START_ADDRESS =0;
	for (uint16_t i = 0; i < 100; i++) {
		StudentCodes[i] = eeprom_read_dword((const uint32_t *)(EEPROM_START_ADDRESS + i * sizeof(long int)));
	}
}
void saveStudentNumberInEEPROM(void){
	for (uint16_t i = 0; i < 100; i++) {
		eeprom_write_dword((uint32_t *)(EEPROM_START_ADDRESS + i * sizeof(long int)), StudentCodes[i]);
	}
}
int CheckStudentNumberValidation(long int StudentNum){
	if(StudentNum <= 40100000 || StudentNum >=  40200000)
	return 0;
	else
	return 1;
}

bool areEqual(char* str1, char* str2, unsigned char minLength)
{
	for(unsigned char i = 0; i < minLength; i++)
	if(str1[i] != str2[i])
	return FALSE;
	return TRUE;
}