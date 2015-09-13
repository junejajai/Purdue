/**
 * CS180 - Lab 03 - Person
 *
 * (A brief description of the class)
 *
 * @author jaideep juneja <(juneja0@purdue.edu)>
 *
 * lab 03 (Your lab section)
 *
 * 09/19/2014(Today's date)
 */
public class Person
{
    private String id;
    int age;
    private int ldl;
    private int hdl;
    private int other;
    public Person(String id,int age,int ldl,int hdl,int other)
    {
        this.id = id;
        this.age = age;
        this.ldl = ldl;
        this.hdl = hdl;
        this.other = other;
    }
    public boolean isAdult()
    {
        if(this.age>=18)
        {
            return true;
        }
        
        return false;
       
    }
    public int getTotalCholesterol()
    {
        int sum = ldl + hdl + other;
        return sum;
    }
    public boolean hasGoodTotalCholesterol()
    {
        int healthy_level;
        if(this.isAdult())
        {
            healthy_level = 200;
        }
        else
        {
         healthy_level = 170;   
        }
        if(this.getTotalCholesterol()<=healthy_level)
        {
            return true;
        }
        else
        {
            return false;
        }
        }
        
        public boolean hasGoodLDL()
        {
            int healthy_level;
        if(this.isAdult())
        {
            healthy_level = 130;
        }
        else
        {
         healthy_level = 110;  
        }
        if(this.ldl<=healthy_level)
        {
            return true;
        }
        else
        {
            return false;
        }
        }
        public boolean hasGoodHDL()
        {
            int healthy_level=40;
       
        if(this.hdl>=healthy_level)
        {
            return true;
        }
        else
        {
            return false;
        }
        }
        public void printReport() {
    System.out.println(this.id + "'s Report");
    System.out.println("Age: " + this.age + " (" + (isAdult() ? "Adult" : "Child") + ")");
    System.out.println("Total Cholesterol: " + this.getTotalCholesterol() + 
        " ("+(hasGoodTotalCholesterol()?"Good":"Bad")+")");
    System.out.println("LDL: " + this.ldl + " (" + (hasGoodLDL() ? "Good" : "Bad") + ")");
    System.out.println("HDL: " + this.hdl + " (" + (hasGoodHDL() ? "Good" : "Bad") + ")");
}
            
        
    }