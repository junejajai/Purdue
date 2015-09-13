    import java.util.Scanner;
    class Nirvana extends Thread {
        public boolean enlightenment = false;
        public void run() {
            meditate();
        }
        
        
     public synchronized void meditate() {
         try{
            while (!enlightenment) {

                System.out.println("Om...");
                 wait();
            }
        }catch(InterruptedException e)
        {
            System.out.println("You will not obtain Nirvana");
        }
     }
       public  synchronized void enlighten () {

            enlightenment = true;
            notify();
            
        }
        public static void main(String[] args) throws InterruptedException {
            Nirvana t = new Nirvana();
            t.start();
            Scanner s = new Scanner(System.in);
            s.nextLine();
            t.enlighten();
            t.join();
        }
    }

