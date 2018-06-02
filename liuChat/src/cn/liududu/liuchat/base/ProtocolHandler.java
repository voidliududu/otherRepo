package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.IpMsgCommand;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.IpMsg;
import cn.liududu.liuchat.entity.User;

import javax.swing.*;
import java.io.File;

public class ProtocolHandler {
    private UdpService us;
    private BroadcastService bs;
    public ProtocolHandler(UdpService us,BroadcastService bs) {
        this.us = us;
        this.bs = bs;
    }
    /**
     * 发送更新用户列表的请求
     *
     * */
    public void getListRequest(User me) {
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_GETLIST);
        bs.sendMsg(ipMsg.toDatagramPacket());
    }
    /**
    * 发送离线请求
    *
    * */
    public void sendOfflineRequest(User me) {
        Logger.log("准备发送离线请求");
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_BR_EXIT);
        bs.sendMsg(ipMsg.toDatagramPacket());
    }
    /**
     * 向用户发送消息
     *
     * */
    public void sendMsg(User me, User user,String msg){
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_SENDMSG);
        ipMsg.setAddr(user.getIpAddr());
        ipMsg.setText(msg);
        us.sendMsg(ipMsg.toDatagramPacket());
    }
    /**
     * 群发消息
     *
     * */
    public void sendAll(User me,String msg) {
        Logger.log("正在准备发送消息");
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_SENDMSGTOALL);
        ipMsg.setText(msg);
        bs.sendMsg(ipMsg.toDatagramPacket());
    }
    /**
     * 请求发送文件
     *
     * */
    public void fileTransferRequest(User me, User user,File file) {
        Logger.log("正在装配文件传输请求消息");
        if (user == null) {
            //todo 用户为空，群聊时发生。显示提示
            JOptionPane.showMessageDialog(null, "未指定发送人", "未指定发送人", JOptionPane.ERROR_MESSAGE);
            return;
        }
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_GETFILEDATA);
        ipMsg.setText(file.getName());
        ipMsg.setAddr(user.getIpAddr());
        us.sendMsg(ipMsg.toDatagramPacket());
    }

    /**
    * 同意文件传输请求
    *
    * */
    public void acceptFileTransferRequest(User me, User user, String text) {
        Logger.log("准备发送文件传输确认");
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_ACCEPTFILEDATA);
        ipMsg.setAddr(user.getIpAddr());
        ipMsg.setText(text);
        us.sendMsg(ipMsg.toDatagramPacket());
    }
    /**
    * 拒绝文件传输请求
    * */
    public void declineFileTransferRequest(User me, User user) {
        Logger.log("准备发送拒绝文件传输请求");
        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_DECLINEFILEDATA);
        ipMsg.setAddr(user.getIpAddr());
        us.sendMsg(ipMsg.toDatagramPacket());
    }
}
