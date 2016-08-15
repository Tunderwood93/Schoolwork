package view;
import javax.swing.*; 

import controller.MainController;
import model.Account;
import model.TopWindowModel;
import model.ModelEvent;

import java.awt.*; 
import java.awt.event.*;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.DataInputStream;
import java.io.InputStreamReader;
import java.lang.String;


public class MainView extends JFrameView
{
	public static final String EDITINUSD = "Edit in USD"; 
	public static final String EDITINEURO = "Edit in Euro";
	public static final String EDITINYEN = "Edit in Yen";
	public static final String SAVE = "Save";
	public static final String EXIT = "Exit";
	public static final String CREATEWITHDRAW = "Create withdraw agent";
	public static final String CREATEDEPOSIT = "Create deposit agent";
	public String fileName;


	public ArrayList<Account> listOfAccounts = new ArrayList<Account>();

	public JComboBox dropDownOfAccounts; 

	/**
	 * @author Trevor Underwood
	 * The main view function is a template for the main view. It takes in a model, a controller, a type, and a list of accounts
	 * so that it can find the names of all accounts to add to the combobox.
	 */
	public MainView(TopWindowModel model, MainController controller, ArrayList<Account> listOfAcc, int currency, String fileName)
	{
		super(model,controller);
		this.fileName = fileName;
		String[] nameList = new String[listOfAcc.size()];
		for(int i = 0; i < listOfAcc.size(); i++)
		{
			String names = listOfAcc.get(i).firstName + " " + listOfAcc.get(i).lastName;
			nameList[i] = names;
		}
		dropDownOfAccounts = new JComboBox(nameList);
		dropDownOfAccounts.setSelectedIndex(0);
		controller.accountHolder = listOfAcc.get(0);
		this.getContentPane().add(dropDownOfAccounts, BorderLayout.NORTH);

		JPanel buttonPanel = new JPanel();
		Handler handler = new Handler(); 
		CBHandler cbhandler = new CBHandler();
		dropDownOfAccounts.addActionListener(cbhandler);

		JButton editUSD = new JButton(EDITINUSD);
		JButton editEURO = new JButton(EDITINEURO);
		JButton editYEN = new JButton(EDITINYEN);
		JButton save = new JButton(SAVE);
		JButton exit = new JButton(EXIT);
		JButton createWithdraw = new JButton(CREATEWITHDRAW);
		JButton createDeposit = new JButton(CREATEDEPOSIT);

		editUSD.addActionListener(handler);
		editEURO.addActionListener(handler);
		editYEN.addActionListener(handler);
		save.addActionListener(handler);
		exit.addActionListener(handler);
		createWithdraw.addActionListener(handler);
		createDeposit.addActionListener(handler);

		buttonPanel.setLayout(new GridLayout(4, 4, 5, 5));
		this.getContentPane().add(buttonPanel, BorderLayout.SOUTH);
		buttonPanel.add(editUSD, null);
		buttonPanel.add(editEURO, null);
		buttonPanel.add(editYEN, null);
		buttonPanel.add(save, null);
		buttonPanel.add(exit, null);
		buttonPanel.add(createWithdraw, null);
		buttonPanel.add(createDeposit, null);

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
			((MainController)getController()).operation(e.getActionCommand(), fileName); 
		} 
	}

	class CBHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			JComboBox cb = (JComboBox)e.getSource();
			int accToPass = (int)cb.getSelectedIndex();
			((MainController)getController()).setCurrentAccount(accToPass); 
		} 
	}

	public static void main(String [] args)
	{
		ArrayList<Account> AccountList = new ArrayList<Account>();
		String fileName = "";

		if(args.length > 0)
		{
			fileName = args[0];
		}

		try
		{
			// Reading in from the file and parsing with regular expressions
			FileInputStream fstream = new FileInputStream(fileName);
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String lineFromFile;
			while((lineFromFile = br.readLine()) != null)
			{
				String tokens[] = lineFromFile.split("\\|");
				int id = Integer.parseInt(tokens[0].replaceAll("[\\D]", ""));
				double funds = Double.parseDouble(tokens[2].replaceAll("[\\f]", ""));
				if(funds < 0)
				{
					throw new Exception("ID: " + id + " Has negative funds.\n");
				}
				String names = tokens[1];
				String allNames[] = names.replaceAll("(^\\s+|\\s+$)", "").split("\\s+");
				String firstname;
				String lastname;
				String middleInitial;

				if(allNames.length == 3)
				{
					firstname = allNames[1];
					lastname = allNames[0];
					middleInitial = allNames[2];
				}
				else
				{
					firstname = allNames[1];
					lastname = allNames[0];
					middleInitial = "";
				}
				Account account = new Account(id, firstname, lastname, middleInitial, funds);
				AccountList.add(account);
			}
			in.close();
		}
		catch (Exception e)
		{
			System.err.println("Error: " + e.getMessage());
		}
		new MainController(AccountList, fileName); }
}