package cn.liududu.liuchat.view;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.listener.TestListener;

import javax.swing.*;
import java.awt.*;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
* 通讯录列表项
* */
public class ContactsItem extends JPanel {
    protected String name;
    protected String ipAddr;
    public JLabel nameLabel;
    public JLabel ipAddrLabel;
    public JPanel info;
    public int state = 0;

    public static final int NORMAL = 0;
    public static final int NOTIFY = 1;

    /**
    * 通过user构造通讯列表项
     * @param user 用户对象
    * */
    public ContactsItem(User user) {
        super();
        name = user.getName();
        ipAddr = user.getIpAddr().toString().split("/")[1];

        nameLabel = new JLabel(this.name);
        nameLabel.addMouseListener(new TestListener());
        /*ip*/
        ipAddrLabel = new JLabel(this.ipAddr);
        info = new JPanel();
        info.setLayout(new BorderLayout());
        info.add(nameLabel,"North");
        info.add(ipAddrLabel,"South");
        this.add(info);

    }

    @Override
    public void setBackground(Color color) {
        super.setBackground(color);
//        nameLabel.setBackground(color);
//        ipAddrLabel.setBackground(color);
//        info.setBackground(color);
    }

    public void setState(int state) {
        this.state = state;
    }

    /**
    * 默认构造函数用于测试
     *
    * */
    public ContactsItem() {
        super();
        this.ipAddr = Config.broadcastGroup;
        this.name = Config.groupName;

        nameLabel = new JLabel(this.name);
        nameLabel.addMouseListener(new TestListener());
        /*ip*/
        ipAddrLabel = new JLabel(this.ipAddr);
        info = new JPanel();
        info.setLayout(new BorderLayout());
        info.add(nameLabel,"North");
        info.add(ipAddrLabel,"South");
        this.add(info);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }

    public String getIpAddr() {
        return ipAddr;
    }

    public void setIpAddr(String ipAddr) {
        this.ipAddr = ipAddr;
    }

    public User toUser() {
        if (name.equals(Config.groupName)) {
            return null;
        }
        InetAddress ip;
        try {
            ip = InetAddress.getByName(ipAddr);
        } catch (UnknownHostException e) {
            ip = null;
        }
        return new User(name,ip);
    }
}
