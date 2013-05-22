/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import java.security.Signature;
import java.security.SignatureException;
import java.security.SignedObject;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.CipherInputStream;
import javax.crypto.CipherOutputStream;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SealedObject;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;

/**
 * A Poker Game Server
 * @author Alexander Black
 * @author Joseph Schechter
 */
public class Serv
{

    public static void main(String[] argv)
    {
        // TODO code application logic here
        if (argv.length < 1) {
            System.out.println("Server must be called with port. serv <port_number>");
            System.exit(0);
        }
        new Serv(Integer.parseInt(argv[0]));
    }
    private PrivateKey serverKeyA, serverKeyB;
    private Socket sockA, sockB;
    private static final int AES_Key_Size = 256;
    private Cipher pkCipher, aesCipher;
    private byte[] aesKeyA, aesKeyB;
    private SecretKeySpec aeskeySpecA, aeskeySpecB;
    private int port;
    private DataInputStream inA, inB;
    private DataOutputStream outA, outB;
    private int turn;

    Serv(int port)
    {
        try {
            this.port = port;
            ServerSocket ss = new ServerSocket(port);
            ServerSocket ss1 = new ServerSocket(port + 1);
            // create RSA public key cipher
            pkCipher = Cipher.getInstance("RSA");
            // create AES shared key cipher
            aesCipher = Cipher.getInstance("AES");
            readPubPrivKeys();
            sockA = ss.accept();
            sockB = ss1.accept();
            turn = 0;

            run();
        } catch (IOException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchPaddingException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Starts server communication with clients and retrieves session keys
     */
    private void run()
    {
        try {
            outA = new DataOutputStream(sockA.getOutputStream());
            inA = new DataInputStream(sockA.getInputStream());
            outB = new DataOutputStream(sockB.getOutputStream());
            inB = new DataInputStream(sockB.getInputStream());

            //Read A's session key
            byte[] first = new byte[256];
            byte[] second = new byte[256];
            inA.readFully(first);
            inA.readFully(second);

            pkCipher.init(Cipher.DECRYPT_MODE, serverKeyA);
            first = pkCipher.doFinal(first);
            second = pkCipher.doFinal(second);

            aesKeyA = new byte[32];
            for (int i = 0; i < 16; i++) {
                aesKeyA[i] = first[i];
                aesKeyA[i + 16] = second[i];
            }
            aeskeySpecA = new SecretKeySpec(aesKeyA, "AES");

            //Read B's session key
            first = new byte[256];
            second = new byte[256];
            inB.readFully(first);
            inB.readFully(second);

            pkCipher.init(Cipher.DECRYPT_MODE, serverKeyB);
            first = pkCipher.doFinal(first);
            second = pkCipher.doFinal(second);

            aesKeyB = new byte[32];
            for (int i = 0; i < 16; i++) {
                aesKeyB[i] = first[i];
                aesKeyB[i + 16] = second[i];
            }
            aeskeySpecB = new SecretKeySpec(aesKeyB, "AES");

            System.out.println(readMessage('a')); //Greetings
            System.out.println(readMessage('b'));
            game();


            inA.close();
            inB.close();
            outA.close();
            outB.close();
            sockA.close();
            sockB.close();
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeyException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    /**
     * Generates random numbers
     * @return Three random numbers 1-15.
     */
    private int[] newRandom()
    {
        int Max = 15;
        int Min = 1;

        int[] nums = new int[3];
        nums[0] = Min + (int) (Math.random() * ((Max - Min) + 1));
        nums[1] = Min + (int) (Math.random() * ((Max - Min) + 1));
        while (nums[0] == nums[1]) {
            nums[1] = Min + (int) (Math.random() * ((Max - Min) + 1));
        }

        nums[2] = Min + (int) (Math.random() * ((Max - Min) + 1));
        while (nums[0] == nums[2] || nums[1] == nums[2]) {
            nums[2] = Min + (int) (Math.random() * ((Max - Min) + 1));
        }
        return nums;
    }

    /**
     * Plays a poker game
     */
    private void game()
    {
        int aWins = 0;
        int bWins = 0;

        while (aWins < 2 && bWins < 2) {
            int[] rand = newRandom();
            System.out.println(rand[0] + " " + rand[1] + " " + rand[2]);

            int a = Integer.parseInt(readMessage('a'));
            int b = Integer.parseInt(readMessage('b'));

            if (rand[a] > rand[b]) {
                //A Wins
                sendMessage("won", 'a');
                sendMessage("lost", 'b');
                aWins++;
            } else if (rand[b] > rand[a]) {
                //B Wins
                sendMessage("won", 'b');
                sendMessage("lost", 'a');
                bWins++;
            } else {
                //Tie
                sendMessage("tie", 'a');
                sendMessage("tie", 'b');
            }
            turn++;
            sendMessage("newround", 'a');
            sendMessage("newround", 'b');
            System.out.println(aWins + " " + bWins);
        }

        if (aWins >= 2) {
            sendMessage("Win", 'a');
            sendMessage("Lost", 'b');
        } else {
            sendMessage("Win", 'b');
            sendMessage("Lost", 'a');
        }
    }

    /**
     * Reads a message from a client
     * @param client Which client to read from
     * @return The message received
     */
    private String readMessage(char client)
    {
        String toRet = "";
        try {
            byte[] enc;
            if (client == 'a') {
                enc = new byte[inA.readInt()];
                inA.readFully(enc);
            } else {
                enc = new byte[inB.readInt()];
                inB.readFully(enc);
            }
            toRet = decrypt(new String(enc), client);

        } catch (InvalidKeyException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
        return toRet;
    }

    /**
     * Sends a message to a client
     * @param message The message you wish to send
     * @param client Which client to send the message to
     */
    private void sendMessage(String message, char client)
    {
        try {
            byte[] enc;
            enc = encrypt(message, client).getBytes();
            if (client == 'a') {
                outA.writeInt(enc.length);
                outA.write(enc);
            } else {
                outB.writeInt(enc.length);
                outB.write(enc);
            }

        } catch (IOException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeyException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Encrypts a message with the session key
     * @param message the message you wish to encrypt
     * @param client who to send the message to
     */
    private String encrypt(String message, char client) throws IOException, InvalidKeyException
    {
        String encrypted = "";
        try {
            if (client == 'a') {
                aesCipher.init(Cipher.ENCRYPT_MODE, aeskeySpecA);
            } else {
                aesCipher.init(Cipher.ENCRYPT_MODE, aeskeySpecB);
            }
            // Gets the raw bytes to encrypt, UTF8 is needed for
            // having a standard character set
            byte[] stringBytes = message.getBytes("UTF8");
            // encrypt using the cypher
            byte[] raw = aesCipher.doFinal(stringBytes);
            // converts to base64 for easier display.
            BASE64Encoder encoder = new BASE64Encoder();
            encrypted = encoder.encode(raw);
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
        return encrypted;
    }

    /**
     * Decrypts a message from the client
     * @param encrypted the message(encrypted)
     * @param client who the message was received from
     */
    private String decrypt(String encrypted, char client) throws IOException, InvalidKeyException
    {
        String clear = "";
        try {
            if (client == 'a') {
                aesCipher.init(Cipher.DECRYPT_MODE, aeskeySpecA);
            } else {
                aesCipher.init(Cipher.DECRYPT_MODE, aeskeySpecB);
            }
            BASE64Decoder decoder = new BASE64Decoder();
            byte[] raw = decoder.decodeBuffer(encrypted);
            //decode the message
            byte[] stringBytes = aesCipher.doFinal(raw);
            //converts the decoded message to a String
            clear = new String(stringBytes, "UTF8");
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
        return clear;
    }

    /**
     * Reads the private RSA keys
     */
    private void readPubPrivKeys()
    {
        try {
            KeyFactory kf = KeyFactory.getInstance("RSA");


            File f = new File("ServerAPrivate.der");
            byte[] encodedKey = new byte[(int) f.length()];
            new FileInputStream(f).read(encodedKey);
            PKCS8EncodedKeySpec privateKeySpec = new PKCS8EncodedKeySpec(encodedKey);
            serverKeyA = kf.generatePrivate(privateKeySpec);

            f = new File("ServerBPrivate.der");
            encodedKey = new byte[(int) f.length()];
            new FileInputStream(f).read(encodedKey);
            privateKeySpec = new PKCS8EncodedKeySpec(encodedKey);
            serverKeyB = kf.generatePrivate(privateKeySpec);



        } catch (IOException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeySpecException ex) {
            Logger.getLogger(Serv.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
