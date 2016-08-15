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
import model.TopWindowModel;

import model.ModelEvent;
/**
 * 
 * @author Trevor Underwood
 *	Sets up the view for the created agents for the threads
 */
public class TopWindowView extends JFrameView
{
	public static final String STARTAGENT = "Start Agent"; 

	public int option;
	
	private JTextField topWindowID = new JTextField();
	public JTextField topWindowIDEdit = new JTextField(10);
	private JTextField amountInUSD = new JTextField();
	public JTextField amountInUSDEdit = new JTextField(10);
	private JTextField opPerSec= new JTextField(20);
	public JTextField opPerSecEdit= new JTextField(10);
	public JOptionPane warning = new JOptionPane();

	public TopWindowView(TopWindowModel model, TopWindowController controller, int option, Account account)
	{
		super(model, controller);
		this.option = option;
		JPanel TopWindowPanel = new JPanel();
		JPanel amtPanel = new JPanel();
		JPanel opPanel = new JPanel();

		topWindowID.setText("Agent ID: ");
		amountInUSD.setText("Amount in $");
		opPerSec.setText("Operations per second");
		
		topWindowID.setEditable(false);
		amountInUSD.setEditable(false);
		opPerSec.setEditable(false);

		TopWindowPanel.add(topWindowID);
		TopWindowPanel.add(topWindowIDEdit);
		amtPanel.add(amountInUSD);
		amtPanel.add(amountInUSDEdit);
		opPanel.add(opPerSec);
		opPanel.add(opPerSecEdit);
		
		this.getContentPane().add(TopWindowPanel, BorderLayout.NORTH);
		this.getContentPane().add(amtPanel, BorderLayout.WEST);
		this.getContentPane().add(opPanel, BorderLayout.EAST);

		JPanel buttonPanel = new JPanel();
		Handler handler = new Handler();
		JButton startTopWindow = new JButton(STARTAGENT);
		startTopWindow.addActionListener(handler);
		
		buttonPanel.setLayout(new GridLayout(4, 4, 5, 5));
		this.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
		buttonPanel.add(startTopWindow, null);
		pack();
	}

	public void modelChanged(ModelEvent event)
	{
		String msg = event.getAccount() + "";
	}
	
	class Handler implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			((TopWindowController)getController()).operation(e.getActionCommand()); 
		} 
	}
}
