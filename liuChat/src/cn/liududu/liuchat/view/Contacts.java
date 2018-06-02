package cn.liududu.liuchat.view;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.common.Theme;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.listener.ContactsListener;
import cn.liududu.liuchat.listener.TestListener;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ContainerAdapter;
import java.awt.event.ContainerEvent;
import java.util.Vector;

/**
* 通讯录Panel
* */
public class Contacts extends JPanel {
    private JList<ContactsItem> jl;
    private DefaultListModel<ContactsItem> listModel;
    public Contacts() {
        super();
        listModel = new DefaultListModel<ContactsItem>();
        jl = new JList<>(listModel);
        jl.setCellRenderer(new ContactsListRender());
        jl.addListSelectionListener(new ContactsListener());
        jl.setBackground(Color.decode(Theme.ContactsBackgroundColor));
        JScrollPane jsp = new JScrollPane(jl);
        jsp.setBorder(BorderFactory.createEmptyBorder());
        jsp.setPreferredSize(new Dimension(Theme.ContactListWidth,Theme.ContactListHeigth));
        jsp.setBackground(Color.decode(Theme.ContactsBackgroundColor));
        this.add(jsp);
        setPreferredSize(new Dimension(150,60));
    }
    /**
    * 添加通讯记录
    * */
    public void addContactsItem(ContactsItem item) {
        this.listModel.addElement(item);
    }
    /**
    * 从通讯录中删除记录
    *
    * */
    public void removeContactsItem(ContactsItem contactsItem) {
        int removedItem = -1;
        int length = this.listModel.getSize();
        for (int i = 0; i < length; i++) {
            if (((ContactsItem)(listModel.get(i))).getIpAddr().equals(contactsItem.getIpAddr())){
                removedItem = i;
            }
        }
        if (removedItem != -1) {
            this.listModel.remove(removedItem);
        }
    }
    /**
    * 通过ip从通讯录中查找记录
    *
    * */
    public ContactsItem findItemByIp(String ipaddr) {
        int targetItem = -1;
        int length = this.listModel.getSize();
        for (int i = 0; i < length; i++) {
            if (((ContactsItem)(listModel.get(i))).getIpAddr().equals(ipaddr)){
                targetItem = i;
            }
        }
        if (targetItem != -1) {
            return (ContactsItem)(this.listModel.get(targetItem));
        } else {
            return null;
        }
    }
}


class ContactsListRender extends ContactsItem implements ListCellRenderer<ContactsItem> {
    @Override
    public Component getListCellRendererComponent(JList<? extends ContactsItem> jList, ContactsItem contactsItem, int i, boolean b, boolean b1) {

        if (b) {
            contactsItem.setBackground(Color.decode(Theme.ContactsItemSelectColor));
            contactsItem.info.setBackground(Color.decode(Theme.ContactsItemSelectColor));
        } else {
            if (contactsItem.state == ContactsItem.NOTIFY) {
                contactsItem.setBackground(Color.decode(Theme.NotifiedContactsItemBackgroundColor));
                contactsItem.info.setBackground(Color.decode(Theme.NotifiedContactsItemBackgroundColor));
            }else {
                contactsItem.setBackground(Color.decode(Theme.ContactsBackgroundColor));
                contactsItem.info.setBackground(Color.decode(Theme.ContactsBackgroundColor));
            }
        }

        return contactsItem;
    }
}

/*列表前图标*/
//        Panel avator = new Panel();
//        avator.add(new JLabel(new ImageIcon(Config.defaultAvator)));
//        JLabel nameLabel = new JLabel(user.getName());
//        JLabel ipAddrLabel = new JLabel(user.getIpAddr().toString());
//        nameLabel.setBackground(Color.decode(Theme.ContactsBackgroundColor));
//        ipAddrLabel.setBackground(Color.decode(Theme.ContactsBackgroundColor));
//
//        this.add(nameLabel);
//        this.add(ipAddrLabel);
//        Panel info = new Panel();
//        info.setLayout(new BorderLayout());
//        info.add(nameLabel,"North");
//        info.add(ipAddrLabel,"South");
//        this.add(avator);
//        this.add(info);
//
//        this.setBackground(Color.decode(Theme.ContactsBackgroundColor));
//        this.setVisible(true);
