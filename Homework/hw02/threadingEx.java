// Homework 02
// Will Townsend
//
// Simple program initializes two threads to 
// adds the numbers 1 - 10 together and prints a
// final sum
//creation of the class FactorialThread which extends the thread class
class AdditionThread extends Thread {
  
    private Thread t; // define our thread t in our class
    private String tname; // variable for the name of our String
    private int s,e;
    public int result=0;
    
    // Constructor for our object
    // assigns name for thread
    AdditionThread(String name,int start,int end){
        tname = name;
        s=start;
        e=end;
        System.out.println("Creating " + tname);
    }
    //actual function of each thread
    public void run(){
        System.out.println("Running " + tname);
        try{
           for(int i = s; i <= e; i++){
              result += i;
              Thread.sleep(50);
           }
     } catch(InterruptedException e){ //catches interruption of the thread run()
           System.out.println(tname + "Interrupted");
        }
        System.out.println(tname+" Exiting...");
    }
    public void start(){
        System.out.println("Starting " + tname);
        //creates the actual thread, t
        if(t==null){
           t = new Thread(this, tname);// initializes the thread t of the object
           t.start(); //starts the function of the thread defined by run()
           try{
              t.join();//joins thread to sychronize them
           }catch(Exception e){System.out.println("Failed to join thread");}
        }
    }
  }
  // main class file
  public class threadingEx {
     // main program to be run
     public static void main(String args[]){
        //create first FactorialThread object
        AdditionThread ft1 = new AdditionThread("Thread1",1,5);
        ft1.start();
        //create second FactorialThread object
        AdditionThread ft2 = new AdditionThread("Thread2",6,10);
        ft2.start();
        System.out.println("\nFinal Sum: " + (ft1.result+ft2.result));
    }
  }
  /* 
  // Example 1 from tutorials point:
  class RunnableDemo implements Runnable {
     private Thread t;
     private String threadName;
     
     RunnableDemo( String name) {
        threadName = name;
        System.out.println("Creating " +  threadName );
     }
     
     public void run() {
        System.out.println("Running " +  threadName );
        try {
           for(int i = 4; i > 0; i--) {
              System.out.println("Thread: " + threadName + ", " + i);
              // Let the thread sleep for a while.
              Thread.sleep(50);
           }
        } catch (InterruptedException e) {
           System.out.println("Thread " +  threadName + " interrupted.");
        }
        System.out.println("Thread " +  threadName + " exiting.");
     }
     
     public void start () {
        System.out.println("Starting " +  threadName );
        if (t == null) {
           t = new Thread (this, threadName);
           t.start ();
        }
     }
  }
  public class threadingEx {
     public static void main(String args[]) {
        RunnableDemo R1 = new RunnableDemo( "Thread-1");
        R1.start();
        
        RunnableDemo R2 = new RunnableDemo( "Thread-2");
        R2.start();
     }   
  }
  //Example 2 from tutorialspoint:
  class ThreadDemo extends Thread {
     private Thread t;
     private String threadName;
     
     ThreadDemo( String name) {
        threadName = name;
        System.out.println("Creating " +  threadName );
     }
     
     public void run() {
        System.out.println("Running " +  threadName );
        try {
           for(int i = 4; i > 0; i--) {
              System.out.println("Thread: " + threadName + ", " + i);
              // Let the thread sleep for a while.
              Thread.sleep(50);
           }
        } catch (InterruptedException e) {
           System.out.println("Thread " +  threadName + " interrupted.");
        }
        System.out.println("Thread " +  threadName + " exiting.");
     }
     
     public void start () {
        System.out.println("Starting " +  threadName );
        if (t == null) {
           t = new Thread (this, threadName);
           t.start();
        }
     }
  }
  public class threadingEx {
     public static void main(String args[]) {
        ThreadDemo T1 = new ThreadDemo( "Thread-1");
        T1.start();
        
        ThreadDemo T2 = new ThreadDemo( "Thread-2");
        T2.start();
     }   
  }
  */
