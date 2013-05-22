/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package realimap;

/**
 *
 * @author bootes
 */
import javax.swing.table.DefaultTableModel;

/**
 * FileTableModel is the model for file tables for the Gnutella application
 *
 * @author Alexander Black
 * @author Edward Cheung
 * @version 1.0 11/17/10
 */
@SuppressWarnings("serial")
public class FileTableModel extends DefaultTableModel
{

    /**
     * No cells should be editable by the user
     */
    public boolean isCellEditable(int row, int column)
    {
        return false;
    }

    /**
     * Clears the table
     */
    public void clear()
    {
        dataVector.clear();
        /*for(int i = 0; i < getRowCount(); i++)
        {
        removeRow(0);
        }*/
    }
}
