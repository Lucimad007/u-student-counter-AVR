#include "micro_config.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "usart.h"
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
				displayFirstMainMenu();
                break;

            case STATE_TEMPERATURE_MONITOR:
                currentState = STATE_MAIN_MENU;
				displayFirstMainMenu();
                break;
            case STATE_RETRIEVE_STUDENT_DATA:
                currentState = STATE_MAIN_MENU;
				displayFirstMainMenu();
                break;
            case STATE_TRAFFIC_MONITOR:
                currentState = STATE_MAIN_MENU;
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
		LCD_String_xy(0,0,"Code Accepted!");
		_delay_ms(1000);
	}
	else{
		LCD_Clear();
		LCD_String_xy(0,0, "Not Accepted!");
		Buzzer_Beep();
		_delay_ms(1000);
	}
}

void handleStudentManagement(void)
{
	char key;
	long int StudentNumber=0;
	LCD_String_xy(1, 0, NULL);
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
			_delay_ms(1000);
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
	LCD_String_xy(0,0,NULL);
	LCD_String("Present Students");
	LCD_Number(StudentCount);
	_delay_ms(100);
	LCD_Clear();
	LCD_String_xy(0,0,NULL);
	LCD_Number(StudentCodes[Scroller*2]);
	LCD_String_xy(1,0,NULL);
	LCD_Number(StudentCodes[Scroller*2+1]);
	while(1){
		if(StudentCount == 0)
		{
			LCD_String_xy(1,0, "No Students.");
			break;
		}
		key=scan_keypad();
		if(key=='0'){
			Scroller=(Scroller+1) >= StudentCount ? 0 : (Scroller+1);
		}
		else if(key=='8'){
			Scroller=(Scroller-1) < 0 ? 0 : (Scroller-1);
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
	printf("Retrievinng Student Data...\n");
	// logic
	// save data to EEPROM using USART
	// check success and failure and show on LCD
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

