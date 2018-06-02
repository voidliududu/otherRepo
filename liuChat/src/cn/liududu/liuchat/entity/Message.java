package cn.liududu.liuchat.entity;

import java.net.DatagramSocket;
import java.util.Date;

public class Message {
    private String from;
    private String address;
    private String text;
    private Date date;

    public Message(String from, String address, String text) {
        this.address = address;
        this.from = from;
        this.text = text;
        this.date = new Date();
    }

    public String getFrom() {
        return from;
    }

    public String getAddress() {
        return address;
    }

    public String getText() {
        return text;
    }

    public Date getDate() {
        return date;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setText(String text) {
        this.text = text;
    }

    public void setDate(Date date) {
        this.date = date;
    }
}
