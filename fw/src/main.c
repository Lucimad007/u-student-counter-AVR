#include "micro_config.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "USART.h"
#include "ultrasonic.h"

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

// state machine
void displayMainMenu(void);
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

int main(void) {
	
	while (1)
	{
	}
	return 0;
}

void displayMainMenu(void)
{
	printf("1. Start Attendance\n");
	printf("2. Manage Students\n");
	printf("3. Monitor Temperature\n");
	printf("4. Traffic Monitoring\n");
	printf("Enter your choice: ");
	// show on LCD
}

void handleAttendanceInit(void)
{
	char key;
	while(1){
		LCD_Clear();
		LCD_String_xy(0,0,NULL);
		LCD_String("1.Submit Student Code");
		LCD_String_xy(1,0,NULL);
		LCD_String("2.Exit");
		key=scan_keypad();
		if (key=='1')
		{
			handleStudentManagement();
		}
		else{
			handleStudentManagement();
			return;
		}
	}
}

void handleSubmitCode(void)
{
	char key;
	long int tmpStudentCode=0,StudentCode=0;
	LCD_Clear();
	LCD_String_xy(0,0,NULL);
	LCD_String("Enter Student Code:");
	LCD_String_xy(1,0,NULL);
	while (1)
	{
		key=scan_keypad();
		if(key!='o'){
			tmpStudentCode=tmpStudentCode*10 + (key-'0');
			LCD_Char(key);
		}
		else{
			break;
		}
	}
	_delay_ms(200);
	if(CheckStudentNumberValidation(tmpStudentCode)){
		StudentCode=tmpStudentCode;
		StudentCodes[StudentCount]=StudentCode;
		StudentCount++;
		LCD_Clear();
		LCD_String_xy(0,0,NULL);
		LCD_String("Student Code Accepted!");
		return;
	}
	else{
		LCD_Clear();
		LCD_String_xy(0,0,NULL);
		LCD_String("Student Code Not Accepted!");
		Buzzer_Beep();
		_delay_ms(200);
		return;
	}
}

void handleStudentManagement(void)
{
	char key;
	long int StudentNumber=0;
	LCD_Clear();
	LCD_String("Enter Student Code:");
	LCD_String_xy(1,0,NULL);
	LCD_String("Student Number: ");
	while(1){
		key=scan_keypad();
		if(key!='o'){
			StudentNumber=StudentNumber*10 + (key-'0');
			LCD_Char(key);
		}
		else{
			break;
		}
	}
	for(int i=0;i<StudentCount;i++){
		if(StudentNumber==StudentCodes[i]){
			LCD_Clear();
			LCD_String("Student Found!");
			_delay_ms(100);
			return;
		}
	}
	LCD_Clear();
	LCD_String("Student Not Found!");
	_delay_ms(100);
	return;
}

void handleViewPresentStudents(void)
{
	int Scroller=0;
	char key;
	LCD_Clear();
	LCD_String_xy(0,0,NULL);
	LCD_String("Present Students:");
	LCD_Number(StudentCount);
	_delay_ms(100);
	LCD_Clear();
	LCD_String_xy(0,0,NULL);
	LCD_Number(StudentCodes[Scroller*2]);
	LCD_String_xy(1,0,NULL);
	LCD_Number(StudentCodes[Scroller*2+1]);
	while(1){
		key=scan_keypad();
		if(key=='0'){
			Scroller=(Scroller+1);
		}
		else if(key=='8'){
			Scroller=(Scroller-1);
		}
		else if(key=='o'){
			break;
		}
		LCD_Clear();
		if(Scroller*2<=StudentCount){
			LCD_String_xy(0,0,NULL);
			LCD_Number(StudentCodes[Scroller*2]);
			LCD_String_xy(1,0,NULL);
			LCD_Number(StudentCodes[Scroller*2+1]);
		}
		else{
			if(StudentCount%2==0){
				continue;
			}
			else{
				LCD_String_xy(0,0,NULL);
				LCD_Number(StudentCodes[StudentCount-1]);
			}
		}

	}
}

void handleTemperatureMonitor(void)
{
	char Temperature[10];
	float celsius;
	keypad_init();
	_delay_ms(100);
	Buzzer_Init();
	_delay_ms(100);
	LCD_Init();
	_delay_ms(100);
	ADC_Init();
	_delay_ms(100);
	while(1)
	{
		Buzzer_Beep();
		_delay_ms(1000);
		LCD_String_xy(1,0,"Temperature");
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);
		sprintf(Temperature,"%d%cC  ", (int)celsius, degree_sysmbol);/* convert integer value to ASCII string */
		LCD_String_xy(2,0,Temperature);/* send string data for printing */
		_delay_ms(1000);
		memset(Temperature,0,10);
	}
}

void handleRetrieveStudentData(void)
{
	loadStudentCodesFromEEPROM();
	for(int i=0;i<5;i++){
		LCD_Clear();
		LCD_String_xy(0,0,NULL);
		LCD_Number(StudentCodes[i]);
		_delay_ms(500);
	}
	USART_SendArray(StudentCodes,2);
}


void handleTrafficMonitor(void)
{
	uint16_t pulseWidth;
	int distance;
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
			LCD_Clear();
			LCD_Number(distance);
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
	if(StudentNum <= 40100000 || StudentNum >=  40200000){
		return 0;
	}
	else{
		return 1;
	}
}