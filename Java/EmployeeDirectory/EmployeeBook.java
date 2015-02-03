package homework3;
import java.util.Map;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;


public class EmployeeBook {

	Scanner input = new Scanner(System.in);
	public EmployeeBook()
	{	
			Map<Identification, Employee> myMap = new HashMap<Identification, Employee>();
			
			employeeMap = myMap;
			
			System.out.print("\nEmployee Book initialized.\n");
	}
	public boolean containsEmployee(int IDnumber)
	{
		boolean found = false;
		
		if(employeeMap.isEmpty())
		{
			return found;
		}
		
		Set<Identification> IDnumbers = employeeMap.keySet();
				
		for(Identification key : IDnumbers)
		{
			if(key.getID() == IDnumber)
			{
				found = true;
			}
		}
		
		return found;
	}

	public void clearBook()
	{
		if(employeeMap.isEmpty()== false)
		{
			employeeMap.clear();
		}
	}
	public void createNewEmployee()
	{
		String name = new String();
		
		System.out.print("\nPlease Enter the new Employee's last name: \n");
		name = input.next();
		
		Employee newEmployee = new Employee(name);
		//Employee testEmployee = new Employee("test");
		
		Identification IDnum = new Identification();
		
		boolean notfound = false;
		
		while(!notfound)
		{
			if(employeeMap.containsKey(IDnum))
			{
				IDnum.setID();
			}
			else
			{
				notfound = true;//iterate through map and see if the ID number is always there
			}
		}
		
		//insert into Map
		employeeMap.put(IDnum , newEmployee);
		
		if(employeeMap.containsKey(IDnum))
		{
			System.out.print("\nEmployee Added successfully.\n");
		}
		else
		{
			System.out.print("\nError: Employee Addition unsuccesful.\n");
		}
	}
	public void deleteEmployee()
	{	//Make it so it uses the string name instead of ID. or make sure ID number is readily available
		//Find it in Map
		int IDinput;
		boolean removed = false;
		
		System.out.print("\nEnter the Employee ID number: \n");
		IDinput = input.nextInt();
		
		while(IDinput < 0 || IDinput >= 30)
		{
			System.out.print("\nPlease enter an ID between 0 and 29.\n");
			IDinput = input.nextInt();
		}
		
		if(employeeMap.isEmpty())
		{
			System.out.print("\nThere are currently no employees.\n");
		}
		
		Set<Identification> IDnumbers = employeeMap.keySet();
		
		Identification taggedForRemoval = new Identification();
		
		for(Identification key : IDnumbers)
		{
			if(key.getID() == IDinput)
			{
				taggedForRemoval = key;
			}
		}
		
		employeeMap.remove(taggedForRemoval);
		removed = true;
		System.out.printf("\nEmployee %d removed.\n", IDinput);
		
		if(removed == false)
		{
			System.out.printf("\nDeletion Unsuccessful. Employee %d not found.\n", IDinput);
		}

	}
	public void viewAll()
	{
		//Iterate through Map, printing stuff as I go
		if(employeeMap.isEmpty())
		{
			System.out.print("\nThere are currently no employees.\n");
		}
		
		//Iterator<Entry<Identification, Employee>> entries = employeeMap.entrySet().iterator();
		
		/*while (entries.hasNext()) {
		  Entry<Identification, Employee> thisEntry = (Entry<Identification, Employee>) entries.next();
		  Employee value = thisEntry.getValue();
		  
		  value.printInfo();
		  entries.next();*/
		
		 //}
		
		Set<Identification> IDnumbers = employeeMap.keySet();
		
		//TreeSet<Identification> sortedIDnumbers = new TreeSet< Identification >(keys);
		
		for(Identification key : IDnumbers)
		{
			System.out.printf("ID: %d\t", key.getID());
			employeeMap.get(key).printInfo();
		}
		
		
	}
	public Employee getEmployee(int IDnumber)
	{	
		boolean found = false;
		
		if(employeeMap.isEmpty())
		{
			System.out.print("\nThere are currently no employees.\n");
		}
		
		Set<Identification> IDnumbers = employeeMap.keySet();
		
		Identification foundID = new Identification();
		
		for(Identification key : IDnumbers)
		{
			if(key.getID() == IDnumber)
			{	
				foundID = key;
				found = true;
			}
		}
		
		if(found == false)
		{
			System.out.print("\nError: Employee Not found\n");
		}
		
		return employeeMap.get(foundID);
		
	}
	private Map<Identification, Employee> employeeMap;
	
}
