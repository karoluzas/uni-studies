import javax.swing.*;
import java.awt.*;

public class EmptyStringException extends Exception{
    private MessagePanels popup;

    public EmptyStringException(){
        System.out.println("Empty string");
    }

    public EmptyStringException(String message){
        popup = new MessagePanels();
        popup.errorMessage(message);
    }
}