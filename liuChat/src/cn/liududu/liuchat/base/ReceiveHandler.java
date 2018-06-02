package cn.liududu.liuchat.base;

import java.net.DatagramPacket;

public interface ReceiveHandler extends Runnable{
    public void handle();

    public void setDatagramPacket(DatagramPacket dp);
}
