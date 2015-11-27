package br.edu.ifba.embarcados.javaapp;

import br.edu.ifba.embarcados.javaapp.asincexec.AsincExec;

public class Executor {

	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub
		/*IComunicacaoSensores conector = FabricaConectores.getConector(); //Enviaos para o AsincExec.java
		if (conector.iniciar("COM4") == 0) {
			while (true) {
				conector.ler();
				System.out.println("AcelX = " + conector.getAcelX());
				System.out.println("AcelY = " + conector.getAcelY());
				System.out.println("AcelZ = " + conector.getAcelZ());
				Thread.sleep(100);
			}
		}*/
		
		ListenerAcelerometro listener = new ListenerAcelerometro();
		
		AsincExec asinc = new AsincExec("COM4");
		
		asinc.addListener(listener);
		
		Thread t = new Thread(asinc);
		
		t.start();
		
		for (int i = 0; i < 50; i++) {
			Thread.sleep(1000);
		}
		
		asinc.setContinuar(false);
		t.join();
		System.out.println("Continuar: False!");
	}

}
