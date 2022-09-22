// Homework 02
// Will Townsend
//
// A modified version of hw 02 where we are using 2
// thread to find the summation of all numbers up to
// 50 using 2 threads and 5 threads to compare their
// times and thus their efficiency and speed comparitevly

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
      //System.out.println("Creating " + tname);
  }

  //actual function of each thread
  public void run(){
      //System.out.println("Running " + tname);
      try{
         for(int i = s; i <= e; i++){
            result += i;
            Thread.sleep(0);
         }
   } catch(InterruptedException e){ //catches interruption of the thread run()
         System.out.println(tname + "Interrupted");
      }
      //System.out.println(tname+" Exiting...");
  }

  public void start(){
      //System.out.println("Starting " + tname);
      //creates the actual thread, t
      if(t==null){
         t = new Thread(this, tname);// initializes the thread t of the object
         t.start(); //starts the function of the thread defined by run()
      }
      try{
         t.join();//joins thread to wait for the other thread to stop
      }catch(Exception e){System.out.println("Failed to join thread");}
  }
}

// main class file
public class threadingEx {
   // main program to be run
   public static void main(String args[]){
      
      /*
       * Testing the time with two threads
      */
      long begin = System.nanoTime();
      //create first FactorialThread object
      AdditionThread ft1 = new AdditionThread("Thread1",1,25);
      ft1.start();

      //create second AdditionThread object
      AdditionThread ft2 = new AdditionThread("Thread2",26,50);
      ft2.start();

      System.out.println("\nFinal Sum: " + (ft1.result+ft2.result));
      long end = System.nanoTime();
      System.out.println("2 Thread Runtime: " + ((end-begin)*0.000000001) + " sec");

      /*
       * Testing the time with five threads
       */
      begin = System.nanoTime();
      //create first AdditionThread object
      ft1 = new AdditionThread("Thread1",1,10);
      ft1.start();

      //create second AdditionThread object
      ft2 = new AdditionThread("Thread2",11,20);
      ft2.start();

      //create first AdditionThread object
      AdditionThread ft3 = new AdditionThread("Thread3",21,30);
      ft3.start();

      //create second AdditionThread object
      AdditionThread ft4 = new AdditionThread("Thread4",31,40);
      ft4.start();

      //create second AdditionThread object
      AdditionThread ft5 = new AdditionThread("Thread5",41,50);
      ft5.start();

      System.out.println("\nFinal Sum: " + (ft1.result+ft2.result+ft3.result+ft4.result+ft5.result));
      end = System.nanoTime();
      System.out.println("5 Thread Runtime: " + ((end-begin)*0.000000001) + " sec");
  }
}