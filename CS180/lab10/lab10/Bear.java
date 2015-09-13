public class Bear extends Animal
{
    Bear(String status)
    {
        super(status);
    }
    
    @Override
    public void makeMove(SiteGrid sg)
    {
        
        try
        {
            if(site.getType() == SiteType.WINTERING && Math.random() < 0.3){
                die();
            }
            else{
                super.makeMove(sg);
            }
       
      /*
        if(site.getType().equals("WINTERING"))
        {
            if(Math.random() < 0.3)
            {
             die();
            status1 = "DEAD";
            }
        }
        if(status1.equals("ALIVE"))
        {
            super.makeMove(sg);
        }*/
        }
        catch(NullPointerException e)
        {
            super.makeMove(sg);
        }
        
        
    }
    
    
}