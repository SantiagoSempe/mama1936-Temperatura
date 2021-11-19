/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de la Disply
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de ADC
 */
#ifndef ADC_H
#define ADC_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/
typedef enum{
    AIN0 = 0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN8, AIN9, AIN10, AIN11, AIN12, AIN13, AIN_CVREF, AIN_FIXREF, VDD_CALC = 255
} adcMap_t;

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/
void adcInit( void );                      /* Inicializa el ADC */
uint16_t adcRead(adcMap_t analogInput);    /* Realiza una conversión AD */
uint16_t adcRead_mV(adcMap_t analogInput); /* Realiza una conversión AD en mV */
/*==================[fin del archivo]========================================*/
#endif// ADC_H
