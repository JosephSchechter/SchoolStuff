package realimap;

import java.util.ArrayList;

/**
 * Symbolizes a folder that could contain emails
 * 
 * @author Alexander Black
 */
public class Folder
{

    private String name;
    private int count;

    /**
     * Creates a folder
     * @param name The name of the folder
     */
    Folder(String name, int count)
    {
        this.name = name;
        this.count = count;
    }

    /**
     * Get the number of emails the folder should contain according to the server
     * @return The number of emails the folder should contain
     */
    public int getCount()
    {
        return count;
    }

    /**
     * Set the number of emails the folder should contain
     * @param count the number of emails
     */
    public void setCount(int count)
    {
        this.count = count;
    }

    /**
     * Get the name of the folder
     * @return The name of the folder
     */
    public String getName()
    {
        return name;
    }
}
