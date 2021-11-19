/*
 * File:   dust.casd
 * Author: Alumno
 *
 * Created on 4 de octubre de 2021, 16:29
 * 
 */
#include <xc.h>
#include "user.h"
#include "uart.h"
#include "tick.h"
#include "mssp.h"
#include <stdio.h>
#include "AHT10.h"
#include "gy906.h"
#include "system.h"
#include "adc.h"
#include "dust.h"



estadoSensor_t estadoActual;
uint8_t casillero;
uint16_t bufferMed[CANT_PROMEDIOS]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t resStrDUST[10];
uint8_t DUSTFlag;

void iniciarMEF_Polvo(void){
    estadoActual=PREPARANDO_MEDICION;
    casillero = 255;
}

void actualizarMEF_Polvo(void){
    uint8_t i;
    static float dust;
    static uint16_t aux;
    static uint16_t acum;
    static tick_t tinicio;
    static uint16_t nAdcRef;
    switch(estadoActual){
        case PREPARANDO_MEDICION:
            PIN_IRLED=1;
            casillero++;
            nAdcRef = adcRead_mV(VDD_CALC);
            if(casillero>CANT_PROMEDIOS-1){
                for(i=1;i<CANT_PROMEDIOS;i++){
                    bufferMed[i-1]=bufferMed[i];
                }
                casillero=CANT_PROMEDIOS - 1;
            }
            estadoActual=MIDIENDO;
            tinicio=tickRead();
            break;
        case MIDIENDO:
            PIN_IRLED = 0;
            __delay_us(280);
            aux = adcRead(AIN1);
            __delay_us(40);
            PIN_IRLED = 1;
            bufferMed[casillero] = (600UL*aux) / nAdcRef;
            estadoActual=ESPERANDO_CICLO;
            break;
        case ESPERANDO_CICLO:
            if((tickRead()-tinicio)>10){
                estadoActual=PROMEDIANDO;
            }
            break;
        case PROMEDIANDO:
            acum=0;
            for(i=0;i<CANT_PROMEDIOS;i++){
                acum+=bufferMed[i];
            }
            acum/=CANT_PROMEDIOS;
            estadoActual=IMPRIMIENDO;
            break;
        case IMPRIMIENDO:
            
            dust=((float)acum)/1000*0.17f-0.1f;
            my_ftoa(&dust,resStrDUST,3);
            //printf("E%s\n",str);
            DUSTFlag = 1;
            estadoActual=IDDLE;
            break;
        case IDDLE:
            if((tickRead()-tinicio)>=100){
              estadoActual=PREPARANDO_MEDICION;  
            }
            break;
        default:
            iniciarMEF_Polvo();            
    }
}
