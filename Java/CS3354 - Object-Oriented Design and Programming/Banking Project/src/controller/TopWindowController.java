package controller;
import javax.swing.JOptionPane;

import model.TopWindowModel;
import view.TopWindowView;
import model.Account;
import model.TopWindow;
import view.JFrameView;
import view.NewTopWindow;



public class TopWindowController extends AbstractController
{
	TopWindow window;	
	Account account;
	public TopWindowController(TopWindowModel window, Account account, int option)
	{
		setModel(window);
		setView(new TopWindowView((TopWindowModel)getModel(), this, option, account));
		((JFrameView)getView()).setVisible(true);
		if(option == 0)
		{
			((TopWindowView)getView()).setTitle("Start Deposit for: " + account.firstName + " " + account.lastName);
		}
		else 
		{
			((TopWindowView)getView()).setTitle("Start Withdraw for: " + account.firstName + " " + account.lastName);
		}
		this.account = account;
	}
	
	public void operation(String option)
	{
		if(option.equals(TopWindowView.STARTAGENT))
		{
			try
			{
				int AgentID = Integer.parseInt(((TopWindowView)getView()).topWindowIDEdit.getText());
				double Amount = Double.parseDouble( ((TopWindowView)getView()).amountInUSDEdit.getText());
				double ops = Double.parseDouble(((TopWindowView)getView()).opPerSecEdit.getText());
				int type = ((TopWindowView)getView()).option;
				window = ((TopWindowModel)getModel()).makeTopWindow(AgentID, Amount, ops, type, account);
				if(window != null)
				{
					((TopWindowView)getView()).dispose();
					setView(new NewTopWindow((TopWindowModel)getModel(), this, window, account));
					((JFrameView)getView()).setVisible(true);
					if(type == 1)
					{
						((NewTopWindow)getView()).setTitle("Withdraw agent: " + window.ID + " for " + account.firstName + " " + account.lastName);
					}
					else
					{
						((NewTopWindow)getView()).setTitle("Deposit agent: " + window.ID + " for " + account.firstName + " " + account.lastName);
					}
				}
				else
				{
					((TopWindowView)getView()).warning.showMessageDialog((TopWindowView)getView(),
						    "Agent already exists!",
						    "Agent exists",
						    JOptionPane.WARNING_MESSAGE);
				}
			}
			catch(Exception name)
			{
				((TopWindowView)getView()).warning.showMessageDialog((TopWindowView)getView(),
					    "Unusable information was entered. Try again.",
					    "Incorrect Information",
					    JOptionPane.WARNING_MESSAGE);
			}	
		}
		
		else if(option.equals(NewTopWindow.STOPAGENT))
		{
			((TopWindowModel)getModel()).stopWindow(this.window);
			((NewTopWindow)getView()).dismissAgent.setEnabled(true);
			((NewTopWindow)getView()).running.setText("Stopped");
		}
		else if(option.equals(NewTopWindow.DISMISSAGENT))
		{
			((NewTopWindow)getView()).dispose();
		}
	}
}
