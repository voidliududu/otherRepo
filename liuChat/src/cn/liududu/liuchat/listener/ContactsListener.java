package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.view.ContactsItem;
import cn.liududu.liuchat.view.MainWindow;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


/**
* 处理与通讯录有关的事件
*
* */
public class ContactsListener implements ListSelectionListener {

    /**
    * 当用户点击列表项时，更改会话用户，显示当前用户的消息窗
    *
    * */
    @Override
    public void valueChanged(ListSelectionEvent listSelectionEvent) {
        MainWindow mw = MainWindow.getInstance();
        JList<ContactsItem> jl = (JList)listSelectionEvent.getSource();
        ContactsItem item = jl.getModel().getElementAt(jl.getSelectedIndex() == -1? 0 : jl.getSelectedIndex());
        item.setState(ContactsItem.NORMAL);
        System.out.println(item.getName());
        mw.getChatFrame().getMw().changeMessageBoard(item.getIpAddr());
        mw.setSessionUser(item.toUser());
        System.out.println(mw.getSessionUser());
//        System.out.println(mw.getSessionUser().getName());
    }
    //todo 什么时候创建消息窗？ 获知用户存活时
}
