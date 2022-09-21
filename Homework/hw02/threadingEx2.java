/* 
 * Will Townsned
 * 
 * A second threading example adding numbers up to n with 5 threads
 * a little more complex than threadingEx1.java
 * 
 * Unfinished Program
*/
import  java.util.Scanner;

class additionThread extends Thread{
    private String tname;
    private Thread t;
    private int start, end;
    public int sum;

    additionThread(String name, int intStart, int intEnd){
        tname = name;
        start = intStart;
        end = intEnd;
        System.out.println("Creating Thread " + tname);
    }

    public void run(){
        System.out.println("Running Thread " + tname);
        for(int i=start;i<=end;i++){
        	sum+=i;
        }
        
        System.out.println("Thread " + tname + " Exiting");
    }

    public void start(){
        System.out.println("Starting Thread " + tname);
        if (t==null){
            t = new Thread(this, tname);
            t.start();
            try{
                t.join();
            }catch(InterruptedException e){System.out.println("Failed to join Thread");}
        }
    }
}

public class threadingEx2 {
    public static void  main(String args[]){
        int finalSum = 0;
        Scanner obj = new Scanner(System.in);
        additionThread t1,t2,t3,t4,t5;

        System.out.print("Enter a number: ");
        int n = obj.nextInt();
        
        int interval=n/5;
        int remainder = n%5;
        
        if(remainder==0){
            t1 = new additionThread("01", 1, interval);
            t1.start();
            
            t2 = new additionThread("02", interval+1, interval*2);
            t2.start();
            
            t3 = new additionThread("03", (interval*2)+1, interval*3);
            t3.start();
            
            t4 = new additionThread("04", (interval*3)+1, interval*4);
            t4.start();
            
            t5 = new additionThread("05", (interval*4)+1, interval*5);
            t5.start();

            finalSum = t1.sum+t2.sum+t3.sum+t4.sum+t5.sum;
            System.out.println("Final Sum: " + finalSum);
        }
        else{
            //finalSum = t1.sum+t2.sum+t3.sum+t4.sum+t5.sum;
            //System.out.println("Final Sum: " + finalSum);
        }

        obj.close();
    }
}
