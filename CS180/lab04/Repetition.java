/**
 * CS 180 - Lab 04 - Repetition
 * 
 Repetition stuff
 * 
 * juneja0@purdue.edu
 * 
 * @lab (Your lab section)
 *
 * 09/26/2014
 */
import java.util.Scanner;
public class Repetition
{
    public static void even()
    {
        for(int i=0;i<=100;i++)
        {
            if(i % 2 == 0)
            {
                System.out.print( i + " ");
            }
        }
    }
    public static void powers() 
    {
        int exp = 0;
        while((Math.pow(2,exp))<1000)
        {
            System.out.print( Math.pow(2,exp) + " ");
            exp++;
            
            
        }
    }
    public static void alphabet() 
    {
        for(char i = 'a'; i<='z';i++)
        {
            System.out.print( i + " ");
        }
    }
    
    public static void vertical ( String s)
    {
        for(int i=0;i<s.length();i++)
        {
            System.out.println(s.charAt(i));
        }
    }
    public static void testResults() 
    {
        Scanner sc = new Scanner(System.in);
        int max =Integer.MIN_VALUE;
        int min =Integer.MAX_VALUE;
        double average = 0;
        int sum = 0;
        int count = 0;
        int t;
        System.out.println("Enter grade");
        //t=sc.nextInt();
        while(sc.hasNextInt())
        {
            t = sc.nextInt();
            if(t>max)
            {
                max = t;
            }
            if(t<min)
            {
                min = t; 
            }
            count++;
            sum = sum + t;
            System.out.println("Enter  next grade or enter non integer to end : ");
            
        }
        average = sum/count;
        
        System.out.println("=====-----=====-----=====-----=====----====----====----====----====");
        
        System.out.println("=            Test Results         =");
        
        System.out.printf("= Average:%21.1f = \n",average);   
        
        System.out.printf("= Lowest:%21d = \n",min);    
        
        System.out.printf("= Highest:%21d = \n",max);  
        System.out.println("=====-----=====-----=====-----=====----====----====----====----====");
        
    }
    
    
    
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        even();
        System.out.println();
        powers();
        System.out.println();
        alphabet();
        System.out.println(); 
                System.out.println("Enter string");
                String s = sc.nextLine();
        vertical(s);
                System.out.println(); 
                testResults();
        
        
    }
}
