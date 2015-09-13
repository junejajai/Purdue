    public class B implements Runnable {
        public void run() {
            while (true) {
                System.out.println("B");
                Thread.yield();
            }
        }
        public static void main(String[] args) {
            Runnable r = new B();
            Thread t1 = new Thread(r);
            t1.start();
        }
    }

