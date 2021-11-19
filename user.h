/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USER_H
#define USER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
//definicion de tipo de datos
typedef enum {
    PREPARANDO_MEDICION,
    MIDIENDO,
    ESPERANDO_CICLO,
    IMPRIMIENDO,
    PROMEDIANDO,
    IDDLE 
}estadoSensor_t;

typedef enum { 
    RECIBIENDO_INFO,
    PIDIENDO_INFO,
    CALCULANDO,
    IMPRIMIENDO_I2C,
    IDDLE_I2C,
    ESPERANDO       
}estadoSensorI2C_t;

//Definiciòn de entradas y salidas.


void appInit(void);
void my_ftoa(float* fvalue, char* farray, uint8_t decs);
//char* itoa(int value, char* result, int basen);
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
void my_delay(uint16_t timeout);

// Maquinas de estado



#endif	/* USER_H */

