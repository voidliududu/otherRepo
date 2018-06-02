package cn.liududu.liuchat.view;

import cn.liududu.liuchat.common.Theme;
import cn.liududu.liuchat.listener.FileButtonListener;
import cn.liududu.liuchat.listener.MessageSubmitListener;

import javax.swing.*;
import java.awt.*;

public class TextBar extends JPanel {

    public static TextBar textBar;

    private JTextArea jta;
    private JButton submit;
    private JButton sendFile;

    public TextBar() {
        this.setLayout(new BorderLayout());
        jta = new JTextArea();
        jta.setRows(5);
        this.add(jta,"North");
        this.setBorder(BorderFactory.createEmptyBorder(10,20,10,20));
        JPanel headBar = new JPanel();
        headBar.setLayout(new FlowLayout(FlowLayout.RIGHT));

        submit = new JButton("发送");
        submit.setBackground(Color.decode(Theme.ButtonBackgroundColor));
        submit.setForeground(Color.WHITE);
        submit.addActionListener(new MessageSubmitListener());
        sendFile = new JButton("传输文件");
        sendFile.setBackground(Color.decode(Theme.ButtonBackgroundColor));
        sendFile.setForeground(Color.WHITE);
        sendFile.addActionListener(new FileButtonListener());
        headBar.add(sendFile);
        headBar.add(submit);

        this.add(headBar,"South");
    }

    public static TextBar getInstance() {
        if (textBar != null) {
            return textBar;
        } else{
            textBar = new TextBar();
            return textBar;
        }
    }

    public String getText() {
        return jta.getText();
    }

    public void clearText() {
        this.jta.setText("");
    }
}
