package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;

import java.io.IOException;
import java.net.*;

public class BroadcastService extends Thread{
    public static BroadcastService bs;
    private MulticastSocket ms;
    private InetAddress addr;
    private MsgQueue msgQueue;
    private MultiSender multiSender;
    private MultiReceiver multiReceiver;
    private BroadcastService() {
        try {
//            InetSocketAddress isa = new InetSocketAddress(InetAddress.getLocalHost(),Config.broadcastPort);
            ms = new MulticastSocket(Config.broadcastPort);
            addr = InetAddress.getByName(Config.broadcastGroup);
            ms.setTimeToLive(10);
            ms.setLoopbackMode(true);
            ms.joinGroup(addr);
            msgQueue = new MsgQueue(Config.msgQueueSize);
            multiSender = new MultiSender(ms,msgQueue);
            multiReceiver = new MultiReceiver(ms);
        } catch (IOException e) {
            Logger.log("广播错误");
            Logger.log(e.getMessage());
            System.exit(0);
        }
    }

    public static BroadcastService getInstance() {
        if (bs == null) {
            bs = new BroadcastService();
            return bs;
        } else{
            return bs;
        }
    }
    @Override
    public void run() {
        Logger.log("启动广播监听消息服务");
        multiReceiver.start();
        Logger.log("启动广播发送消息服务");
        multiSender.start();
    }
    public void sendMsg(DatagramPacket dp)
    {
        dp.setAddress(addr);
        dp.setPort(Config.broadcastPort);
        Logger.log("正将消息加入队列");
        msgQueue.enqueue(dp);
    }
}

class MultiSender extends Thread{
    public final MulticastSocket udpserver;
    public MsgQueue msgQueue;
    public int status;

    public MultiSender(MulticastSocket ds,MsgQueue msgQueue) {
        this.udpserver = ds;
        this.msgQueue = msgQueue;
        status = 1;
    }
    public void close() {
        this.status = 0;
    }

    private void send(DatagramPacket dp) {
        try {
            Logger.log("广播即将发送");
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

class MultiReceiver extends Thread{
    private DatagramPacket dp;
    private MulticastSocket ds;
    private ReceiveHandler rh;
    private int status;
    public MultiReceiver(MulticastSocket ds) {
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
                Logger.log("收到广播消息");
                rh.setDatagramPacket(dp);
                new Thread(rh).run();
            } catch (IOException e) {

            }
        }
    }
}
