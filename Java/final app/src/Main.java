public class Main {
    public static void main(String[] args) {
        /*MyThread obj = new MyThread();
        Thread thread = new Thread(obj);
        thread.start();*/

        MyGuiThread gui_thread = new MyGuiThread();
        gui_thread.start();

    }
}
