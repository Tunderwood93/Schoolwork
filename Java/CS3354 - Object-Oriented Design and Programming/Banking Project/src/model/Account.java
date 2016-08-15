package model;

/**
 * 
 * @author Trevor Underwood
 *	Account class for simplifying storage of the information in the input file.
 */
public class Account
{
	public int ID;
	public String firstName;
	public String lastName;
	public String middleInitial;
	public double funds;
	
	public Account(int ID, String firstName, String lastName, String middleInitial, double funds)
	{
		this.ID = ID;
		this.firstName = firstName;
		this.lastName = lastName;
		this.middleInitial = middleInitial;
		this.funds = funds;
	}
}
