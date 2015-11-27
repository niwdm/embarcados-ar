/*
 * Executor.cpp
 * Testa a comunicação com o arduino, retornando
 * e exibindo valores dos eixos do acelerometro
 *
 *  Created on: 15/10/2015
 *      Author: Airton Ribeiro
 */

#include "Comunicacao.h"

#include <iostream>

using namespace std;

struct Eixos { // necessario inserir todos os eixos dos sensores
	short acelx, acely, acelz, terremoto; // acelerômetro
	short temp, altitude; // barometro
};

int main(int argc, char **argv) {
	//Criar instancia da classe de comunicação
	//cout << "tam = " << sizeof(Eixos) << endl;
	//Comunicacao com = Comunicacao("/dev/ttyACM0");
	Comunicacao com = Comunicacao("COM4");
	//enquanto estiver executando...
	//realizar a leitura do caractere I Inicio
	if (com.iniciar() == EXIT_SUCCESS) {
		char ci, cf;
		Eixos eixos;
		while (true) {
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
						cout << "X = " << eixos.acelx << endl;
						cout << "Y = " << eixos.acely << endl;
						cout << "Z = " << eixos.acelz << endl;
						cout << "Terremoto = " << eixos.terremoto << endl;
						cout << "Temp = " << eixos.temp << endl;
						cout << "Altitude = " << eixos.altitude << endl;
					}
				}
			}
			Sleep(100);
		}
	}
	return EXIT_SUCCESS;
}
