/**
 * C library for the ESP8266 WiFi module with a PIC microcontroller
 * Copyright (C) 2015 Camil Staps <info@camilstaps.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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
 * File:    esp8266.h
 * Author:  Camil Staps <info@camilstaps.nl>
 * Website: http://github.com/camilstaps/ESP8266_PIC
 * Version: 0.1
 *
 * See:     esp8266.c
 *
 * This is the header file for the ESP8266 PIC18 library. It contains:
 *
 *  * Constants and bitmasks
 *  * Prototypes for functions that should be written by the user for his
 *    implementation
 *  * Prototypes for functions that can be used by the user
 *  * Prototypes for functions that are intended for internal use only
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef ESP8266_H
#define	ESP8266_H

#ifdef	__cplusplus
extern "C" {
#endif

/** Some constants **/

#define ESP8266_STATION 0x01
#define ESP8266_SOFTAP 0x02

#define ESP8266_TCP 1
#define ESP8266_UDP 0

#define ESP8266_OK 1
#define ESP8266_READY 2
#define ESP8266_FAIL 3
#define ESP8266_NOCHANGE 4
#define ESP8266_LINKED 5
#define ESP8266_UNLINK 6
    
#define MAX_COMMAND_SIZE 50
#define CHARACTER_TIME  1
    
#define STD_TIMEOUT 500
#define SHORT_TIMEOUT 200
#define LONG_TIMEOUT 1500
#define VERY_LONG_TIMEOUT 10000
#define RESPONSE_TIMEOUT 3000

  
/** Should be witten by the user for input from / output to the ESP module **/

void _esp8266_putch(unsigned char);


/** Function prototypes **/

// Print a string to the output
void _esp8266_print(unsigned const char *);



void sendATCmd(char* cmd);

bit esp8266_init(void);

bit checkResponse(char* resp, char* espec);

#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */
