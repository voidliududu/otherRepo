package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.exception.UnresolvedMsgStringException;
import cn.liududu.liuchat.entity.IpMsg;

import java.net.DatagramPacket;

public class Response implements ReceiveHandler {
    private DatagramPacket dp;

    /**
    * 接收消息的入口
    *
    * */
    public void run() {
        handle();
    }
    /**
    * 由UdpService调用
     * @param dp DatagramPacket 接收到的数据报
    * */
    public void setDatagramPacket(DatagramPacket dp) {
        this.dp = dp;
    }
    /**
    * 对消息的处理
    *
    * */
    public void handle() {
        try {
            IpMsgLayer iml = IpMsgLayer.getInstance();
            iml.dispatch(new IpMsg(dp));
        } catch (UnresolvedMsgStringException e) {

        }
    }
}
