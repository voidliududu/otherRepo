package cn.liududu.liuchat.view;

import javax.swing.*;
import cn.liududu.liuchat.common.Theme;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.listener.WindowWatcher;

import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ContainerAdapter;
import java.awt.event.WindowAdapter;

public class MainWindow extends JFrame {
    private static MainWindow mw;

    private Contacts contacts;
    private ChatFrame chatFrame;
    private User sessionUser;
    public MainWindow() {
        super();
        this.setSize(Theme.windowSizeX,Theme.windowSizeY);
        this.sessionUser = null;
//        this.setBackground(Color.BLUE);
//        this.pack();
        Container rootContainer =  getContentPane();

        //添加通讯录
        Contacts con = new Contacts();

        contacts = con;
        rootContainer.add(con,"West");

        //添加聊天窗
        chatFrame = new ChatFrame();
        rootContainer.add(chatFrame);

        //添加群聊界面
        ContactsItem item = new ContactsItem();
        MessageBoard mb = new MessageBoard(item.ipAddr);
        con.addContactsItem(item);
        chatFrame.getMw().addMessageBoard(mb);
        chatFrame.getMw().changeMessageBoard(item.ipAddr);
        //主窗口属性设置
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);


        this.addWindowListener(new WindowWatcher());

    }

    public static MainWindow getInstance() {
        if (mw != null) {
            return mw;
        } else {
            mw = new MainWindow();
            return mw;
        }
    }

    public Contacts getContacts() {
        return contacts;
    }

    public ChatFrame getChatFrame() {
        return chatFrame;
    }

    public User getSessionUser() {
        return sessionUser;
    }

    public void setSessionUser(User sessionUser) {
        this.sessionUser = sessionUser;
    }
}
