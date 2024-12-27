#include "micro_config.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "usart.h"

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
	

	int choice;

    while (1) {
        switch (currentState) {
            case STATE_MAIN_MENU:
                displayMainMenu();
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        currentState = STATE_ATTENDANCE_INIT;
                        break;
                    case 2:
                        currentState = STATE_STUDENT_MANAGEMENT;
                        break;
                    case 3:
                        currentState = STATE_VIEW_PRESENT;
                        break;
                    case 4:
                        currentState = STATE_TEMPERATURE_MONITOR;
                        break;
                    case 5:
                        currentState = STATE_RETRIEVE_STUDENT_DATA;
                        break;
                    case 6:
                        currentState = STATE_TRAFFIC_MONITOR;
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                }
                break;

            case STATE_ATTENDANCE_INIT:
                handleAttendanceInit();
                currentState = STATE_MAIN_MENU;
                break;

            case STATE_STUDENT_MANAGEMENT:
                handleStudentManagement();
                currentState = STATE_MAIN_MENU;
                break;

            case STATE_VIEW_PRESENT:
                handleViewPresentStudents();
                currentState = STATE_MAIN_MENU;
                break;

            case STATE_TEMPERATURE_MONITOR:
                handleTemperatureMonitor();
                currentState = STATE_MAIN_MENU;
                break;
            case STATE_RETRIEVE_STUDENT_DATA:
                handleRetrieveStudentData();
                currentState = STATE_MAIN_MENU;
                break;
            case STATE_TRAFFIC_MONITOR:
                handleTrafficMonitor();
                currentState = STATE_MAIN_MENU;
                break;

            default:
                printf("Unknown state. Resetting to Main Menu.\n");
                currentState = STATE_MAIN_MENU;
        }
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
	printf("Attendance Initialized. Waiting for student codes...\n");
	// logic
	// submut code or exit
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
	printf("Monitoring Temperature...\n");
	// logic
	// ADC and then displaying on LCD
}

void handleRetrieveStudentData(void)
{
	printf("Retrievinng Student Data...\n");
	// logic
	// save data to EEPROM using USART
	// check success and failure and show on LCD
}

void handleTrafficMonitor(void)
{
	printf("Monitoring Traffic...\n");
	// logic
	// Display data received from sonar
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

