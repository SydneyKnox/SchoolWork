package homework3;

public class Employee {
	
	public Employee(String name)
	{
		setName(name);
		
		setSales(0);
		
		SalesNumbers(0);
		
	}
	
	public Employee()
	{
		setName("unknown");
				
		setSales(0);
		
		SalesNumbers(0);
	}
	
	public void setName(String name)
	{
		if(name.length() > 20)
		{
			name = name.substring(0,20);
		}
		
		employee_name = name;
	}

	public void setSales(double dollars)
	{
		if(dollars >=0)
		{
			sales_dollars = sales_dollars + dollars;
		}
	}
	
	public void SalesNumbers(int num)
	{	
		if(num == 0)//if instantiting object
		{
			number_of_sales = 0;
		}
		else
		{
			number_of_sales += num;
		}
	}

	public String getName()
	{
		return employee_name;
	}
		
	public double getDollars()
	{
		return sales_dollars;
	}
	
	public int getNums()
	{
		return number_of_sales;
	}
	
	public void printInfo()
	{
		System.out.printf("\nEmployee %s:\n************************************\n"
				+ "Number of Sales: %d\nTotal Sales ($): %,.2f\n\n\n", getName(), getNums(), getDollars());
	}

	private String employee_name;
	private double sales_dollars;
	private int number_of_sales;
	
}
