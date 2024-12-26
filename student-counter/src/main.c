<<<<<<< HEAD
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "eeprom.h"
#include "sensors.h"
#include "buzzer.h"

//#define F_CPU 16000000UL

void Show_Menu(void);

void Show_Menu(void) {
	LCD_Clear();
	LCD_Print("1. Attendance");
	LCD_SetCursor(2, 0);
	LCD_Print("2. Sensors");
}

void main(void) {
	LCD_Init();
	Buzzer_Init();
	
	//------------------------------- testing eeprom ---------------------------

	
	char buffer[20];
	unsigned int address;
	DDRB = 0xFF; // Set PORTB as output
	PORTB = 0x00; // Turn off all LEDs

	EEPROM_Clear();

	const char* testData = "now we are in eeprom";
	address = EEPROM_FindNextAddress();
	EEPROM_WriteString(address, testData);
	EEPROM_ReadString(address, buffer, sizeof(testData)); // Length of "Hello, EEPROM!" + null terminator

	PORTB = buffer[0];
	//------------------------------- testing eeprom ---------------------------
	
	
	
	while (1) {
		Show_Menu();
		//char key = Keypad_GetKey();
//
		//if (key == '1') {
			//LCD_Clear();
			//LCD_Print("Recording...");
			//EEPROM_Write(0x00, 'P');
			//_delay_ms(1000);
			//} else if (key == '2') {
			//LCD_Clear();
			//char buffer[16];
			//int temp = Read_Temperature();
			//snprintf(buffer, sizeof(buffer), "Temp: %d", temp);
			//LCD_Print(buffer);
			//_delay_ms(2000);
		//}
	
	
	
	//------------------------------- testing bbuzer ---------------------------
	
	 //Buzzer_Beep();
	 //_delay_ms(1000); 
//
	 //Buzzer_Success();
	 //_delay_ms(1000); 
//
	 //Buzzer_CriticalWarning();
	 //_delay_ms(2000); 
	
	//------------------------------- testing bbuzer ---------------------------
	
	
	
	}
}
=======
#include "micro_config.h"
#include "keypad.h"

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


// USART protocol
void USART_init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
void UART_SendString(unsigned char *str);

// state machine
void displayMainMenu();
void handleAttendanceInit();
void handleSubmitCode();
void handleStudentManagement();
void handleViewPresentStudents();
void handleTemperatureMonitor();
void handleRetrieveStudentData();
void handleTrafficMonitor();

// LM35 Temperature sensor
// also remember to connect both AVCC & AREF to the same VCC as the sensor
void ADC_Init();
int ADC_Read(char channel);
// signed char didn't work even though its range is from -55 to 150s
float toCelsius(int readADC);

void main(void) {

    USART_init(MYUBRR); // Initialize USART with the correct baud rate

    // test LM35 for temperature

	ADC_Init();                 /* initialize ADC*/

    DDRB = 0XFF;
    PORTB = 0;
	
	while(1)
	{
	   PORTB = toCelsius(ADC_Read(7)); // 7 means PA7
	   _delay_ms(1000);
	}


    //test keypad
    // uint8 button;
	// DDRB = 0xFF;
	// PORTB = 0x00;
	// while (1) {

	// 	button = Keypad_getPressedKey();
	// 	if ((button >= 0) && (button <= 9))
	// 		PORTB = button;
    //     _delay_ms(1000);
	// }
    
    // state machine
    
    // while (1) {       
    //     unsigned char str[] = "hello lucimad!\n";
    //     PORTC |= 0b00000001;
    //     _delay_ms(500);       
    //     //UART_SendString(str); // Send character 'A' every 500 ms
    //     UART_SendString(str);
    //     PORTC &= 0b11111110;
    //     _delay_ms(500);
    // }

    // int choice;

    // while (1) {
    //     switch (currentState) {
    //         case STATE_MAIN_MENU:
    //             displayMainMenu();
    //             scanf("%d", &choice);
    //             switch (choice) {
    //                 case 1:
    //                     currentState = STATE_ATTENDANCE_INIT;
    //                     break;
    //                 case 2:
    //                     currentState = STATE_STUDENT_MANAGEMENT;
    //                     break;
    //                 case 3:
    //                     currentState = STATE_VIEW_PRESENT;
    //                     break;
    //                 case 4:
    //                     currentState = STATE_TEMPERATURE_MONITOR;
    //                     break;
    //                 case 5:
    //                     currentState = STATE_RETRIEVE_STUDENT_DATA;
    //                     break;
    //                 case 6:
    //                     currentState = STATE_TRAFFIC_MONITOR;
    //                     break;
    //                 default:
    //                     printf("Invalid choice. Try again.\n");
    //             }
    //             break;

    //         case STATE_ATTENDANCE_INIT:
    //             handleAttendanceInit();
    //             currentState = STATE_MAIN_MENU;
    //             break;

    //         case STATE_STUDENT_MANAGEMENT:
    //             handleStudentManagement();
    //             currentState = STATE_MAIN_MENU;
    //             break;

    //         case STATE_VIEW_PRESENT:
    //             handleViewPresentStudents();
    //             currentState = STATE_MAIN_MENU;
    //             break;

    //         case STATE_TEMPERATURE_MONITOR:
    //             handleTemperatureMonitor();
    //             currentState = STATE_MAIN_MENU;
    //             break;
    //         case STATE_RETRIEVE_STUDENT_DATA:
    //             handleRetrieveStudentData();
    //             currentState = STATE_MAIN_MENU;
    //             break;
    //         case STATE_TRAFFIC_MONITOR:
    //             handleTrafficMonitor();
    //             currentState = STATE_MAIN_MENU;
    //             break;

    //         default:
    //             printf("Unknown state. Resetting to Main Menu.\n");
    //             currentState = STATE_MAIN_MENU;
    //     }
    // }
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


/** 
    USART protocoll
    UART is implemented here
**/

void USART_init(unsigned int ubrr) {
    UBRRL = (unsigned char)ubrr;
    UBRRH = (unsigned char)(ubrr >> 8);
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // Set UCSZ1 and UCSZ0 for 8-bit data
}

void USART_Transmit(unsigned char data)
{
    while(!(UCSRA &(1<<UDRE)));
    UDR = data; 
}

// ---- maybe adding SIZE parameter ---- //
void UART_SendString(unsigned char *str)  
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		USART_Transmit(str[j]);	
		j++;
	}
}


// LM35 Temperature sensor

void ADC_Init()
{										
	DDRA = 0x00;	        /* Make ADC port as input */
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}

// channel is the pin
int ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}

float toCelsius(int readADC)
{
    float celsius;
    celsius = (readADC*4.88); 
	celsius = (celsius/10.00);
    return celsius;
}
