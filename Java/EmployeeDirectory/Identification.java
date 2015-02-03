package homework3;

import java.util.Random;
import java.util.Scanner;

public class Identification {

	Scanner input = new Scanner(System.in);
	
	public Identification()
	{
		setID();
	}
	public Identification(Identification ID)
	{
		IDnum = ID.getID();
	}
	public Identification(int inputID)
	{
		while(inputID<0 || inputID>29)
		{
			System.out.print("\nID number must be between 0 and 29. Enter an ID number: \n");
			inputID = input.nextInt();
		}
		
		IDnum = inputID;
	}
	public void setID()
	{	
		Random randomNumbers = new Random();
		int randomNum = randomNumbers.nextInt(30);
		int ID = randomNum;

		//eventually put in a check to make sure ID isn't already taken
		if(ID >= 0 && ID < 30)
		{
			IDnum = ID;
		}
	}
	
	public void setID(int ID)
	{
		if(ID< 0 || ID>29)
		{
			System.out.print("\nInvalid ID number inputted. ID number not set.\n");
		}
		else
		{
			IDnum = ID;
		}
	}
	public int getID()
	{
		return IDnum;
	}
	
	private int IDnum;
}
