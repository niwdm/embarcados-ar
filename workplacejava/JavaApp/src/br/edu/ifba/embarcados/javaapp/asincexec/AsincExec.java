package br.edu.ifba.embarcados.javaapp.asincexec;

import java.io.BufferedInputStream;
import java.io.FileInputStream;

import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.Logger;

import br.edu.ifba.embarcados.javaapp.Janela;
import br.edu.ifba.embarcados.javaapp.conector.FabricaConectores;
import br.edu.ifba.embarcados.javaapp.conector.IComunicacaoSensores;
import javazoom.jl.player.Player;

public class AsincExec implements Runnable {
	
	private String porta;
	private boolean continuar;
	
	private static final Logger logger = Logger.getLogger(AsincExec.class);
	
	private List<IListenerAcelerometro> listeners;
	
	public AsincExec(String porta) {
		this.porta = porta;
		listeners = new ArrayList<IListenerAcelerometro>();
	}
	
	public void addListener(IListenerAcelerometro listener) {
		listeners.add(listener);
	}
	
	public void setContinuar(boolean continuar){
		this.continuar = continuar;
	}
	
	public void playSirene () {
		String file="D:\\Documents\\workplacejava\\JavaApp\\src\\Siren.mp3";
		try {
		FileInputStream fis = new FileInputStream(file);
		BufferedInputStream bis = new BufferedInputStream(fis);
		Player player = new Player(bis);
		player.play();
		}
		catch (Exception ex) {
			System.out.println("Erro no som! " + ex);
		}
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		Janela jn = new Janela();
		IComunicacaoSensores conector = FabricaConectores.getConector();
		if (conector.iniciar(porta) == 0) {
			continuar = true;
			while (continuar) {
				conector.ler();
				/*System.out.println("AcelX = " + conector.getAcelX()); //removido por causa da interface
				System.out.println("AcelY = " + conector.getAcelY());
				System.out.println("AcelZ = " + conector.getAcelZ());*/
				//notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
				//notificarVibracao(conector.getTerremoto());
				//notificarBarometro(conector.getTemp(), conector.getAltitude());
				if (conector.getTerremoto() == 1){
					logger.info("Terremoto identificado! Altitude: " + conector.getAltitude() +
							"m. Temperatura: " + conector.getTemp() + "º.");
					jn.upTexto();
					playSirene();
				}
				
				try {
					Thread.sleep(50);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			conector.finalizar();
		}
	}
	
	/*private void notificar(int x, int y, int z) { //, int terremoto, int temp, int altitude
		for (IListenerAcelerometro listener : listeners) {
			listener.notificarMovimento(x, y, z); //terremoto, temp, altitude
		}
	}
	
	private void notificarBarometro(int temp, int altitude) {
		for (IListenerAcelerometro listener : listeners) {
			listener.notificarBarometro(temp, altitude); //terremoto, temp, altitude
		}
	}*/
	
	/*private void notificarVibracao(int terremoto) {
		for (IListenerAcelerometro listener : listeners) {
			listener.notificarVibracao(terremoto); //terremoto, temp, altitude
		}
	}*/


}