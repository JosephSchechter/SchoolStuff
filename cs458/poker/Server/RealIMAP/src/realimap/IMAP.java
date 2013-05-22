package realimap;

import java.awt.Dimension;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * An IMAP email Client
 * @author Alexander Black
 *
 */
public class IMAP extends JFrame implements ListSelectionListener
{
    //private DBAdapter emailData;

    private Boolean connected = false;
    private OutputStreamWriter out;
    private BufferedReader in;
    private Socket socket;
    private ArrayList<String> inputData;
    private String address;
    private int port;
    private String username;
    private String password;
    private ArrayList<Folder> folders;
    private ArrayList<Email> emails;
    private JTable localTable;
    private FileTableModel localModel;
    private boolean secure;
    private SSLSocket sslsocket;
    private final JComboBox previousAccounts;
    private Accounts accounts;
    private JTextArea message;

    IMAP()
    {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        try {//Attempts to read a list of saved email accounts/servers
            FileInputStream fis = new FileInputStream("accounts");
            ObjectInputStream inStream = new ObjectInputStream(fis);
            accounts = (Accounts) inStream.readObject();
            inStream.close();
        } catch (ClassNotFoundException ex) {
            accounts = new Accounts();
        } catch (IOException ex) {
            accounts = new Accounts();
        }

        setTitle("IMAP Email Cient");
        Panel n = new Panel();

        previousAccounts = new JComboBox(accounts.getList()); //List of previously used accounts

        previousAccounts.addActionListener(new ActionListener()
        {

            public void actionPerformed(ActionEvent e)
            {
                int selected = previousAccounts.getSelectedIndex(); //Sets the login info to that of the selected saved account
                address = accounts.getServer(selected);
                port = accounts.getPort(selected);
                username = accounts.getUsername(selected);
                password = accounts.getPassword(selected);
                secure = accounts.getSecure(selected);
            }
        });

        n.add(previousAccounts);


        JButton refresh = new JButton("Get Emails"); //Button that allows you to download messages

        refresh.addActionListener(
                new ActionListener()
                {//Listens to the refresh local table button

                    public void actionPerformed(ActionEvent e)
                    {
                        run();
                    }
                });

        n.add(refresh);


        add("North", n);

        localModel = new FileTableModel();
        localModel.addColumn("From");
        localModel.addColumn("Subject");
        localModel.addColumn("Date");

        localTable = new JTable(localModel);
        localTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        //localTable.setAutoCreateRowSorter(true);
        JScrollPane localListScrollPane = new JScrollPane(localTable);

        Dimension minimumSize = new Dimension(100, 50);
        localListScrollPane.setMinimumSize(minimumSize);

        localTable.getSelectionModel().addListSelectionListener(this);

        // add("Center", localListScrollPane);

        message = new JTextArea();
        JScrollPane messageScroll = new JScrollPane(message);
        messageScroll.setMinimumSize(minimumSize);
        // add("South", messageScroll);

        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                localListScrollPane, messageScroll);
        splitPane.setOneTouchExpandable(true);
        splitPane.setDividerLocation(350);

        add("Center", splitPane);

        setSize(800, 375);
        setVisible(true);

        inputData = new ArrayList<String>();
        emails = new ArrayList<Email>(); //The emails are stored in this ArrayList because I couldn't get the SQL database to work
    }

    /**
     * Sends a command to the server. Response from server is recorded to be used by a parsing method.
     * @param message The command to send
     */
    private void sendCommand(String message)
    {
        if (connected) {
            try {
                //System.out.println("Sending: . " + message);
                out.write(". " + message + "\r" + "\n");
                out.flush();
                readData();
            } catch (IOException ex) {
                System.out.println("IO Error Sending Command");
                connected = false;
            }
        }
    }

    /**
     * Connects to the server and sends login command
     */
    public void connect()
    {
        try {
            if (!secure) {
                socket = new Socket(address, port);
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out = new OutputStreamWriter(socket.getOutputStream());
            } else {
                // Open a connection as a client.
                SSLSocketFactory sslsocketfactory = (SSLSocketFactory) SSLSocketFactory.getDefault();
                sslsocket = (SSLSocket) sslsocketfactory.createSocket(address, port);
                in = new BufferedReader(new InputStreamReader(sslsocket.getInputStream()));
                out = new OutputStreamWriter(sslsocket.getOutputStream());
            }
            connected = true;
            sendCommand("login " + username + " " + password);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Listens to response from server and stops listening when server finishes command
     * @param command The command the server is responding to
     */
    private void readData()
    {
        inputData.clear();
        String input;
        try {
            while (!(input = in.readLine()).startsWith(". OK ")) {
                inputData.add(input);
            }
        } catch (IOException ex) {
            connected = false;
        }
    }

    /**
     * Parses the response from a select command.
     * @return The number of emails in the selected folder.
     */
    private int parseSelect()
    {
        for (int i = 0; i < inputData.size(); i++) {
            if (inputData.get(i).endsWith("EXISTS")) {
                String data = inputData.get(i);
                data = data.substring(data.indexOf(" ") + 1, data.indexOf(" ", data.indexOf(" ") + 1));
                return Integer.parseInt(data);
            }
        }
        return 0;
    }

    /**
     * Fetches an email and parses from, subject, date, and message data from it
     * @param messageNum Message number of the email you'd like to retrieve
     */
    private void readEmail(int messageNum)
    {
        sendCommand("fetch " + messageNum + " (body[header.fields (from subject date)])"); //Gets from, subject, and date
        String subject = "";
        String date = "";
        String from = "";

        for (int i = 0; i < inputData.size(); i++) {
            String test = inputData.get(i);
            if (test.startsWith("Date:")) {
                date = inputData.get(i);
                date = date.substring(date.indexOf(" ") + 1); //Removes unimportant information
            } else if (test.startsWith("From:")) {
                from = inputData.get(i);
                from = from.substring(from.lastIndexOf(" ") + 2, from.length() - 1); //Removes unimportant information
            } else if (test.startsWith("Subject")) {
                subject = inputData.get(i);
                subject = subject.substring(subject.indexOf(" ") + 1); //Removes unimportant information
            }
        }
        sendCommand("fetch " + messageNum + " rfc822.text"); //Gets the message
        String message = "";
        inputData.remove(0);
        inputData.remove(inputData.size() - 1);
        for (int i = 0; i < inputData.size(); i++) {
            message = message + inputData.get(i) + "\n";
        }

        emails.add(new Email(date, subject, from, message)); //Add the email to our list of emails
    }

    /**
     * Parse the response to the list all folders command
     * @return All the folders in the account
     */
    private ArrayList<Folder> parseFolders()
    {
        ArrayList<Folder> toReturn = new ArrayList<Folder>();
        String name = "";
        for (int i = 0; i < inputData.size(); i++) {
            name = inputData.get(i);
            name = name.substring(name.lastIndexOf("\"/\"") + 5, name.length() - 1);
            if (!name.subSequence(0, 1).equals("[")) {
                toReturn.add(new Folder(name, 0));
            }
        }
        return toReturn;
    }

    /**
     * Retrieves every email in every folder in the account on the server.
     */
    private void getMessages()
    {
        if (connected) {
            emails.clear();
            sendCommand("list \"\" \"*\""); // Lists all the folders on the account
            folders = parseFolders();
            for (int i = 0; i < folders.size(); i++) {
                Folder currentFolder = folders.get(i);
                sendCommand("select " + currentFolder.getName());
                currentFolder.setCount(parseSelect());
                folders.set(i, currentFolder);
                for (int j = 0; j < currentFolder.getCount(); j++) //Now reads all the emails in the folders
                {
                    int messageNum = j + 1;
                    readEmail(messageNum);
                }
            }
        }
        connected = false;
        try {
            if (in != null) {
                in.close();
            }
            if (out != null) {
                out.close();
            }
            if (socket != null) {
                socket.close();
            }
        } catch (IOException e) {
        }
    }

    /**
     * Starts the process of actually connecting to the server to retrieve emails
     */
    private void run()
    {
        if (username == null || password == null || address == null || port < 1) { //Retrieve the login info from client if none is set
            FileOutputStream fos = null;
            {
                ObjectOutputStream outStream = null;
                try {
                    address = (String) JOptionPane.showInputDialog("Enter the server address: ");
                    port = Integer.parseInt(JOptionPane.showInputDialog("Enter the port: "));
                    JOptionPane pane = new JOptionPane("Use SSL?");
                    Object[] options = new String[]{"No", "Yes"};
                    pane.setOptions(options);
                    JDialog dialog = pane.createDialog(new JFrame(), "Dialog");
                    dialog.setVisible(true);
                    Object obj = pane.getValue();
                    if (options[0].equals(obj)) {
                        secure = false;
                    } else {
                        secure = true;
                    }
                    username = (String) JOptionPane.showInputDialog("Enter your username: ");
                    password = (String) JOptionPane.showInputDialog("Enter your password: ");
                    accounts.addAccount(address, port, username, password, secure);

                    fos = new FileOutputStream("accounts");
                    outStream = new ObjectOutputStream(fos);
                    outStream.writeObject(accounts);
                    outStream.flush();

                    previousAccounts.addItem(address + ":" + port + " - " + username); //Add to the list of used accounts
                    previousAccounts.setSelectedIndex(previousAccounts.getItemCount()-1);
                } catch (IOException ex) {
                    Logger.getLogger(IMAP.class.getName()).log(Level.SEVERE, null, ex);
                } finally {
                    try {
                        fos.close();
                    } catch (IOException ex) {
                        Logger.getLogger(IMAP.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    try {
                        outStream.close();
                    } catch (IOException ex) {
                        Logger.getLogger(IMAP.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        }
        connect();

        getMessages();

        updateTable();
    }

    /**
     * Updates the table of email headers
     */
    private void updateTable()
    {
        localModel.clear();
        for (int i = 0; i < emails.size(); i++) {
            localModel.addRow(new String[]{emails.get(i).getFrom(), emails.get(i).getSubject(), emails.get(i).getDate()});
        }
    }

    /**
     * Listens for updates of what email header is selected and posts the corresponding message in our window.
     * @param e
     */
    public void valueChanged(ListSelectionEvent e)
    {
        if(emails.size() > localTable.getSelectedRow())
            message.setText(emails.get(localTable.getSelectedRow()).getMessage());
        else
            message.setText("");
    }
}
