package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import controller.TopWindowController;
import model.Account;
import model.TopWindow;
import model.TopWindowModel;
import model.ModelEvent;

/**
 * 
 * @author Trevor Underwood
 *	View class for the agent window.
 */
public class NewTopWindow extends JFrameView
{
	TopWindow current;
	public static final String STOPAGENT = "Stop Agent";
	public static final String DISMISSAGENT = "Dismiss Agent"; 

	public JTextField running = new JTextField(10);
	private JTextField amountInUSD = new JTextField(20);
	private JTextField opPerSec = new JTextField(20);
	private JTextField moneyTransferred = new JTextField(20);
	private JTextField totalOperations = new JTextField(20);
	public JOptionPane warning = new JOptionPane();
	public JButton dismissAgent;

	public NewTopWindow(TopWindowModel model, TopWindowController controller, TopWindow window, Account account)
	{
		super(model, controller);

		current = window;

		JPanel agentPanel = new JPanel();
		JPanel statePanel = new JPanel();

		//Show running status
		if(window.going == true)
		{
			running.setText("Running");
		}
		else
		{
			running.setText("Blocked");
		}
		amountInUSD.setText("Amount in $: " + window.amount);
		String moneyTrans = Double.toString(window.totalMoneyTransfered);
		String totalOps = Integer.toString(window.numOfOperationsFinished);
		moneyTransferred.setText("Total money transferred: " + moneyTrans);
		totalOperations.setText("Total operations completed: " + totalOps);
		opPerSec.setText("Operations per second: " + window.operations);

		//Make everything uneditable
		running.setEditable(false);
		amountInUSD.setEditable(false);
		opPerSec.setEditable(false);
		moneyTransferred.setEditable(false);
		totalOperations.setEditable(false);

		agentPanel.add(amountInUSD);
		agentPanel.add(opPerSec);

		statePanel.add(moneyTransferred);
		statePanel.add(totalOperations);

		this.getContentPane().add(agentPanel, BorderLayout.NORTH);
		this.getContentPane().add(statePanel, BorderLayout.WEST);
		this.getContentPane().add(running, BorderLayout.EAST);

		JPanel buttonPanel = new JPanel();
		Handler handler = new Handler();
		dismissAgent = new JButton(DISMISSAGENT);
		dismissAgent.addActionListener(handler);
		dismissAgent.setEnabled(false);
		JButton stopAgent = new JButton(STOPAGENT);
		stopAgent.addActionListener(handler);

		buttonPanel.setLayout(new GridLayout(4, 4, 5, 5));
		this.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
		buttonPanel.add(stopAgent, null);
		buttonPanel.add(dismissAgent, null);
		pack();
	}
	public void modelChanged(ModelEvent event)
	{
		if(current.going)
		{
			running.setText("Running");
		}
		else
		{
			running.setText("Blocked");
		}
		moneyTransferred.setText(String.valueOf(current.totalMoneyTransfered));
		totalOperations.setText(String.valueOf(current.numOfOperationsFinished));
	}
	class Handler implements ActionListener
	{
		// Event handling is handled locally
		public void actionPerformed(ActionEvent e)
		{
			((TopWindowController)getController()).operation(e.getActionCommand()); 
		}
	}
}
