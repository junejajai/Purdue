/**
 * CS 180 - Lab 08 - CollegeFeeCalculator
 * 
 * (Brief description of the class file)
 * 
 * @author (Jaideep juneja) <(juneja0@purdue.edu)>
 * 
 * @lab 803 (Your lab section)
 *
 * 7/11/2014 (Today's date)
 */

import javax.swing.JOptionPane;

public class CollegeFeeCalculator
{
    
    public static void main(String[] args)
    {
      int c = 0;
      while(c == 0)
    {
        int result[] = new int[10];
        String x[] = new String[10];
        JOptionPane.showMessageDialog (null, "Welcome to CollegeFeeCalculator!", "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
        
        
        x[0] = JOptionPane.showInputDialog(null,"Please Enter Your Name and then press ok","Enter Name",JOptionPane.QUESTION_MESSAGE);
        
        String[] selections = { "Part Time", "Full Time",};
        result[0]=JOptionPane.showOptionDialog(null,"Please Select Your Enrollment","Enrollment",JOptionPane.PLAIN_MESSAGE,JOptionPane.QUESTION_MESSAGE,null,selections,selections[0]);
        
        
        x[1]=JOptionPane.showInputDialog(null,"Please Enter Number Of Credit Hours,then press Ok","Credit Hours",JOptionPane.QUESTION_MESSAGE);
        int credit = Integer.parseInt(x[1]);
        
        while((result[0] == 0 && credit >= 8) || (result[0] == 1 && credit<8))
        {
            JOptionPane.showMessageDialog (null, "Please enter valid credit hours", "Invalid no. of credits", JOptionPane.ERROR_MESSAGE);   
            
            result[0]=JOptionPane.showOptionDialog(null,"Please Select Your Enrollment","Enrollment",JOptionPane.PLAIN_MESSAGE,JOptionPane.QUESTION_MESSAGE,null,selections,selections[0]);
            
            
            x[1]=JOptionPane.showInputDialog(null,"Please Enter Number Of Credit Hours,then press Ok","Credit Hours",JOptionPane.QUESTION_MESSAGE);
            credit = Integer.parseInt(x[1]);
            
        }
        
        String[] roptions = {"In-state","Out-of-state","International"};  
        x[2] = (String) JOptionPane.showInputDialog(null,"Please select the appropriate residency ","Residency",JOptionPane.QUESTION_MESSAGE,null, roptions,"In-state");
        
        String[] hoptions = {"ON-Campus","OFF-Campus"}; 
        x[3] = (String) JOptionPane.showInputDialog(null,"Please select your Housing ","Housing",JOptionPane.QUESTION_MESSAGE,null, hoptions,"On-Campus");
        
        
        if(x[3].equals("ON-Campus"))
        {
            String[] rhoptions = {"Earhart","Hillenbrand","Owen","Windsor"}; 
            x[4] = (String) JOptionPane.showInputDialog(null,"Please select Residence Hall ","Residence-Hall",JOptionPane.QUESTION_MESSAGE,null, rhoptions,"Earhart");
        }
        String y ="";
        int TotalFee = 0;
        int TuitionFee = 0;
        int HousingFee = 0;
        
        if(result[0] == 1)
        { 
            if(x[2].equals("In-state"))
            {
                TuitionFee = 4996 * credit;
            }
            if(x[2].equals("Out-of-state"))
            {
                TuitionFee = (9401 + 4996) * credit;
            }
            if(x[2].equals("International"))
            {
                TuitionFee = (4996 + 9401 + 1000) * credit;
            }
            
            y = "Full Time";
        }
        
        
        else if(result[0] == 0)
        { 
            if(x[2].equals("In-state"))
            {
                TuitionFee = 350 * credit;
            }
            if(x[2].equals("Out-of-state"))
            {
                TuitionFee = (350 + 600) * credit;
            }
            if(x[2].equals("International"))
            {
                TuitionFee = (350 + 600 + 70) * credit;
            }
            y = "Part Time";
        }
        
        if(x[3].equals("ON-Campus"))
        {
            if(x[4].equals("Earhart"))
            {
                HousingFee = 4745;
            }
            
            if(x[4].equals("Hillenbrand"))
            {
                HousingFee = 5307;
            }
            if(x[4].equals("Owen"))
            {
                HousingFee = 4130;
            }
            if(x[4].equals("Windsor"))
            {
                HousingFee = 4150;
            }
            
            
        }
        
        
        TotalFee = HousingFee + TuitionFee;
        String s = "";
        s = s + "Name : " + x[0] + "\n Credit Hours : " + x[1] + "\n Enrollment : " + y + "\n Residency : " + x[2] + "\n Tuition Fee : " + TuitionFee + "\n Housing Expense : " + HousingFee +"\n Total Sem. Fee : " + TotalFee; 
        
        JOptionPane.showMessageDialog (null, s, "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
        c = JOptionPane.showConfirmDialog(null,"Would you like to perform another Fee Calculation", "Are You Done",JOptionPane.YES_NO_OPTION);
        
    }
    
    
}
}