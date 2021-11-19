/*
 * File:   AHT10.c
 * Author: Alumnoasd
 *
 * Created on 30 de septiembre de 2021, 09:12
 */
#include <stdint.h>
#include <xc.h>
#include <stdio.h>
#include "mssp.h"
#include "AHT10.h"
#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "user.h"
#include "uart.h"
#include "tick.h"
#include "dust.h"

estadoSensorI2C_t estadoAHT10;
tick_t tInicio_AHT10;
uint8_t resStrAHT[10];
uint8_t AHTFlag;


void AHT10CallCmd(void) {
    i2cStart();
    i2cWriteByte(AHT10_ADDRESS_WRITE);
    i2cWriteByte(0xAC);
    i2cWriteByte(0x33);
    i2cWriteByte(0x00);
    i2cStop();
//    __delay_ms(100);   
}

uint32_t AHTReadCmd(void){
    uint8_t hum[6];
    uint32_t humedad, aux;
    i2cStart();
    i2cWriteByte(AHT10_ADDRESS_READ);
    hum[0] = i2cReadByte(); //aca devueleve el estado
    i2cReadAck();
    hum[1] = i2cReadByte();
    i2cReadAck();
    hum[2] = i2cReadByte();
    i2cReadAck();
    hum[3] = i2cReadByte();
    i2cReadAck();
    hum[4] = i2cReadByte();
    i2cReadAck();
    hum[5] = i2cReadByte();
    i2cReadNoAck();
    i2cStop();
    //Termina de leer y empieza a calcular
    humedad = 0;
    humedad = hum[1];
    humedad <<= 12;
    aux = hum[2];
    aux <<= 4;
    humedad |= aux;
    humedad += (hum[3]&0xF0) >> 4;
    return humedad;
}

void iniciarMEF_AHT10 (void){
    estadoAHT10 = PIDIENDO_INFO;
    tInicio_AHT10 = tickRead();
}

void actualizarMEF_AHT10 (void){
    static uint32_t humedad = 0;
    static float resultado;
    PIN_IRLED = 1;
    switch (estadoAHT10) {
        case PIDIENDO_INFO:
            AHT10CallCmd();
            tInicio_AHT10 = tickRead();
            estadoAHT10 = ESPERANDO;
            //            }
            break;
        case ESPERANDO:
            if ((tickRead() - tInicio_AHT10) >= 100) {
                estadoAHT10 = RECIBIENDO_INFO;
            }
            break;
        case RECIBIENDO_INFO:
            humedad = AHTReadCmd();
            
            estadoAHT10 = CALCULANDO;
            break;
        case CALCULANDO:
           resultado = 100*((float)humedad/(float)(0x100000));
            estadoAHT10 = IMPRIMIENDO_I2C;
            break;
        case IMPRIMIENDO_I2C:            
            my_ftoa(&resultado,resStrAHT,1);
            //printf("E%s\n",str);  //para la prueba
            AHTFlag = 1;
            tInicio_AHT10 = tickRead();
            estadoAHT10 = IDDLE_I2C;
            break;
        case IDDLE_I2C:
            if((tickRead()-tInicio_AHT10)>=500){
                estadoAHT10 = RECIBIENDO_INFO;
            }
            break;
        default:
            iniciarMEF_AHT10();
            break;                  
    }
    PIN_IRLED = 0;
}



