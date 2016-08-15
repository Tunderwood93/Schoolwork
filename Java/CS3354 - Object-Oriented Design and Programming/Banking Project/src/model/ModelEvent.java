package model;

import java.awt.event.ActionEvent;


public class ModelEvent extends ActionEvent
{
	Account account;
	double funds;

	public ModelEvent(Object obj, int id, String message, Account account, double funds)
	{
		super(obj, id, message);

		this.account = account;
		this.funds = funds;
	}

	public Account getAccount()
	{
		return account;
	}
}
