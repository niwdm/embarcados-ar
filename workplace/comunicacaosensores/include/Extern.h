/*
 * Extern.h
 *
 *  Created on: 15/10/2015
 *      Author: Airton Ribeiro
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#ifdef __cplusplus
extern "C" {
#endif

int iniciar(char* porta);
int ler();
int getAcelX();
int getAcelY();
int getAcelZ();
int getTerremoto();
int getTemp();
int getAltitude();
int finalizar();

#ifdef __cplusplus
}
#endif



#endif /* EXTERN_H_ */
