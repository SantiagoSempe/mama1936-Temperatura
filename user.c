/*
 * File:   user.c
 * Author: g_ferasd
 *
 * Created on 23 de septiembre de 2021, 20:37
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
#include <stdlib.h>
/* Funciones/Parametros System, como conf de osc/perif */


//definicion de datos internos

uint8_t contador;


void appInit(void){
       /**
    LATx registers
    */

    TRIS_IRLED =0;
    /**
    TRISx registers


    /**
    ANSELx registers
    */
    ANSELB = 0x3F;
    ANSELA = 0x3F;

    /**
    WPUx registers
    */
    WPUE = 0x00;
    WPUB = 0x00;
    OPTION_REGbits.nWPUEN = 1;


    /**
    APFCONx registers
    */
    APFCON = 0x00;
    
    // SCS FOSC; SPLLEN disabled; IRCF 500KHz_MF; 
    OSCCON = 0x38;
    // TUN 0; 
    OSCTUNE = 0x00;
    // SBOREN disabled; 
    BORCON = 0x00;
    
    // WDTPS 1:65536; SWDTEN OFF; 
    WDTCON = 0x16;
    uartInit();
    tickInit();
    i2cInit();
    adcInit();
    RCIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;

}

void my_delay(uint16_t timeout){
    for (;timeout>0;timeout--){
        __delay_ms(1);
    }
}

void my_ftoa(float* fvalue, char* farray, uint8_t decs){
    int ent;
    char i;
    uint8_t auxc;
	float aux;

	ent = (int) (*fvalue);
	itoa(farray,ent,10);
	aux = *fvalue - (float)ent;
	if(aux<0.0f){
		aux = -aux;
	}
	i=0;
	while(farray[i]!='\0'){
		i++;
	}
	farray[i]='.';
	i++;
	for(;decs>0;decs--){
	auxc=
	aux=aux*10;
	auxc= (uint8_t)aux;
	aux =aux-(float)auxc;
	farray[i]=auxc+'0';
	i++;
	}
	farray[i]='\0';
}

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[iâ€¦j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C


//************************** MAQUINAS DE ESTADO ********************************


//AHT10 MEF

//GY906 MEF

//Polvo MEF