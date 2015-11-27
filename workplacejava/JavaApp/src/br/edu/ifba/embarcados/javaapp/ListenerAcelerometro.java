package br.edu.ifba.embarcados.javaapp;

import br.edu.ifba.embarcados.javaapp.asincexec.IListenerAcelerometro;

public class ListenerAcelerometro implements IListenerAcelerometro{

	@Override
	public void notificarMovimento(int x, int y, int z) { // int terremoto, int temp, int altitude
		// TODO Auto-generated method stub
		System.out.print("X = " + x + "\t\t");
		System.out.print("Y = " + y + "\t\t");
		System.out.println("Z = " + z + "\t\t");
		//System.out.print("Terremoto = " + terremoto + "\t\t");
		//System.out.print("Temp = " + temp + "\t\t");
		//System.out.println("Altitude = " + altitude);
		
	}

	@Override
	public void notificarVibracao(int terremoto) {
		// TODO Auto-generated method stub
		System.out.println("Terremoto = " + terremoto);
	}
	
	public void notificarBarometro (int temp, int altitude){
		System.out.print("Temp = " + temp + "\t\t");
		System.out.println("Altitude = " + altitude);
	}
	
}
