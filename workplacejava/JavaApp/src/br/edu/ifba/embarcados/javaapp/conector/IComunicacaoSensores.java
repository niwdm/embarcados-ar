package br.edu.ifba.embarcados.javaapp.conector;

import com.sun.jna.Library;

public interface IComunicacaoSensores extends Library {
	
	public int iniciar(String porta);
	int ler();
	int getAcelX();
	int getAcelY();
	int getAcelZ();
	int getTerremoto();
	int getTemp();
	int getAltitude();
	int finalizar();	

}
