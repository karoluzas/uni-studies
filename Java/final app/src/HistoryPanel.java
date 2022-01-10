import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;

public class HistoryPanel{
    Font historyFont;
    JFrame frame;
    JTextArea textArea;
    JScrollPane scrollPane;
    ImageIcon icon;

    public HistoryPanel(ArrayList<String> numbersList, Color backgroundColor, Color textAreaColor, Font textColor){
        frame = new JFrame("History");
        textArea = new JTextArea(14,20);
        scrollPane = new JScrollPane(textArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        historyFont = new Font("Arial", Font.PLAIN, 22);
        icon = new ImageIcon("history.png");

        scrollPane.setBorder(null);
        scrollPane.getVerticalScrollBar().setBackground(textAreaColor);

        textArea.setBackground(textAreaColor);
        textArea.setLayout(new GridBagLayout());
        textArea.setFont(historyFont);
        textArea.setEditable(false);

        for(Iterator<String> it = numbersList.iterator(); it.hasNext(); ){
            textArea.append(it.next() + "\n");
        }

        frame.setIconImage(icon.getImage());
        frame.setResizable(false);
        frame.getContentPane().setBackground(backgroundColor);
        frame.setLayout(new FlowLayout());
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.add(scrollPane);
        frame.setSize(400,412);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

    }
}
