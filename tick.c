/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de Tick
 * 
 * Aquí se encuentra la implementación de uart, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas.
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/
#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "tick.h"       /* Funciones/Parametros Tick */

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
volatile tick_t tickCounter;    //Variable global que almacena el tick count

/*==================[declaraciones de funciones internas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Inicializa la el contador de tick 
 * @return	Nada
 * @note    Las opciones se modifican en el código, por ejemplo con la 
 * constante UART_BAUDRATE
 * @sa      UART_BAUDRATE    
 */
void tickInit(void) {
    // Set TMR0 to the options selected in the User Interface
	
    // PSA assigned; PS 1:4; TMRSE Increment_hi_lo; mask the nWPUEN and INTEDG bits
    OPTION_REG = (uint8_t)((OPTION_REG & 0xC0) | (0xD1 & 0x3F)); 
	
    // TMR0 6; 
    TMR0 = 0x06;
	
    // Load the TMR value to reload variable
    timer0ReloadVal= 6;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt
    INTCONbits.TMR0IE = 1;

    // Set Default Interrupt Handler
}

/**
 * @brief	Lee Tick Counter
 * @return	El vlor del contador de tick
 */
tick_t tickRead( void ) {
    tick_t aux;
    GIE = 0;                        //Inicia Zona critica
    aux = tickCounter;              //  Operaciones atomicas
    GIE = 1;                        //Finaliza la zona critica
    return aux;
}

/**
 * @brief       Escribe Tick Counter
 * @param[in]   ticks Valor a escribir en el contador de tick
 * @return      Nada
 */
void tickWrite( tick_t ticks ){
    GIE = 0;                        //Inicia Zona critica
    tickCounter = ticks;            //  Operaciones atomicas
    GIE = 1;     
}

/*==================[fin del archivo]========================================*/
