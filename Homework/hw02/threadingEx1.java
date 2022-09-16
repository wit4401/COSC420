// Homework 02
// Will Townsend
//
// 09-09-2022

class FactorialThread extends Thread {
  
  private Thread t;
  private String tname;
  
  FactorialThread(String name){
      tname = name;
      System.out.println("Creating " + tname);
  }

  public void run(){

      int val = 1;

      System.out.println("Running " + tname);
      try{
      for(int i = 1; i <= 5; i++){
        
        val *= i;
        System.out.println( tname + ":" + i + "! = " + val);
        Thread.sleep(1000);
      
      }
   } catch(InterruptedException e){
         System.out.println(tname + "Interrupted");
      }

      System.out.println(tname+" Exiting...");
  }

  public void start(){
      System.out.println("Starting " + tname);
      if(t==null){

         t = new Thread(this, tname);
         t.start();
      }
  }

}

public class threadingEx1 {
   public static void main(String args[]){

      FactorialThread ft1 = new FactorialThread("Thread1");
      ft1.start();

      FactorialThread ft2 = new FactorialThread("Thread2");
      ft2.start();
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

public class hw02 {

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

public class hw02 {

   public static void main(String args[]) {
      ThreadDemo T1 = new ThreadDemo( "Thread-1");
      T1.start();
      
      ThreadDemo T2 = new ThreadDemo( "Thread-2");
      T2.start();
   }   
}
*/