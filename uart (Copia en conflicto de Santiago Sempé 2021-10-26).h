/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de user
 */
#ifndef UART_H
#define UART_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
/* User Level #define Macros                                                 */
/* TODO: Los parámetros de user.c pueden ponerse aquí */
    

//Pines de la UART
#define	TRIS_PICTX      TRISCbits.TRISC6
#define	PIN_PICTX       PORTCbits.RC6
#define	TRIS_PICRX      TRISCbits.TRISC7
#define	PIN_PICRX       PORTCbits.RC7
//Definición del Baudrate
#define	UART_BAUDRATE        9600

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo
extern uint8_t bufferRx[40];// en simulacion se usa maximo 40 bytes
extern uint8_t* RxPtr;

/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aquí */
void uartInit(void);    /* Inicializa la UART */
//void putch(char data);  /* Pone un byte en stdout */
//char getch(void);       /* Toma un byte en stdin  */
//char getche(void);      /* Toma un byte en stdin con eco */
void uartWriteByte( uint8_t value );      /* Envia un byte en forma boqueante */
__bit uartReadByte( uint8_t* receivedByte );/* Toma un byte de la UART */
__bit uartGetByte(uint8_t* receivedByte);//Toma un Byte del BUFFER de la UART
void uartBufferReset(void); //Rsetea el buffer de la UART para que no desborde

/*==================[fin del archivo]========================================*/
#endif// UART_H
