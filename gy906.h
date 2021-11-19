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
#ifndef GY906_H
#define	GY906_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

#define GY906_ADDRESS_WRITE 0xB4
#define GY906_ADDRESS_READ 0xB5

// RAM
#define GY906_RAWIR1 0x04
#define GY906_RAWIR2 0x05
#define GY906_TA 0x06
#define GY906_TOBJ1 0x07
#define GY906_TOBJ2 0x08
// EEPROM
#define GY906_TOMAX 0x20
#define GY906_TOMIN 0x21
#define GY906_PWMCTRL 0x22
#define GY906_TARANGE 0x23
#define GY906_EMISS 0x24
#define GY906_CONFIG 0x25
#define GY906_ADDR 0x2E
#define GY906_ID1 0x3C
#define GY906_ID2 0x3D
#define GY906_ID3 0x3E
#define GY906_ID4 0x3F

extern uint8_t resStrGY[10];
extern uint8_t GYFlag;

uint16_t GY906ReadCmd(uint8_t cmd);
void GY906WriteReg(uint8_t address,uint8_t value);
void iniciarMEF_GY906 (void);
void actualizarMEF_GY906 (void);


#endif	/* XC_HEADER_TEMPLATE_H */

