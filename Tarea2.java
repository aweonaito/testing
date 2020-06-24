/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tarea2;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

/**
 *
 * @author felip
 */
public class Tarea2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        PipedOutputStream list_o = new PipedOutputStream();
        PipedInputStream list_i = new PipedInputStream(list_o);
        PipedOutputStream prim_o = new PipedOutputStream();
        PipedInputStream prim_i = new PipedInputStream(prim_o);

        Thread hilo1 = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    int a;
                    System.out.println("Introduce un numero:");
                    Scanner N = new Scanner(System.in);
                    a = N.nextInt();
                    if (a <= 2) {
                        System.out.println("Numero ingresado no valido");
                        list_o.write("Numero ingresado no valido".getBytes());
                        throw new Exception("no valido");
                        System.exit(0);
                    } else {
                        System.out.println(a);
                        for (int i = 2; i < a; i++) {
                            list_o.write((byte) i);
                            list_o.flush();
                        }
                        list_o.close();
                        int n = -1;
                        while ((n = prim_i.read()) != -1) {
                            System.out.println("Leyendo desde el hilo 1: " + n);
                        }
                        prim_i.close();
                    }
                } catch (IOException e) {
                }
            }
        });

        Thread hilop = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    int n = -1;
                    int i = 0;
                    int j;
                    while ((n = list_i.read()) != -1) {
                        if (n == 2 || n == 3 || n == 5 || n == 7) {
                            prim_o.write((byte) n);
                            prim_o.flush();
                        }
                        if (n % 2 != 0 && n % 3 != 0 && n % 5 != 0 && n % 7 != 0) {
                            prim_o.write((byte) n);
                            prim_o.flush();
                        }
                    }
                    list_i.close();
                    prim_o.close();
                } catch (IOException e) {
                }
            }
        });

        hilo1.start();
        hilop.start();

    }
}
