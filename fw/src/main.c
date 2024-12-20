#include "micro_config.h"
#include "keypad.h"
#include "lcd.h"
#include "sensors.h"
#include "buzzer.h"
#include "USART.h"

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


//
//void main(void) {
//
    //USART_init(MYUBRR); // Initialize USART with the correct baud rate
//
    //// test LM35 for temperature
//
	//ADC_Init();                 /* initialize ADC*/
//
    //DDRB = 0XFF;
    //PORTB = 0;
	//
	//while(1)
	//{
	   //PORTB = toCelsius(ADC_Read(7)); // 7 means PA7
	   //_delay_ms(1000);
	//}
//
    //
    //// state machine
    //
    //// while (1) {       
    ////     unsigned char str[] = "hello lucimad!\n";
    ////     PORTC |= 0b00000001;
    ////     _delay_ms(500);       
    ////     //UART_SendString(str); // Send character 'A' every 500 ms
    ////     UART_SendString(str);
    ////     PORTC &= 0b11111110;
    ////     _delay_ms(500);
    //// }
//
    //// int choice;
//
    //// while (1) {
    ////     switch (currentState) {
    ////         case STATE_MAIN_MENU:
    ////             displayMainMenu();
    ////             scanf("%d", &choice);
    ////             switch (choice) {
    ////                 case 1:
    ////                     currentState = STATE_ATTENDANCE_INIT;
    ////                     break;
    ////                 case 2:
    ////                     currentState = STATE_STUDENT_MANAGEMENT;
    ////                     break;
    ////                 case 3:
    ////                     currentState = STATE_VIEW_PRESENT;
    ////                     break;
    ////                 case 4:
    ////                     currentState = STATE_TEMPERATURE_MONITOR;
    ////                     break;
    ////                 case 5:
    ////                     currentState = STATE_RETRIEVE_STUDENT_DATA;
    ////                     break;
    ////                 case 6:
    ////                     currentState = STATE_TRAFFIC_MONITOR;
    ////                     break;
    ////                 default:
    ////                     printf("Invalid choice. Try again.\n");
    ////             }
    ////             break;
//
    ////         case STATE_ATTENDANCE_INIT:
    ////             handleAttendanceInit();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
//
    ////         case STATE_STUDENT_MANAGEMENT:
    ////             handleStudentManagement();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
//
    ////         case STATE_VIEW_PRESENT:
    ////             handleViewPresentStudents();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
//
    ////         case STATE_TEMPERATURE_MONITOR:
    ////             handleTemperatureMonitor();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
    ////         case STATE_RETRIEVE_STUDENT_DATA:
    ////             handleRetrieveStudentData();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
    ////         case STATE_TRAFFIC_MONITOR:
    ////             handleTrafficMonitor();
    ////             currentState = STATE_MAIN_MENU;
    ////             break;
//
    ////         default:
    ////             printf("Unknown state. Resetting to Main Menu.\n");
    ////             currentState = STATE_MAIN_MENU;
    ////     }
    //// }
//}
//
//

int main(void){
	char Temperature[10];
	float celsius;

	LCD_Init();                 
	ADC_Init();                 
	
	while(1)
	{
		LCD_String_xy(1,0,"Temperature");
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);
		sprintf(Temperature,"%d%cC  ", (int)celsius, degree_sysmbol);/* convert integer value to ASCII string */
		LCD_String_xy(2,0,Temperature);/* send string data for printing */
		_delay_ms(1000);
		memset(Temperature,0,10);
	}
}


void displayMainMenu() 
{
    printf("1. Start Attendance\n");
    printf("2. Manage Students\n");
    printf("3. Monitor Temperature\n");
    printf("4. Traffic Monitoring\n");
    printf("Enter your choice: ");
    // show on LCD
}

void handleAttendanceInit() 
{
    printf("Attendance Initialized. Waiting for student codes...\n");
    // logic
    // submut code or exit
}

void handleSubmitCode() 
{
    printf("Submitting Student Code...\n");
    // logic
    // get error on LCD & buzzer sound if wrong length or format
}

void handleStudentManagement() 
{
    printf("Managing Students...\n");
    // logic
    // search for presentation
}

void handleViewPresentStudents()
{
    printf("Viewing Present Students...\n");
    // logic
    // display number of present students
    // then
    // display names and shift the display
}

void handleTemperatureMonitor() 
{
    printf("Monitoring Temperature...\n");
    // logic
    // ADC and then displaying on LCD
}

void handleRetrieveStudentData()
{
    printf("Retrievinng Student Data...\n");
    // logic
    // save data to EEPROM using USART
    // check success and failure and show on LCD
}

void handleTrafficMonitor() 
{
    printf("Monitoring Traffic...\n");
    // logic
    // Display data received from sonar
}