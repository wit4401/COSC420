// Will Townsned
//
// A second threading example adding numbers up to n with 5 threads
// a little more complex than threadingEx1.java
import  java.util.Scanner;

class additionThread implements Runnable{
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
        try{
            for(int i=start;start<=end;i++){
                sum+=i;
                Thread.sleep(50);
            }
        }catch(InterruptedException e){
            System.out.println("Thread " + tname + " Interrupted");
        }
    }

    public void start(){
        System.out.println("Starting Thread " + tname);
        if (t==null){
            t = new Thread(this, tname);
            t.start();
        }
    }
}

public class threadingEx2 {
    public static void  main(String args[]){
        int finalSum = 0;
        int interval;
        Scanner obj = new Scanner(System.in);
        additionThread t1,t2,t3,t4,t5;

        System.out.print("Enter a number: ");
        int n = obj.nextInt();
        interval=n/5;
        if(n%5==0){
            t1 = new additionThread("01", 1, interval);
            t2 = new additionThread("02", interval+1, interval*2);
            t3 = new additionThread("03", (interval*2)+1, interval*3);
            t4 = new additionThread("04", (interval*3)+1, interval*4);
            t5 = new additionThread("05", (interval*4)+1, interval*5);
            t1.start();
            t2.start();
            t3.start();
            t4.start();
            t5.start();

            finalSum = t1.sum+t2.sum+t3.sum+t4.sum+t5.sum;
            System.out.println("Final Sum: " + finalSum);
        }
        else{
            
            finalSum = t1.sum+t2.sum+t3.sum+t4.sum+t5.sum;
            System.out.println("Final Sum: " + finalSum);
        }

        obj.close();
    }
}
