package homework3;
import java.util.Scanner;

public class EmployeeBookTest {
	
	
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);
		EmployeeBook Directory = new EmployeeBook();
			//Directory.clearBook();
		int userInput = 0;
		
		while(userInput != 5)
		{
			System.out.print("\nMenu:\n------------------------------------\n");
			System.out.print("1: Add Employee\n2: Delete Employee\n3: Edit Employee Information\n4: Print Employee List\n5: Quit\n");
			
			userInput = input.nextInt();
			
			while(userInput < 1 || userInput > 5)
			{
				System.out.print("\nInvalid input. Please input a 1-5: \n");
				userInput = input.nextInt();
			}//end blocking while loop for menu choice
			
			//If they want to add an employee to the gradebook
			if(userInput == 1)
			{
				Directory.createNewEmployee();
			}
			if(userInput == 2)
			{
				Directory.deleteEmployee();
			}
			if(userInput == 3)
			{
				int inputID;
				System.out.print("\nEnter Employee's ID number: \n");
				inputID = input.nextInt();
				
				if(!Directory.containsEmployee(inputID))
				{
					System.out.print("Invalid ID number.");
				}
				else
				{
					int chosenEmployeeID = inputID;
					
					System.out.print("\n*************************************\n"
							+ "1: Change employee name\n2:Add Sale\n3:See employee information.\n");
					
					int userInput2 = input.nextInt();
					
					while(userInput2 < 1 || userInput2 > 3)
					{
						System.out.print("\nInvalid Input. Enter 1-3: \n");
						userInput2 = input.nextInt();
					}
					
						if(userInput2 == 1)
						{
							System.out.print("\nEnter new name: ");
							
							String newName = new String();
							
							newName = input.next();
							
							Directory.getEmployee(chosenEmployeeID).setName(newName);
						}
						if(userInput2 == 2)
						{
							System.out.print("\nEnter the amount (in dollars) of the sale: \n");
							double inputSale = input.nextDouble();
							
							Directory.getEmployee(chosenEmployeeID).setSales(inputSale);
							Directory.getEmployee(chosenEmployeeID).SalesNumbers(1);
							
							System.out.printf("\nNew number of Sales: %d\nNew Sales Amount: %,.2f", Directory.getEmployee(chosenEmployeeID).getNums(), Directory.getEmployee(chosenEmployeeID).getDollars());
	
						}
						if(userInput2 == 3)
						{
							Directory.getEmployee(chosenEmployeeID).printInfo();
						}
				}
				
				
			}
			if(userInput == 4)
			{
				Directory.viewAll();
			}
			if(userInput == 5)
			{
				System.out.print("\nExiting Directory now.\n");
			}
		}//end menu while loop. user has quit program
		input.close();//close Scanner
	}//end main

}//end class
