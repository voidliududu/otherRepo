package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.entity.User;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.UnknownHostException;

import static org.junit.Assert.*;

public class UdpServiceTest {
    private UdpService udpService;
    @Before
    public void setup() {
        try {
            User me = new User("hello", InetAddress.getLocalHost());
            udpService = UdpService.getInstance();
            new Thread(udpService).start();
        } catch (UnknownHostException e) {

        }
    }
    @Test
    public void sendTest() {

        String testMsg = "1:12:hello:32:this is the first hello";
        byte[] data = testMsg.getBytes();

        DatagramPacket dp = new DatagramPacket(data,data.length);
        try {
            dp.setAddress(InetAddress.getLocalHost());
            dp.setPort(Config.udpPort);
        } catch (UnknownHostException e) {

        }
        udpService.sendMsg(dp);
        udpService.sendMsg(dp);
        udpService.sendMsg(dp);
        udpService.sendMsg(dp);
        udpService.sendMsg(dp);
    }
    @After
    public void afterTest() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e){

        }
    }
}