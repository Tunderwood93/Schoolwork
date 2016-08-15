package controller;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.String;

import model.TopWindowModel;
import view.MainView;
import view.JFrameView;
import model.Account;

/**
 * 
 * @author Trevor Underwood
 *	Main Controller class that handles changes in the view and sends to separate controllers.
 *	Also handles output to the file for save and exit.
 */
public class MainController extends AbstractController
{
	public ArrayList<Account> listOfAccounts = new ArrayList<Account>();
	public Account accountHolder;
	
	public MainController(ArrayList<Account> accountList, String fileName)
	{
		listOfAccounts = accountList;
		setModel(new TopWindowModel());
		((TopWindowModel)getModel()).listOfAccounts = listOfAccounts;
		setView(new MainView((TopWindowModel)getModel(), this, listOfAccounts, 4, fileName));
		((JFrameView)getView()).setVisible(true);
	}
	
	public void operation(String option, String fileName)
	{
		if(option.equals(MainView.EDITINUSD))
		{
			new BalanceController((TopWindowModel)getModel(), accountHolder, 0);
		}
		else if(option.equals(MainView.EDITINEURO))
		{
			new BalanceController((TopWindowModel)getModel(), accountHolder, 1);
		}
		else if(option.equals(MainView.EDITINYEN))
		{
			new BalanceController((TopWindowModel)getModel(), accountHolder, 2);
		}	
		else if(option.equals(MainView.SAVE))
		{
			writeToFile(fileName);	
		}
		else if(option.equals(MainView.EXIT))
		{
			writeToFile(fileName);
			((JFrameView)getView()).dispose();	
		}
		else if(option.equals(MainView.CREATEWITHDRAW))
		{
			new TopWindowController((TopWindowModel)getModel(), accountHolder, 1);
		}
		else if(option.equals(MainView.CREATEDEPOSIT))
		{
			new TopWindowController((TopWindowModel)getModel(), accountHolder, 0);
		}
	}
	
	public void setCurrentAccount(int acc)
	{
		accountHolder = listOfAccounts.get(acc);
	}
	
	public void writeToFile(String fileName)
	{
		PrintWriter writer;
		try {
			writer = new PrintWriter(fileName);
			for(int i = 0; i < listOfAccounts.size(); i++)
			{
				writer.println(listOfAccounts.get(i).ID + "   " + "|" + listOfAccounts.get(i).lastName + "    " + 
						listOfAccounts.get(i).firstName + "    " + listOfAccounts.get(i).middleInitial + "    | " + 
						listOfAccounts.get(i).funds + "   ");
			}
			writer.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
