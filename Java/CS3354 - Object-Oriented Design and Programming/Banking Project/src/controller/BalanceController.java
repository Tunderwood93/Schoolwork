package controller;
import javax.swing.JOptionPane;

import view.JFrameView;
import view.EditingView;
import model.TopWindowModel;
import model.Account;


/**
 * 
 * @author Trevor Underwood
 *	Controller for determining what happens to the balance of an account during deposit and withdraw.
 */
public class BalanceController extends AbstractController
{
	public int currency;

	public BalanceController(TopWindowModel model, Account account, int currency)
	{
		setModel(model);
		setView(new EditingView((TopWindowModel)getModel(), this, account, currency));
		((JFrameView)getView()).setVisible(true);

		this.currency = currency;

		if(currency == 0) // Dollar
		{
			((EditingView)getView()).currentFunds.setText(String.valueOf(account.funds));
			((EditingView)getView()).setTitle(account.lastName + " " + account.firstName + "      " + "USD");
		}
		else if(currency == 1) // Euro
		{
			((EditingView)getView()).currentFunds.setText(String.valueOf(account.funds * 0.72));
			((EditingView)getView()).setTitle(account.lastName + " " + account.firstName + "      " + "Euros");
		}
		else if(currency == 2) // Yen
		{
			((EditingView)getView()).currentFunds.setText(String.valueOf(account.funds * 6.2));
			((EditingView)getView()).setTitle(account.lastName + " " + account.firstName + "      " + "Yen");
		}
	}

	public void operation(String option)
	{
		if(option.equals(EditingView.EXIT))
		{
			((JFrameView)getView()).dispose();
		}
		else if(option.equals(EditingView.WITHDRAW))
		{
			try
			{
				String withdraw = ((EditingView)getView()).amount.getText();
				Double toWithdraw = Double.valueOf(withdraw);		
				((TopWindowModel)getModel()).withdraw(toWithdraw, currency, ((EditingView)getView()).account);
				((EditingView)getView()).amount.setText("0");
			}
			catch(Exception error)
			{
				((EditingView)getView()).warning.showMessageDialog((EditingView)getView(),
						"Please enter only numbers.",
						"A number was not entered.",
						JOptionPane.WARNING_MESSAGE);
				((EditingView)getView()).amount.setText("0");
			}
		}
		else if(option.equals(EditingView.DEPOSIT))
		{
			String deposit = ((EditingView)getView()).amount.getText();
			Double toDeposit = Double.valueOf(deposit);
			
			if(toDeposit > 1)
			{
				try
				{
					((TopWindowModel)getModel()).deposit(toDeposit, currency, ((EditingView)getView()).account);
					((EditingView)getView()).amount.setText("0");
				}
				catch(Exception error)
				{
					((EditingView)getView()).warning.showMessageDialog((EditingView)getView(),
							"Please enter only numbers.",
							"A number was not entered.",
							JOptionPane.WARNING_MESSAGE);
					((EditingView)getView()).amount.setText("0");
				}
			}
			else
			{
				((EditingView)getView()).warning.showMessageDialog((EditingView)getView(),
						"Please enter only numbers greater than 1.",
						"A number less than 1 was entered.",
						JOptionPane.WARNING_MESSAGE);
				((EditingView)getView()).amount.setText("0");
			}
		}
	}
}
