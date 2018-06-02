package cn.liududu.liuchat.listener;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class TestListener extends MouseAdapter {
    @Override
    public void mousePressed(MouseEvent e) {
        JLabel label = (JLabel) e.getSource();
        System.out.println("hel");
        System.out.println(label.getParent());
    }
}
