/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package databasebuilder;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.security.Security;
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
            // Construct data
            System.setProperty("java.protocol.handler.pkgs", "com.sun.net.ssl.internal.www.protocol");
            Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider());
            URL url = new URL("https://buonline.binghamton.edu/banner/bwckschd.p_disp_dyn_sched");
            //String data = URLEncoder.encode("p_calling_proc", "UTF-8") + "=" + URLEncoder.encode("bwckschd.p_disp_dyn_sched", "UTF-8");
            String data =  URLEncoder.encode("p_term", "UTF-8") + "=" + URLEncoder.encode("201120", "UTF-8");


            URLConnection con = (URLConnection) url.openConnection();
            con.setDoOutput(true);
            OutputStreamWriter wr = new OutputStreamWriter(con.getOutputStream());
            wr.write(data);
            wr.flush();

            InputStream is = con.getInputStream();
            byte[] dataR = new byte[is.available()];
            is.read(dataR);
            String str = new String(dataR, 0, dataR.length);
            System.out.println("returned data " + str);
        } catch (Exception e) {
        }
    }
}
