package br.edu.ifba.embarcados.javaapp;

import java.awt.BorderLayout;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.swing.JFrame;
import javax.swing.*;

@SuppressWarnings("serial")
public class Janela extends JFrame {
	public JTextArea ta;
	public JScrollPane jp;
	public Janela() {
		super("Log Monitoramento");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        ta = new JTextArea(24, 12);
        jp = new JScrollPane(ta);
        add(jp, BorderLayout.CENTER);
        pack();
        setSize(600, 400);
        setLocationByPlatform(true);
        setVisible(true);
        
        File file = new File("D:\\Documents\\workplacejava\\JavaApp\\log_monitoramento.log");
        FileInputStream fis = null;
        String texto = "";
        try {
            fis = new FileInputStream(file);
            int content;
            while ((content = fis.read()) != -1) {
                texto += (char) content;
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (fis != null) {
                    fis.close();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }

        ta.setText(texto);
        ta.setLineWrap(true); //quebra de linha automática
        
    }
    public void upTexto(){
    	File file = new File("D:\\Documents\\workplacejava\\JavaApp\\log_monitoramento.log");
        FileInputStream fis = null;
        String texto = "";

        try {
            fis = new FileInputStream(file);
            int content;
            while ((content = fis.read()) != -1) {
                texto += (char) content;
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (fis != null) {
                    fis.close();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    	ta.setText(texto);
    	ta.setCaretPosition(ta.getDocument().getLength());
    }
}