package lab02;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Calculator extends JFrame implements ActionListener {

    JTextField textField;
    String operator = "";
    double num1 = 0, num2 = 0;

    public Calculator() {
        setTitle("Simple Calculator");
        setSize(900, 1200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        textField = new JTextField();
        textField.setFont(new Font("Arial", Font.BOLD, 20));
        add(textField, BorderLayout.NORTH);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 4, 5, 5));

        String[] buttons = {
            "7","8","9","+",
            "4","5","6","-",
            "1","2","3","*",
            "0","%","=","C"
        };

        for (String text : buttons) {
            JButton btn = new JButton(text);
            btn.setFont(new Font("Arial", Font.BOLD, 18));
            btn.addActionListener(this);
            panel.add(btn);
        }

        add(panel);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        if (command.matches("[0-9]")) {
            textField.setText(textField.getText() + command);
        } 
        else if (command.matches("[+\\-*/%]")) {
            num1 = Double.parseDouble(textField.getText());
            operator = command;
            textField.setText("");
        } 
        else if (command.equals("=")) {
            num2 = Double.parseDouble(textField.getText());
            double result = 0;

            switch (operator) {
                case "+": result = num1 + num2; break;
                case "-": result = num1 - num2; break;
                case "*": result = num1 * num2; break;
                case "%": result = num1 % num2; break;
            }

            textField.setText(String.valueOf(result));
        } 
        else if (command.equals("C")) {
            textField.setText("");
            num1 = num2 = 0;
            operator = "";
        }
    }

    public static void main(String[] args) {
        new Calculator();
    }
}