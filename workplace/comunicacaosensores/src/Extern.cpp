/*
 * Extern.cpp
 * Externalização das funcoes da rotina de acesso ao acelerometero
 *
 *  Created on: 15/10/2015
 *      Author: Airton Ribeiro
 */

#include "Extern.h"
#include "Comunicacao.h"

struct Eixos { // necessario inserir todos os eixos dos sensores
	short acelx, acely, acelz, terremoto; // acelerômetro
	short temp, altitude; // barometro
};
Eixos eixos;

Comunicacao com = NULL;

int iniciar(char* porta) {
	com = Comunicacao(porta);
	return com.iniciar();
}

int ler() {
	char ci, cf;
	int resultado = com.ler((char*) &ci, sizeof(ci));
	if (resultado == EXIT_SUCCESS && (ci == 'I')) {
		//Se ocorrer tudo bem
		//Ler os eixos
		resultado = com.ler((char*) &eixos, sizeof(eixos));
		if (resultado == EXIT_SUCCESS) {
			//Se ler os eixos e carateres ocorrer bem
			//Ler o caractere F Final
			resultado = com.ler((char*) &cf, sizeof(cf));
			if ((resultado == EXIT_SUCCESS) && (cf == 'F')) {
				//se tudo for atendido exibe os eixos co Acelerometro
				resultado = EXIT_SUCCESS;
			}
		}
	}
	return resultado;
}

int getAcelX() {
	return (int)eixos.acelx;
}

int getAcelY() {
	return (int)eixos.acely;
}

int getAcelZ() {
	return (int)eixos.acelz;
}

int getTerremoto() {
	return (int)eixos.terremoto;
}

int getTemp() {
	return (int)eixos.temp;
}

int getAltitude() {
	return (int)eixos.altitude;
}

int finalizar() {
	return com.finalizar();
}
