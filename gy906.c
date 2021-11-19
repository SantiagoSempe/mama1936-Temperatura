/*
 * File:   gy906.c
 * Author: g_fer
 *asd
 * Created on 13 de junio de 2021, 18:10
 */


#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "system.h"
#include "mssp.h"
#include "gy906.h"
#include "user.h"
#include "uart.h"
#include "tick.h"
#include "dust.h"

estadoSensor_t estadoGY906;
tick_t tInicio_GY906;
uint8_t resStrGY[10];
uint8_t GYFlag;

uint16_t GY906ReadCmd(uint8_t cmd){
    uint16_t rv=0;
    i2cStart();
    i2cWriteByte(GY906_ADDRESS_WRITE);
    i2cWriteByte(cmd);
    i2cReStart();
    i2cWriteByte(GY906_ADDRESS_READ);
    rv|=i2cReadByte();
    i2cReadAck();
    rv|=(i2cReadByte()<<8);
    i2cReadAck();
    i2cReadByte();
    i2cReadNoAck();
    i2cStop();
    return rv;   
}

void GY906WriteReg(uint8_t address,uint8_t value){
    i2cStart();
    i2cWriteByte(GY906_ADDRESS_WRITE);
    i2cWriteByte(address);
    i2cWriteByte(value);
    i2cStop();
}

void iniciarMEF_GY906 (void){
    estadoGY906 = RECIBIENDO_INFO;
    tInicio_GY906 = tickRead();
}

void actualizarMEF_GY906 (void){
    static uint32_t tempAux,aux;
    static float tempFinal;
    switch(estadoGY906){
        case RECIBIENDO_INFO:
            //PIN_IRLED = 1;
            tempAux = GY906ReadCmd(GY906_TA);
            //PIN_IRLED = 0;
            estadoGY906 = CALCULANDO;
            break;
        case CALCULANDO:
            tempFinal = tempAux*0.02f-273.15f;
            estadoGY906 = IMPRIMIENDO_I2C;
            break;
        case IMPRIMIENDO_I2C:
            my_ftoa(&tempFinal,resStrGY,1);
            //printf("E%s\n",str);
            tInicio_GY906 = tickRead();
            GYFlag=1;
            estadoGY906 = IDDLE_I2C;
            break;
        case IDDLE_I2C:
            if((tickRead()-tInicio_GY906)>=500){
                estadoGY906 = RECIBIENDO_INFO;
            }
            break;
        default:
            iniciarMEF_GY906();
            break;
                    
                    
    }
}


