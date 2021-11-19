
#ifndef AHT10_H
#define	AHT10_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "mssp.h"
#include "gy906.h"

//Direcciones
#define AHT10_ADDRESS_WRITE 0x70
#define AHT10_ADDRESS_READ 0x71

extern uint8_t AHTFlag;
extern uint8_t resStrAHT[10];


void AHT10CallCmd(void);
uint16_t AHT10ReadCmd (void);
void iniciarMEF_AHT10 (void);
void actualizarMEF_AHT10 (void);

#endif

