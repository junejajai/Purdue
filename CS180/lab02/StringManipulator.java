/**
 * CS 180 - Lab 02 - StringManipulator
 * 
 * to create email.com
 * 
 * @author Jaideep Singh Juneja<(juneja0@purdue.edu)>
 * 
 * @lab (Your lab section)
 *
 * @date 09/12/2014(Today's date)
 */

import java.util.Scanner;
public class StringManipulator {
    public String makeUserName(String fullName)
    {
        int b=fullName.indexOf(" ");
        String a=fullName.substring(0,1);
        String c=fullName.substring((b+1)); 
        String d= a+c;
        d=d.toLowerCase();
        return d;
    }
    public String makeEmail(String name,String domain)
    { 
        domain.toLowerCase();
        String e= "@"; 
        String email= name+e+domain;
        email.toLowerCase();
        return email;
        
    }
    
    public static void main(String[] args)
    {
        Scanner sc= new Scanner(System.in); 
        System.out.println("Enter firstname and lastname separated by space: "); 
        String nam = sc.nextLine();
        System.out.println("Enter domain name: ");
        String dom= sc.nextLine();
        StringManipulator s= new StringManipulator();
        nam=s.makeUserName(nam);
                System.out.println("Username is: " + nam);
        String email= s.makeEmail(nam,dom);
        System.out.println("Email Id is: " + email);
    }
    
}