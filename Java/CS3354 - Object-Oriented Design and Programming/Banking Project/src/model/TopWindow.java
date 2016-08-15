package model;



/**
 * 
 * @author Trevor Underwood
 *	Class for the pop out windows. Uses thread for synchronization amongst actions.
 */
public class TopWindow extends Thread
{
	public int ID;
	public Account account;
	public TopWindowModel model;
	public double amount;
	public int option;

	public int deposit = 0;
	public int withdraw = 1;
	public boolean going = true;
	public int numOfOperationsFinished = 0;
	public double totalMoneyTransfered = 0;
	public double operations;

	public TopWindow(int ID, double amount, double ops, int option, Account account, TopWindowModel model)
	{
		this.ID = ID;
		this.account = account;
		this.model = model;
		this.amount = amount;
		this.option = option;
		this.operations = ops;
	}

	public void run()
	{
		if(option == 0) // Deposit
		{
			try{
				while(this.going)
				{
					long millis = (long)operations * 1000;
					account.funds += amount;
					numOfOperationsFinished++;
					totalMoneyTransfered += amount;
					ModelEvent current = new ModelEvent(this, 1, "", account, account.funds);
					model.notifyChanged(current);
					Thread.sleep(millis);
				}
			}catch(InterruptedException e)
			{
				// Something?
			}
		}
		else // Withdraw
		{
			try{
				while(this.going)
				{
					long millis = (long)operations * 1000;
					account.funds -= amount;
					numOfOperationsFinished++;
					totalMoneyTransfered -= amount;
					ModelEvent current = new ModelEvent(this, 1, "", account, account.funds);
					model.notifyChanged(current);
					Thread.sleep(millis);
				}
			}catch(InterruptedException e){
				// Something?
			}
		}
	}
}
