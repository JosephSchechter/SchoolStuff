/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package clienta;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.CipherInputStream;
import javax.crypto.CipherOutputStream;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

/**
 * A Poker Game Client
 * @author Alexander Black
 * @author Joseph Schechter
 */
public class CliA
{

    public static void main(String[] args)
    {
        // TODO code application logic here
        if (args.length < 2) {
            System.out.println("Client must be called with server and port. cli <server_machine> <server_port>");
            System.exit(0);
        }
        new CliA(args[0], Integer.parseInt(args[1]));
    }
    private Socket sock;
    private PublicKey serverKey;
    private PrivateKey clientKey;
    public static final int AES_Key_Size = 256;
    Cipher pkCipher, aesCipher;
    byte[] aesKey;
    SecretKeySpec aeskeySpec;
    private DataOutputStream out;
    private DataInputStream in;
    private int turn;
    private BufferedReader inL;

    private CliA(String address, int port)
    {
        try {
            pkCipher = Cipher.getInstance("RSA");
            // create AES shared key cipher
            aesCipher = Cipher.getInstance("AES");
            makeKey();
            connect(address, port);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchPaddingException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Connects to the server
     * @param address Server's IP Address
     * @param port Server's IP
     */
    public void connect(String address, int port)
    {
        try {
            readPubPrivKeys();
            sock = new Socket(address, port);

            pkCipher.init(Cipher.ENCRYPT_MODE, serverKey);

            out = new DataOutputStream(sock.getOutputStream());
            in = new DataInputStream(sock.getInputStream());
            inL = new BufferedReader(new InputStreamReader(System.in));



            int length = aesKey.length / 2;
            byte[] first = new byte[length];
            byte[] second = new byte[length];
            for (int i = 0; i < length; i++) {
                first[i] = (byte) aesKey[i];
                second[i] = (byte) aesKey[i + length];
            }
            first = pkCipher.doFinal(first);
            second = pkCipher.doFinal(second);
            out.write(first);
            out.write(second);

            sendMessage("Ahello");

            game();

            in.close();
            inL.close();
            out.close();
            sock.close();

        } catch (UnknownHostException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeyException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Runs a poker game
     */
    private void game()
    {
        int aWins = 0;
        int bWins = 0;
        System.out.println("Welcome!");


        while (aWins < 2 && bWins < 2) {
            Boolean goodPick = false;
            int pick = 0;
            while (!goodPick) {
                try {
                    System.out.println("Pick a number 1-3");
                    pick = Integer.parseInt(inL.readLine());
                    if (pick <= 3 && pick >= 1) {
                        goodPick = true;
                    }
                } catch (IOException ex) {
                    Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            pick--;
            sendMessage(Integer.toString(pick));

            String response = readMessage();
            if (response.equals("won")) {
                System.out.println("You Won This Round!");
                aWins++;
            } else if (response.equals("lost")) {
                System.out.println("You Lost This Round");
                bWins++;
            } else if (response.equals("tie")) {
                System.out.println("You Tied This Round");
            } else {
                System.exit(0);
            }
            turn++;
            readMessage(); //New round
        }
        String response = readMessage();
        if (response.equals("Win")) {
            System.out.println("You Won The Game!!! :D");
        } else if (response.equals("Lost")) {
            System.out.println("You Lost :(");
        }
    }

    /**
     * Reads a message from the server
     * @return The message received from the server
     */
    private String readMessage()
    {
        String toRet = "";
        try {
            byte[] enc = new byte[in.readInt()];
            in.readFully(enc);
            toRet = decrypt(new String(enc));

        } catch (InvalidKeyException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
        return toRet;
    }

    /**
     * Sends a message to the server
     * @param message Message you want to send
     */
    private void sendMessage(String message)
    {
        try {
            byte[] enc = encrypt(message).getBytes();
            out.writeInt(enc.length);
            out.write(enc);
        } catch (IOException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeyException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Creates a new AES key
     */
    public void makeKey() throws NoSuchAlgorithmException
    {
        KeyGenerator kgen = KeyGenerator.getInstance("AES");
        kgen.init(AES_Key_Size);
        SecretKey key = kgen.generateKey();
        aesKey = key.getEncoded();
        aeskeySpec = new SecretKeySpec(aesKey, "AES");
    }

    /**
     * Encrypts a message with the session key
     */
    public String encrypt(String message) throws IOException, InvalidKeyException
    {
        String encrypted = "";
        try {
            aesCipher.init(Cipher.ENCRYPT_MODE, aeskeySpec);
            // Gets the raw bytes to encrypt, UTF8 is needed for
            // having a standard character set
            byte[] stringBytes = message.getBytes("UTF8");
            // encrypt using the cypher
            byte[] raw = aesCipher.doFinal(stringBytes);
            // converts to base64 for easier display.
            BASE64Encoder encoder = new BASE64Encoder();
            encrypted = encoder.encode(raw);
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
        return encrypted;
    }

    /**
     * Decrypts a message from the server with the session key
     */
    public String decrypt(String encrypted) throws IOException, InvalidKeyException
    {
        String clear = "";
        try {
            aesCipher.init(Cipher.DECRYPT_MODE, aeskeySpec);
            BASE64Decoder decoder = new BASE64Decoder();
            byte[] raw = decoder.decodeBuffer(encrypted);
            //decode the message
            byte[] stringBytes = aesCipher.doFinal(raw);
            //converts the decoded message to a String
            clear = new String(stringBytes, "UTF8");
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
        return clear;
    }

    /** Reads the RSA key(s) */
    public void readPubPrivKeys()
    {
        try {
            KeyFactory kf = KeyFactory.getInstance("RSA");


            File f = new File("ServerAPublic.der");
            byte[] encodedKey = new byte[(int) f.length()];
            new FileInputStream(f).read(encodedKey);
            X509EncodedKeySpec publicKeySpec = new X509EncodedKeySpec(encodedKey);
            serverKey = kf.generatePublic(publicKeySpec);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeySpecException ex) {
            Logger.getLogger(CliA.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
