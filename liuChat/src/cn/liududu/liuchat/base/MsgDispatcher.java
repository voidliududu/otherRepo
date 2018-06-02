package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.IpMsgCommand;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.IpMsg;
import cn.liududu.liuchat.entity.Message;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.listener.FileTransferRequest;
import cn.liududu.liuchat.listener.MessageListener;
import cn.liududu.liuchat.listener.UserListener;

import javax.swing.*;
import java.net.InetAddress;

public class MsgDispatcher {
    private UdpService us;
    private User me;

    public MsgDispatcher(User me,UdpService us) {
        this.us = us;
        this.me = me;
    }
    /**
     * 请求列表的响应
     *
     * */
    public void getListResponse(IpMsg ipMsg) {
        InetAddress address = ipMsg.getAddr();
        Logger.log("收到列表请求,来自" + address.toString());
        IpMsg responseMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_ANSLIST);
        responseMsg.setAddr(address);
        us.sendMsg(responseMsg.toDatagramPacket());
        User user = new User(ipMsg.getNickname(),ipMsg.getAddr());
        new UserListener().userEntry(user);
    }
    /**
    * 用户离线消息的处理
    *
    *
    * */
    public void handleUserExit(IpMsg ipMsg) {
        User user = new User(ipMsg.getNickname(),ipMsg.getAddr());
        new UserListener().userExit(user);
    }
    /**
     * 收到群发消息的响应
     *
     * */
    public void receiveGroupMsgResponse(IpMsg ipMsg) {
        Message message = new Message(ipMsg.getNickname(),ipMsg.getAddr().toString(),ipMsg.getText());
        new MessageListener().groupMessageCome(message);
    }
    /**
     * 收到私聊消息的响应
     *
     *
     * */
    public void receiveMsgResponse(IpMsg ipMsg) {
        Message message = new Message(ipMsg.getNickname(),ipMsg.getAddr().toString().split("/")[1],ipMsg.getText());
        new MessageListener().messageCome(message);
    }
    /**
     *收到列表回复的响应
     *
     * */
    public void receiveGetList(IpMsg ipMsg) {
        User user = new User(ipMsg.getNickname(),ipMsg.getAddr());
        new UserListener().userEntry(user);
    }

    /**
    * 文件传输请求的处理
    *
    * */
    public void handleFileTransferRequest(IpMsg ipMsg) {
         String name = ipMsg.getNickname();
         String fileInfo = ipMsg.getText();
         String tipsInfo = "用户 " + name + " 请求向你传输文件 " + fileInfo;
         int result = JOptionPane.showConfirmDialog(null, tipsInfo, tipsInfo, JOptionPane.YES_NO_OPTION);
         if (result == 1) {
             //发送同意请求并监听在指定端口
             IpMsgLayer.getInstance().getPh().acceptFileTransferRequest(me,ipMsg.getUserInfo(),ipMsg.getText());
             new FileTransferRequest().AcceptRequest(ipMsg.getAddr().toString().split("/")[1]);
         } else{
             //拒绝文件传输请求
             IpMsgLayer.getInstance().getPh().declineFileTransferRequest(me,ipMsg.getUserInfo());
         }
    }

    /**
    * 拒绝文件传输的处理
    *
    * */
    public void handleDeclineFileTransferRequest(IpMsg ipMsg) {

    }

    /**
    * 同意文件传输请求的处理
    *
    * */
    public void handleAcceptFileTransferRequest(IpMsg ipMsg) {

    }
}
