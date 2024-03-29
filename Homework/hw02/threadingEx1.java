// Homework 02
// Will Townsend
//
// Simple program initializes two threads to 
// adds the numbers 1 - 10 together and prints a
// final sum
//creation of the class AdditionThread which extends the thread class
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
  public class threadingEx1 {
     // main program to be run
     public static void main(String args[]){
        //create first AdditionThread object
        AdditionThread ft1 = new AdditionThread("Thread1",1,5);
        ft1.start();
        //create second AdditionThread object
        AdditionThread ft2 = new AdditionThread("Thread2",6,10);
        ft2.start();
        System.out.println("\nFinal Sum: " + (ft1.result+ft2.result));
    }
  }
