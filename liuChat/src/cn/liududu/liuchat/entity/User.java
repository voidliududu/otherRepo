package cn.liududu.liuchat.entity;

import java.net.InetAddress;

public class User {
    public static User me;
    private String name;
    private InetAddress ipAddr;
    private int status;
    public static final int ONLINE = 0;
    public static final int BUSY = 1;
    public static final int OFFLINE = 2;

    public User(String name,InetAddress ipAddr) {
        this.name = name;
        this.ipAddr = ipAddr;
        status = ONLINE;
    }

    public static User getCurrentUser() {
        return me;
    }

    public static void setCurrentUser(User user) {
        me = user;
    }

    public String getName() {
        return name;
    }

    public InetAddress getIpAddr() {
        return ipAddr;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }
}
