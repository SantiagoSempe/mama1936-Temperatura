/**
 * C library for the ESP8266 WiFi module with a PIC microcontroller
 * Copyright (C) 2015 Camil Staps <info@camilstaps.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.asd
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *****************************************************************************
 *
 * File:    esp8266.c
 * Author:  Camil Staps <info@camilstaps.nl>
 * Website: http://github.com/camilstaps/ESP8266_PIC
 * Version: 0.1
 *
 * See:     esp8266.h
 *
 * C library for interfacing the ESP8266 Wi-Fi transceiver module with a PIC18
 * microcontroller. Should be used with the XC8 compiler.
 */

#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* Para las definiciones de uint8_t por ej.*/
#include "system.h"     /* Funciones/Parametros System, como osc/peripheral config */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "uart.h"
#include "esp8266.h"    // Funciones del esp8266
#include <stdio.h>      /* Archivo de Encabezados StdIO */
#include <string.h>




bit esp8266_init(void){
    unsigned char resp[20];
    sendATCmd("ATE0");
    my_delay(STD_TIMEOUT);
    if(!checkResponse(resp,"OK")) return false;
    sendATCmd("AT+CIPMUX=1");
    my_delay(STD_TIMEOUT);
    if(!checkResponse(resp,"OK")) return false;
    sendATCmd("AT+CWMODE=3");
    my_delay(STD_TIMEOUT);
    if(!checkResponse(resp,"OK")) return false;
    //sendATCmd("AT+CIPRECVMODE=1");
    //my_delay(STD_TIMEOUT);
  //  if(!checkResponse(resp,"OK")) return false;
    return true;
    }

void _esp8266_print(unsigned const char *ptr) {
    while (*ptr != 0) {
        _esp8266_putch(*ptr++);
    }
}


void _esp8266_putch(unsigned char value){
    while (!TXIF)   //Espera que haya espacio en la FIFO (bloquea poco tiempo)
    continue;
    TXREG = value;  //Envía el byte
    
}
/**
 * Sends AT command.
 *
 * 
 *
 * @param AT command to be send, without \r\n
 * 
 * 
 */
void sendATCmd(char* cmd){


    char xCommand[MAX_COMMAND_SIZE],xByte;

    memset(xCommand,0,sizeof(xCommand));

    strcpy(xCommand,cmd);
    strcat(xCommand,"\r\n");
    
    _esp8266_print(xCommand);   // envio comando
    uartBufferReset();
}
/**
 * Checks ESP8266 response to a AT command.
 * Should be called after sendATCmd and a considerable delay
 * (each command has a different latency)
 * This function is separated from sendATCmd to provide
 * the chance of do other stuff meanwhile the ESP8266 proccess
 * the command and respond.
 * Example:
 *      uint8_t resp[20];
 *      sendATCmd("AT+CIPSTART=0,\"TCP\",\"192.168.0.1\",8000);
 *      \\... do some stuff or simply a considerable delay
 *      if(!checkResponse(resp,"CONNECT"){
 *          \\error and not conected
 *      }
 *      else{
 *          \\success and conected
 *      }
 * 
 * @param resp: buffer to store the response
 *        espec: specific response to wait for, null if a specific 
 *        response is not wanted
 * 
 * @return true if success
 *         false if fails
 * 
 */
bit checkResponse(char* resp, char* espec) {
    bool xResponse;
    uint8_t index,xByte;
    if (espec == NULL) xResponse = false;
    else xResponse = true; // verifico si necesito o no una respuesta especifica
    index = 0;
    while (uartGetByte(&xByte)) {
        resp[index] = xByte;
        index++;
        my_delay(CHARACTER_TIME);
    }
    resp[index]=0; //pongo el null de final de string
    uartBufferReset();
    if (xResponse == true) // si espero respuesta verifico la misma
    {
        if (strstr(resp, espec)) return true; // comparo la respuesta con lo que deseado, si es correcto salgo del loop
        else return false;
    }
}
