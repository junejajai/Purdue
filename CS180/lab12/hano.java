import java.io.*;

public class hano
{
    //static int count = 1;
    public static int power(int a,int b)
    {  
        if(b==0)
        {
            return 1;
        }
        return a*power(a,b-1);
    }
    
    public static int fileCount(File f)
    {
        
        int count = 0;
        for (File file : f.listFiles()) {
            if (file.isFile()) {
                count++;
            }
            if (file.isDirectory()) {
                count += fileCount(file);
            }
        }
        return count;
    }
    
    
    public static void hanoi(int n,char src,char dest,char aux)
    {
        if(n == 0)
            return;
        if(n == 1)
        {
            System.out.printf("move %d from %s to %s \n ",n,src,dest);
        }
        else
        {
             hanoi(n-1,src,dest,aux);
             hanoi(1,src,aux,dest);
             hanoi(n-1,aux,src,dest);
        }
    }
    
    public static int mysterySeries(int i,int j)
    {
        if(i<0 || j<0 || i<j)
            return 0;
        if(j == 0||i == j)
        {
            return 1;
        }
        else
        {
            return mysterySeries(i-1, j-1) + mysterySeries(i-1, j);
        }
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    public static void main(String[] args)
    {
        //System.out.println(power(2,5));
        File f = new File("/homes/juneja0/cs180/lab12/test");
        System.out.println(fileCount(f));
        //hanoi(4,'A','B','C');
       // System.out.println(mysterySeries(6,2));
    }
    
}