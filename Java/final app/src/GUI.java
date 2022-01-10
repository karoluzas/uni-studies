import java.awt.event.*;
import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;


public class GUI implements ActionListener{
    JFrame frame;
    JPanel panel;
    JLabel name;
    public ArrayList<String> historyList;
    List<JButton> convertButtons = new ArrayList<JButton>();
    JButton[] numberButtons = new JButton[10];
    JButton hexButton, octalButton, binaryButton, anyButton;
    JButton clearButton, deleteButton, modButton;
    JButton addButton, subButton, mulButton, divButton, equalsButton;
    JButton historyButton, decimalButton, runtimeButton, stopButton;
    JTextField inputField, resultField;
    Font myFontNumbers, myFontText;
    ImageIcon icon;
    CheckOperation check_operation = new CheckOperation();
    MessagePanels popupMessage;

    Color buttonColor, textFieldColor, backgroundColor;
    double number1, number2, result;
    int con;
    char operator;
    boolean opera = false, conversion = false;

    Converter convert;
    ConverterFactoryDesign convertWithFactoryDesign;


    GUI(){



        historyList = new ArrayList<String>();

        // Fonts
        myFontNumbers = new Font("Arial", Font.PLAIN, 30);
        myFontText = new Font("Arial", Font.PLAIN, 18);

        // Color variables
        backgroundColor = new Color(33, 33, 33);
        textFieldColor = new Color(153, 153, 153);
        buttonColor = new Color(104, 104, 104);

        // Default settings for the frame of the GUI
        frame = new JFrame("Calculator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(510, 450);
        frame.setLocationRelativeTo(null);
        frame.getContentPane().setBackground(backgroundColor);
        frame.setLayout(null);
        frame.setResizable(false);
        icon = new ImageIcon("calculator.png");
        frame.setIconImage(icon.getImage());

        // Text field that will hold the input
        inputField = new JTextField();
        inputField.setBounds(20, 30, 450, 50);
        inputField.setFont(myFontNumbers);
        inputField.setEditable(true);
        inputField.setBackground(textFieldColor);
        inputField.setBorder(BorderFactory.createEmptyBorder());

        // Text field that will hold the result
        resultField = new JTextField();
        resultField.setBounds(20, 100, 450, 50);
        resultField.setFont(myFontNumbers);
        resultField.setEditable(false);
        resultField.setBackground(textFieldColor);
        resultField.setBorder(BorderFactory.createEmptyBorder());

        // Making of the buttons
        hexButton = new JButton("Hex");
        octalButton = new JButton("Octal");
        binaryButton = new JButton("Binary");
        anyButton = new JButton("Any");
        deleteButton = new JButton("Del");
        clearButton = new JButton("Clear");
        historyButton = new JButton("History");
        addButton = new JButton("+");
        subButton = new JButton("-");
        mulButton = new JButton("*");
        divButton = new JButton("/");
        equalsButton = new JButton("=");
        modButton = new JButton("%");
        decimalButton = new JButton(".");
        runtimeButton = new JButton("Time");
        stopButton = new JButton("Stop");

        // Adding the buttons into an array
        convertButtons.add(hexButton);
        convertButtons.add(octalButton);
        convertButtons.add(binaryButton);
        convertButtons.add(anyButton);
        convertButtons.add(deleteButton);
        convertButtons.add(clearButton);
        convertButtons.add(addButton);
        convertButtons.add(subButton);
        convertButtons.add(mulButton);
        convertButtons.add(divButton);
        convertButtons.add(equalsButton);
        convertButtons.add(modButton);
        convertButtons.add(historyButton);
        convertButtons.add(decimalButton);
        convertButtons.add(runtimeButton);
        convertButtons.add(stopButton);

        for(JButton convButton: convertButtons){

            convButton.addActionListener(this);
            convButton.setFont(myFontText);
            convButton.setForeground(Color.white);
            convButton.setFocusable(false);
            convButton.setBackground(buttonColor);
            convButton.setBorder(BorderFactory.createEmptyBorder());

        }

        for(int i = 0; i < 10; i++){
            numberButtons[i] = new JButton(String.valueOf(i));
            numberButtons[i].addActionListener(this);
            numberButtons[i].setFont(myFontNumbers);
            numberButtons[i].setForeground(Color.white);
            numberButtons[i].setBackground(buttonColor);
            numberButtons[i].setBorder(BorderFactory.createEmptyBorder());

        }

        panel = new JPanel();
        panel.setBounds(20, 180, 450, 200);
        panel.setLayout(new GridLayout(5,5,10,10));
        panel.setBackground(backgroundColor);

        // Adding the buttons into the panel
        panel.add(hexButton);
        panel.add(numberButtons[1]);
        panel.add(numberButtons[2]);
        panel.add(numberButtons[3]);
        panel.add(addButton);

        panel.add(octalButton);
        panel.add(numberButtons[4]);
        panel.add(numberButtons[5]);
        panel.add(numberButtons[6]);
        panel.add(subButton);

        panel.add(binaryButton);
        panel.add(numberButtons[7]);
        panel.add(numberButtons[8]);
        panel.add(numberButtons[9]);
        panel.add(mulButton);

        panel.add(equalsButton);
        panel.add(divButton);
        panel.add(numberButtons[0]);
        panel.add(modButton);
        panel.add(deleteButton);

        panel.add(historyButton);
        panel.add(clearButton);
        panel.add(decimalButton);
        panel.add(runtimeButton);
        panel.add(stopButton);

        name = new JLabel("Calculator");
        name.setBounds(20, -35, 400, 100);
        name.setFont(myFontText);
        name.setForeground(Color.white);

        frame.add(name);
        frame.add(panel);
        frame.add(inputField);
        frame.add(resultField);
        frame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(conversion){
            inputField.setText("");
            resultField.setText("");
            number2 = 0;
            conversion = false;
        }
        // Add number into the input field
        for(int i = 0; i < 10; i++){
            if(e.getSource() == numberButtons[i]){
                inputField.setText(inputField.getText().concat(String.valueOf(i)));
                if(opera) {
                    resultField.setText(String.valueOf(result));
                    opera = false;

                }

            }
        }

        MyThread obj = new MyThread();
        Thread thread = new Thread(obj);

        try {
            if (e.getSource() == addButton) {
                operator = '+';
                number1 = check_operation.turnToNumber(inputField.getText(), number1);

                inputField.setText("");
                if (!opera) {
                    resultField.setText(String.valueOf(number1).concat(" + "));
                }
            }
            if (e.getSource() == subButton) {
                operator = '-';
                number1 = check_operation.turnToNumber(inputField.getText(), number1);

                inputField.setText("");
                if (!opera) {
                    resultField.setText(String.valueOf(number1).concat(" - "));
                }
            }
            if (e.getSource() == mulButton) {
                operator = '*';
                number1 = check_operation.turnToNumber(inputField.getText(), number1);

                inputField.setText("");
                if (!opera) {
                    resultField.setText(String.valueOf(number1).concat(" * "));
                }

            }
            if (e.getSource() == divButton) {
                operator = '/';
                number1 = check_operation.turnToNumber(inputField.getText(), number1);

                inputField.setText("");
                if (!opera) {
                    resultField.setText(String.valueOf(number1).concat(" / "));
                }
            }
            if (e.getSource() == modButton) {
                operator = '%';
                number1 = check_operation.turnToNumber(inputField.getText(), number1);

                inputField.setText("");
                if (!opera) {
                    resultField.setText(String.valueOf(number1).concat(" % "));
                }
            }
            if (e.getSource() == clearButton) {
                inputField.setText("");
                resultField.setText("");
                number1 = 0;
                number2 = 0;
                opera = false;
                operator = '\0';
            }
            if (e.getSource() == deleteButton) {
                if (!inputField.getText().equals("")) {
                    String string = inputField.getText();
                    inputField.setText("");
                    for (int i = 0; i < string.length() - 1; i++) {
                        inputField.setText(inputField.getText() + string.charAt(i));
                    }
                }
            }
            if (e.getSource() == decimalButton) {
                if (!inputField.getText().equals("")) {
                    inputField.setText(inputField.getText().concat("."));
                }
            }

            if (e.getSource() == hexButton) {
                if (inputField.getText().equals("")) {
                    inputField.setText(String.valueOf(number1));
                    con = (int) number1;
                } else {
                    con = Integer.parseInt(inputField.getText());
                }

                // LAMBDA FUNKCIJA
                convert = (x) -> {
                    String word = "";
                    int reminder;
                    NumberToCharacter symbol = new NumberToCharacter();
                    while(x > 0){
                        reminder = x % 16;
                        word = symbol.convertToChar(reminder) + word;
                        x = x / 16;
                    }
                    return word;
                };
                resultField.setText(convert.convertToFormat(con));
                historyList.add(resultField.getText());
                conversion = true;
                number1 = con;
            }
            if (e.getSource() == octalButton) {
                if (inputField.getText().equals("")) {
                    inputField.setText(String.valueOf(number1));
                    con = (int) number1;
                } else {
                    con = Integer.parseInt(inputField.getText());
                }
                // LAMBDA FUNKCIJA
                convert = (x) ->{
                    String word = "";
                    int reminder;
                    while(x > 0){
                        reminder = x % 8;
                        word = reminder + word;
                        x = x / 8;
                    }
                    return word;
                };
                resultField.setText(convert.convertToFormat(con));
                historyList.add(resultField.getText());
                conversion = true;
                number1 = con;
            }
            if (e.getSource() == binaryButton) {
                // FACTORY DESIGN PATTERN
                convertWithFactoryDesign = new Binary();
                if (inputField.getText().equals("")) {
                    inputField.setText(String.valueOf(number1));
                    con = (int) number1;
                } else {
                    con = Integer.parseInt(inputField.getText());
                }
                resultField.setText(convertWithFactoryDesign.convertFormat(con));
                historyList.add(resultField.getText());
                conversion = true;
                number1 = con;
            }
            if(e.getSource() == historyButton){

                new HistoryPanel(historyList, backgroundColor, textFieldColor, myFontNumbers);
            }
            if(e.getSource() == runtimeButton){
                thread.start();
            }
            if(e.getSource() == stopButton){
                obj.timerStop();
            }




        } catch(NumberFormatException exc) {
            popupMessage = new MessagePanels();
            popupMessage.errorMessage("Wrong format, please enter a number");
            inputField.setText("");
        }


        try {
            if(e.getSource() == equalsButton){
                EqualsOperation equals = new EqualsOperation();

                equals.checkIfInputIsEmpty(inputField.getText());
                if(number2 == 0){
                    number2 = Double.parseDouble(inputField.getText());
                }
                if(!resultField.getText().equals("")){
                    number2 = Double.parseDouble(inputField.getText());
                }

                result = equals.performOperation(number1,number2,operator);
                resultField.setText(String.valueOf(result));
                historyList.add(resultField.getText());
                inputField.setText("");
                number1 = result;

            }
        }catch(EmptyStringException d){
            System.err.println("Empty String");
        }catch(NumberFormatException f){
            popupMessage = new MessagePanels();
            popupMessage.errorMessage("Wrong format, please enter a number");
            inputField.setText("");
        }

    }
}
