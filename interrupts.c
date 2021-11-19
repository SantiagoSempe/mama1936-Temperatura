/*============================================================================
 * Licencia:
 * Autor:asd
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene la rutina de interrupción
 * 
 * Aquí se encuentra la implementación de la rutina de interrupción
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>             /* Archivo de Encabezados General XC8 */
#include "tick.h"           /* Funciones/Parametros Tick */
#include "uart.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/
void isr(void);

/*==================[definiciones de funciones internas]=====================*/
/**
 * @brief	Rutina de interrupción
 * @return	Nada
 * @note    Completar con código de interrupción necesario
 */
void __interrupt() isr(void) {
    uint8_t byte;
    /* El sig. ejemplo de código muestra el manejo de interrupciones.
    Note que no son bloques if separados sino que son if else ecadenados.
    No use bloques if separados para cada flag de interrupción para evitar
    errores en tiempo de ejecución. */
    /* TODO: Completar con el código de las rutinas de interrupción aquí. */
    /* Determina que flag ha generado la interrupción */
    if(RCIF){
        if((byte=RCREG)!=0){
        if(RxPtr<(bufferRx+sizeof(bufferRx))){
           
            *RxPtr=byte;
            RxPtr++;
            }
        }
        else{
            RxPtr=bufferRx;
            RxPtr++;
            *RxPtr=RCREG;   
        }
    } else if (TMR0IF) {
        TMR0IF = 0; /* Baja Interrupt Flag */
        TMR0 += 7; /* Ajusta desborde a 1 mSeg aprox */
        tickCounter++; /* Incrementa el contador */
    }
            
        
        
        
    
    
    
    //if(TMR1IF) {
    //  TMR1IF=0; /* Baja Interrupt Flag 1 */
    //  ...
    //}
    //else if(TMR2IF) {
    //  TMR2IF=0; /* Baja Interrupt Flag 2 */
    //  ...
    //}
    //else {
    //  /* Interrupción de tipo inesperado */
    //}
}


/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/