package cn.liududu.liuchat.entity;

import cn.liududu.liuchat.common.exception.UnresolvedMsgStringException;
import org.junit.Assert;
import org.junit.Test;

import java.net.DatagramPacket;

import static org.junit.Assert.*;

public class IpMsgTest {
    @Test
    public void IpMsgCoventTest() {
        String msg = "1:12:hello:32:this is the first hello";
        DatagramPacket dp = new DatagramPacket(msg.getBytes(),msg.getBytes().length);
        try {
            IpMsg ipmsg = new IpMsg(dp);
            Assert.assertEquals(ipmsg.getVersion(),1);
            Assert.assertEquals(ipmsg.getNo(),12);
            Assert.assertEquals(ipmsg.getNickname(),"hello");
            Assert.assertEquals(ipmsg.getCommand(),32);
            Assert.assertEquals(ipmsg.getText(),"this is the first hello");
            System.out.println(ipmsg.getText());
            byte[] test = ipmsg.toDatagramPacket().getData();
            System.out.println(new String(test,0,test.length));
        } catch (UnresolvedMsgStringException e) {
            System.out.println("消息格式错误");
        }
    }
    @Test
    public void ipmsg2udp() {

    }
}