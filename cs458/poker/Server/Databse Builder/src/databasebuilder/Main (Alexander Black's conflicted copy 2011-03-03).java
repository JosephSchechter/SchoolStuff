/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package databasebuilder;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Alexander Black
 */
public class Main
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new Main();
    }

    Main()
    {
        try {
            URL courseList = new URL("/submit.html?major=" + "&crn=&name=&prof=&location=");
            BufferedReader in = new BufferedReader(new InputStreamReader(courseList.openStream()));
            String inputLine; // = in.readLine();
            while ((inputLine = in.readLine()) != null) 
            {
                int i;
            }
        } catch (MalformedURLException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }

    }
}
