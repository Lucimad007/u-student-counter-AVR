#include <stdio.h>  //just for testing
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz clock frequency
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

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





void main(void) {

    USART_init(MYUBRR); // Initialize USART with the correct baud rate
    
    while (1) {       
        unsigned char str[] = "hello lucimad!\n";
        PORTC |= 0b00000001;
        _delay_ms(500);       
        //UART_SendString(str); // Send character 'A' every 500 ms
        UART_SendString(str);
        PORTC &= 0b11111110;
        _delay_ms(500);
    }

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
