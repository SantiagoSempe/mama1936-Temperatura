/*============================================================================
 * Licencia:
 * Autor:asds
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de ADC
 * 
 * Aquí se encuentra la implementación de ADC, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas.
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/
#include "system.h"
#include "adc.h"        /* Funciones/Parametros ADC */

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Inicializa el ADC
 * @return	Nada
 */
void adcInit(void) {
    FVREN = 1;
    ADFVR1 = 0;
    ADFVR0 = 1;
    ADFM = 1;
    ADPREF0 = 1;
    ADPREF1 = 1;
    ADNREF = 0;
    ADCS2 = 1;
    ADCS1 = 1;
    ADCS0 = 1;
    ADON = 1;
}

/**
 * @brief	Realiza una conversión AD
 * @param[in]   analogInput Selecciona la entrada analógica deseada
 * @return  resultado de la conversión
 */
uint16_t adcRead(adcMap_t analogInput){
    uint16_t result = 0;
    ADCON0bits.CHS = analogInput;
    __delay_us(50);
    GO = 1;
    while(GO){}
    result = ADRESH;
    result <<= 8;
    result |= ADRESL;
    return result;
}
/**
 * @brief	Realiza una conversión AD en mV
 * @param[in]   analogInput Selecciona la entrada analógica deseada
 * @note    Si recibe como parámetro 255 ( o la etiqueta `VDD_CALC` ) determina la tensión de alimentación VDD o tensión de referencia actual 
 * @return  resultado de la conversión en mV
 * @note    Antes de poder medir cualquier canal se debe medir por lo menos una vez la tensión de alimentación o referencia
 */
uint16_t adcRead_mV(adcMap_t analogInput){
    static uint16_t nAdcRef = 0;
    
    if (analogInput == VDD_CALC){
        nAdcRef = adcRead(analogInput);
        //return (1023UL*600U)/nAdcRef;
        return nAdcRef;
    }
    else if(analogInput >= AIN0 || analogInput <= AIN_FIXREF){
        return (600UL*adcRead(analogInput)) / nAdcRef;
    }else{return 0;}
        
    //TODO ...
}
/*==================[fin del archivo]========================================*/
