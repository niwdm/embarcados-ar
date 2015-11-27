/*
 * Comunicacao.h
 *
 * Prover uma classe cujo os metodos possibilitam a
 * comunicação com o dispositivo controlador que
 * realiza a leitura do sensor gy-80/10DOF
 *
 *  Created on: 08/10/2015
 *      Author: Airton Ribeiro
 */

#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <stdlib.h>
#if _WIN32 || _WIN64
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#define Sleep(x) usleep(x * 1000);
#endif

#if _WIN32 || _WIN64
#define sleep(x)
#endif

class Comunicacao {
private:
	char* porta;
#ifdef __linux__
	int hPorta;
#endif
#if _WIN32 || _WIN64
	HANDLE hPorta;
#endif

public:
	Comunicacao(char* porta);

	//Iniciar a comunicacão com a porta serial
	int iniciar();

	//Realiza a leitura de um buffer a partir de uma porta serial
	int ler(char* buffer, long unsigned int bytesParaLer);

	//Finaliza o uso da porta serial
	int finalizar();

};

#endif /* COMUNICACAO_H_ */
