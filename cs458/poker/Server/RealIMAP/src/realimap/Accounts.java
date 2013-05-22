package realimap;

import java.io.Serializable;
import java.util.ArrayList;

/**
 *  Stores email accounts and their servers
 * @author Alexander Black
 */
public class Accounts implements Serializable
{

    ArrayList<String[]> accounts;

    Accounts()
    {
        accounts = new ArrayList<String[]>();
        accounts.add(new String[]{null, "0", null, null, "false"});
    }

    /**
     * Add an email account that has been used
     * @param server
     * @param port
     * @param username
     * @param password
     * @param secure
     */
    public void addAccount(String server, int port, String username, String password, Boolean secure)
    {
        if (secure) {
            accounts.add(new String[]{server, Integer.toString(port), username, password, "true"});
        } else {
            accounts.add(new String[]{server, Integer.toString(port), username, password, "false"});
        }
    }

    /**
     * Retrieve the server for
     * @param i index
     * @return
     */
    public String getServer(int i)
    {
        return accounts.get(i)[0];
    }

    /**
     * Retrieve the port for
     * @param i
     * @return
     */
    public int getPort(int i)
    {
        return Integer.parseInt(accounts.get(i)[1]);
    }

    /**
     * Retrieve the username for
     * @param i
     * @return
     */
    public String getUsername(int i)
    {
        return accounts.get(i)[2];
    }

    /**
     * Retrieve the password for
     * @param i
     * @return
     */
    public String getPassword(int i)
    {
        return accounts.get(i)[3];
    }

    /**
     * Retrieve whether SSL is used for
     * @param i
     * @return
     */
    public Boolean getSecure(int i)
    {
        if (accounts.get(i)[4].equals("true")) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Gets the "name" of this account
     * @return Server:Port - Username
     */
    public String[] getList()
    {
        String[] toReturn = new String[accounts.size()];
        toReturn[0] = "New Account";
        for (int i = 1; i < accounts.size(); i++) {
            toReturn[i] = accounts.get(i)[0] + ":" + accounts.get(i)[1] + " - " + accounts.get(i)[2];
        }
        return toReturn;
    }
}
