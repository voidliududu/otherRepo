package cn.liududu.liuchat.view;


import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.entity.Message;

import javax.swing.*;
import java.awt.*;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class MessageWindow extends JPanel {
    private CardLayout card;
    private Map<String,MessageBoard> chatWindow;
    public MessageWindow() {
        super();
        card = new CardLayout();
        chatWindow = new HashMap<>();
        this.setLayout(card);
        MessageBoard groupMessageBoard = new MessageBoard("group");
        this.addMessageBoard(groupMessageBoard);
        this.getMessageBoard("group").addMessage(new MessageBox("test","tsets",new Date()));
    }
    /**
    * message Window
    *
    * */
    public void addMessageBoard(MessageBoard mb) {
        this.add(mb,mb.getId());
        this.chatWindow.put(mb.getId(),mb);
    }

    public void removeMessageBoard(String id) {
        this.chatWindow.remove(id);
    }

    /**
    * 获取MessageBoard
    *
    * */
    public MessageBoard getMessageBoard(String id) {
        return this.chatWindow.get(id);
    }
    /**
    * 改变显示的window
    *
    * */
    public void changeMessageBoard(String id) {
        if (chatWindow.containsKey(id)) {
            card.show(this, id);
        } else {
            MessageBoard mb = new MessageBoard(id);
            chatWindow.put(id, mb);
            this.add(mb,id);
            card.show(this,id);
        }
    }
}

//        container = new JPanel(new FlowLayout(FlowLayout.LEFT));
//        pcontainer = new JScrollPane(container);
//        pcontainer.setPreferredSize(new Dimension(600,300));
//        container.setPreferredSize(new Dimension(600,300));
////        pcontainer.add(container);
//        MessageBox test = new MessageBox("test","hello world",new Date());
//        MessageBox test1 = new MessageBox("test","hello world",new Date());
//        MessageBox test2 = new MessageBox("test","hello world",new Date());
//        MessageBox test3 = new MessageBox("test","hello world",new Date());
//        MessageBox test4 = new MessageBox("test","hello world",new Date());
//        MessageBox test5 = new MessageBox("test","hello world",new Date());
//        MessageBox test6 = new MessageBox("test","hello world",new Date());
//
//        this.addMessage(test);
//        this.addMessage(test1);
//        this.addMessage(test2);
//        this.addMessage(test3);
//        this.addMessage(test4);
//        this.addMessage(test5);
//        this.addMessage(test6);
//
//        this.add(pcontainer);