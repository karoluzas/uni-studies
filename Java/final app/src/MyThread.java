public class MyThread implements Runnable{
    int i;
    static volatile boolean stop = false;

    public void run() {
        while(!stop){
            System.out.println("Calculator has been running for " + i + " seconds");
            i++;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void timerStop(){
        stop = true;
    }


}
