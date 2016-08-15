package model;

import java.util.ArrayList;


/**
 * @author Trevor Underwood
 * Will use synchronization so threads don't get in each other's way.
 * Used for controlling the deposit and withdraw, as well as creating those windows.
 * Implements methods for the deposit and withdraw windows.
 */
public class TopWindowModel extends AbstractModel
{
	public ArrayList<Account> listOfAccounts = new ArrayList<Account>();
	public ArrayList<TopWindow> listOfWindows = new ArrayList<TopWindow>();
	boolean runningAgent = false;
	boolean windowExists = false;

	public TopWindow makeTopWindow(int TopWindowID, double amount, double ops, int type, Account accHolder)
	{
		TopWindow window;

		//Run through current list to check if it's already created.
		for(int i = 0; i < listOfWindows.size(); i++)
		{
			if(listOfWindows.get(i).ID == TopWindowID)
			{
				windowExists = true;
			}
		}

		// If it doesn't exist, create it.
		if(windowExists == false)
		{	
			if(type == 0)// Make deposit window
			{
				window = new TopWindow(TopWindowID, amount, ops, type, accHolder, this);
				listOfWindows.add(window);
				window.start();
			}
			else// Make withdraw window
			{
				window = new TopWindow(TopWindowID, amount, ops, type, accHolder, this);
				listOfWindows.add(window);
				window.start();
			}
		}
		else // If it does exist, return nothing
		{
			window = null;
		}
		return window;
	}

	public void startWindow(TopWindow window)
	{
		if(window.option == 0) // 0 is deposit
		{
			boolean passed = false;
			passed = deposit(window.amount, 1, window.account);
			while(passed == false)
			{
				runningAgent = false;
			}
			runningAgent = true;
		}
		else if(window.option == 1)// 1 is withdraw
		{
			withdraw(window.amount, 1, window.account);
			runningAgent = true;
		}
	}

	public boolean deposit(double toDeposit, int currency, Account account)
	{
		boolean depositHappened = false;
		int accountIndex = 0;
		while(listOfAccounts.get(accountIndex).ID != account.ID)
		{
			accountIndex++;
		}

		if(currency == 0) // Dollar
		{
			listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds + toDeposit;
			depositHappened = true;
		}
		else if(currency == 1) // Euro
		{
			listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds + (toDeposit * 0.72);
			depositHappened = true;
		}
		else if(currency == 2) // Yen
		{
			listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds + (toDeposit * 94.1);
			depositHappened = true;	
		}

		ModelEvent current = new ModelEvent(this, 1, "", listOfAccounts.get(accountIndex), listOfAccounts.get(accountIndex).funds);
		notifyChanged(current);
		return depositHappened;
	}

	public boolean withdraw(double toWithdraw, int currency, Account account)
	{
		boolean withdrawHappened = false;

		int accountIndex = 0;
		while(listOfAccounts.get(accountIndex).ID != account.ID)
		{
			accountIndex++;
		}

		if(currency == 0) // Dollar
		{
			if(listOfAccounts.get(accountIndex).funds >= toWithdraw)
			{
				listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds - toWithdraw;
				withdrawHappened = true;
			}
		}
		else if(currency == 1) // Euro
		{
			toWithdraw = toWithdraw * 0.72;
			if(listOfAccounts.get(accountIndex).funds >= toWithdraw)
			{
				listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds - toWithdraw;
				withdrawHappened = true;
			}
		}
		else if(currency == 2) // Yen
		{
			toWithdraw = toWithdraw * 6.2;
			if(listOfAccounts.get(accountIndex).funds >= toWithdraw)
			{
				listOfAccounts.get(accountIndex).funds = listOfAccounts.get(accountIndex).funds - toWithdraw;
				withdrawHappened = true;
			}
		}

		ModelEvent current = new ModelEvent(this, 1, "",  listOfAccounts.get(accountIndex), listOfAccounts.get(accountIndex).funds);
		notifyChanged(current);

		return withdrawHappened;
	}

	public void stopWindow(TopWindow window)
	{
		window.going = false;
	}
}
