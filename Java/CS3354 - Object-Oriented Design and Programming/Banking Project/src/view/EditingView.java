package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import controller.BalanceController;
import model.Account;
import model.TopWindowModel;
import model.ModelEvent;

public class EditingView extends JFrameView
{
	public static final String DEPOSIT = "Deposit";
	public static final String WITHDRAW = "Withdraw";  
	public static final String EXIT = "Exit";

	private JTextField available = new JTextField(10); 
	public JTextField amount = new JTextField(10);
	public JTextField currentFunds = new JTextField(10);
	public Account account;

	private JPanel availableFunds = new JPanel();
	public JOptionPane warning = new JOptionPane();

	public EditingView(TopWindowModel model, BalanceController controller, Account account, int currency)
	{
		super(model,controller);
		this.account = account;
		availableFunds.setLayout(new GridLayout(4, 4, 5, 5));
		available.setText("Available Funds");
		available.setEditable(false);
		currentFunds.setEditable(false);
		amount.setText("0");
		availableFunds.add(available, BorderLayout.WEST);
		availableFunds.add(currentFunds, BorderLayout.WEST);
		this.getContentPane().add(availableFunds, BorderLayout.NORTH); 
		this.getContentPane().add(amount, BorderLayout.CENTER);
		JPanel buttonPanel = new JPanel();
		Handler handler = new Handler();

		JButton deposit = new JButton(DEPOSIT);
		JButton withdraw = new JButton(WITHDRAW);
		JButton exit = new JButton(EXIT);

		deposit.addActionListener(handler);
		withdraw.addActionListener(handler);
		exit.addActionListener(handler);

		buttonPanel.setLayout(new GridLayout(4, 4, 5, 5));
		this.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
		buttonPanel.add(deposit, null);
		buttonPanel.add(withdraw, null);
		buttonPanel.add(exit, null);
		pack();
	}

	public void modelChanged(ModelEvent event)
	{
		String msg = "";
		if(account.ID == event.getAccount().ID)
		{
			if(((BalanceController)getController()).currency == 0)// Dollar
			{
				msg = event.getAccount().funds + "";
			}
			else if (((BalanceController)getController()).currency == 1) // Euro
			{
				msg = (event.getAccount().funds * 0.72) + "";
			}
			else if (((BalanceController)getController()).currency == 2) // Yen
			{
				msg = (event.getAccount().funds * 94.1) + "";
			}
			currentFunds.setText(msg);
		}
	}

	class Handler implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			((BalanceController)getController()).operation(e.getActionCommand()); 
		}
	}
}
