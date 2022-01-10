import javax.swing.*;
import java.awt.*;

public class MessagePanels {
    private JFrame frame;
    private JPanel panel;
    private JLabel label;
    private ImageIcon icon;
    private Font myFontText;


    public void errorMessage(String message){
        myFontText = new Font("Arial", Font.PLAIN, 15);
        icon = new ImageIcon("error.png");

        frame = new JFrame("Error");
        frame.setVisible(true);
        frame.setSize(300,100);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.setIconImage(icon.getImage());

        panel = new JPanel();
        panel.setLayout(new GridBagLayout());
        panel.setBackground(new Color(33, 33, 33));

        label = new JLabel(message);
        label.setFont(myFontText);
        label.setForeground(Color.white);

        panel.add(label);
        frame.add(panel);
    }
}
