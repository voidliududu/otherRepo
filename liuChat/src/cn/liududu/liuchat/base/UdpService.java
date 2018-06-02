package cn.liududu.liuchat.base;

import java.io.IOException;
import java.net.*;
import java.util.LinkedList;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;

/**
* Udp通信服务提供者
*
*
* */
public class UdpService extends Thread
{
    public static UdpService udpService;
    private DatagramSocket ds;
    private MsgQueue msgQueue;
    private Sender sender;
    private Receiver receiver;
    /**
    *
    * */
    private UdpService()
    {
        try {
//            InetAddress ia = InetAddress.getByName(Config.serveHost);
//            Logger.log(ia.toString());
//            ds = new DatagramSocket(Config.udpPort,InetAddress.getByName(Config.serveHost));
//            Logger.log("配置地址" + ia.toString());
//            ds = new DatagramSocket(Config.udpPort,ia);
//            ds = new DatagramSocket(Config.udpPort,InetAddress.getByName(Config.serveHost));
            ds = new DatagramSocket(Config.udpPort);
            msgQueue = new MsgQueue(Config.msgQueueSize);
            sender = new Sender(ds,msgQueue);
            receiver = new Receiver(ds);
        } catch (SocketException e) {
            Logger.log("端口或地址被占用");
        }/* catch (UnknownHostException e) {
            Logger.log("本机地址未知");
        }*/
    }
    /**
    * 单例化
    *
    * */
    public static UdpService getInstance() {
        if (udpService == null) {
            udpService = new UdpService();
            return udpService;
        } else{
            return udpService;
        }
    }
    /**
    * 启动服务
    *
    * */
    public void run() {
        Logger.log("启动监听消息服务");
        receiver.start();
        Logger.log("启动发送消息服务");
        sender.start();
    }
    /**
    * 发送消息
    *
    * */
    public void sendMsg(DatagramPacket dp) {
        Logger.log("消息加入发送队列");
        msgQueue.enqueue(dp);
    }
}
/**
* 处理发送消息的请求
* */
class Sender extends Thread {
    public final DatagramSocket udpserver;
    public MsgQueue msgQueue;
    public int status;

    public Sender(DatagramSocket ds,MsgQueue msgQueue) {
        this.udpserver = ds;
        this.msgQueue = msgQueue;
        status = 1;
    }
    public void close() {
        this.status = 0;
    }

    private void send(DatagramPacket dp) {
        try {
            Logger.log("即将发送消息");
            Logger.log("目的地" + dp.getAddress().toString());
            udpserver.send(dp);
        } catch (IOException e) {

        }
    }

    @Override
    public void run() {
        while(status == 1) {
            send(msgQueue.dequeue());
        }
    }
}
/*
* 处理接收消息的请求
*
* */
class Receiver extends Thread {
    private DatagramPacket dp;
    private DatagramSocket ds;
    private ReceiveHandler rh;
    private int status;
    public Receiver(DatagramSocket ds) {
        this.ds = ds;
        status = 1;
        byte[] data = new byte[Config.maxDatagramPacketSize];
        this.dp = new DatagramPacket(data,data.length);
        rh = new Response();
    }

    @Override
    public void run() {
        while(status == 1) {
            try {
                this.ds.receive(dp);
                rh.setDatagramPacket(dp);
                Logger.log("收到updServer的消息");
                new Thread(rh).run();
            } catch (IOException e) {

            }
        }
    }
}

/**
* 消息队列
*
* */
class MsgQueue extends LinkedList {

    private int maxSize;
    public MsgQueue(int maxSize) {
        super();
        this.maxSize = maxSize;
    }

    public void enqueue(DatagramPacket dp) {
        synchronized (this) {
            if (this.size() >= this.maxSize) {
                this.dequeue();
            }
            this.addLast(dp);
            this.notify();
        }
    }

    public DatagramPacket dequeue() {
        synchronized (this) {
            while (this.isEmpty()) {
                try {
                    this.wait();
                } catch (InterruptedException e) {

                }
            }
            return (DatagramPacket) removeFirst();
        }
    }
}
