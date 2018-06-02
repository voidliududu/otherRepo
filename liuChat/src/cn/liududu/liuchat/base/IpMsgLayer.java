package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.IpMsgCommand;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.IpMsg;
import cn.liududu.liuchat.entity.User;

public class IpMsgLayer {
    public static IpMsgLayer ipMsgLayer;
    private ProtocolHandler ph;
    private MsgDispatcher md;
    private UdpService us;
    private BroadcastService bs;
    private User me;

    public IpMsgLayer(User me, UdpService us, BroadcastService bs) {
        this.us = us;
        this.me = me;
        this.ph = new ProtocolHandler(us, bs);
        this.md = new MsgDispatcher(me, us);
    }

    public static IpMsgLayer getInstance(User me, UdpService us, BroadcastService bs) {
        Logger.log("ipMsglayer 实例化");
        if (ipMsgLayer != null) {
            return ipMsgLayer;
        } else {
            ipMsgLayer = new IpMsgLayer(me, us, bs);
            return ipMsgLayer;
        }
    }

    public static IpMsgLayer getInstance() {
        return ipMsgLayer;
    }

    public void login() {
        this.getPh().getListRequest(me);
    }

    /**
     * 分发响应
     */
    public void dispatch(IpMsg ipMsg) {
        switch (ipMsg.getCommand()) {
            case IpMsgCommand.IPMSG_SENDMSG:
                Logger.log("收到私聊消息");
                md.receiveMsgResponse(ipMsg);
                break;
            case IpMsgCommand.IPMSG_SENDMSGTOALL:
                Logger.log("收到群发消息");
                md.receiveGroupMsgResponse(ipMsg);
                break;
            case IpMsgCommand.IPMSG_GETLIST:
                Logger.log("收到列表请求");
                md.getListResponse(ipMsg);
                break;
            case IpMsgCommand.IPMSG_ANSLIST:
                Logger.log("收到列表请求回复");
                md.receiveGetList(ipMsg);
                break;
            case IpMsgCommand.IPMSG_GETFILEDATA:
                Logger.log("收到用户文件传输请求");
                md.handleFileTransferRequest(ipMsg);
                break;
            case IpMsgCommand.IPMSG_BR_EXIT:
                Logger.log("收到用户离线请求");
                md.handleUserExit(ipMsg);
        }
    }

    public ProtocolHandler getPh() {
        return ph;
    }
}
///**
//* 协议请求的处理
//*
//* */
//class ProtocolHandler {
//    private UdpService us;
//
//    public ProtocolHandler(UdpService us) {
//        this.us = us;
//    }
//    /**
//    * 发送更新用户列表的请求
//    *
//    * */
//    public void getListRequest(User me) {
//        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_GETLIST);
//
//    }
//    /**
//    * 向用户发送消息
//    *
//    * */
//    public void sendMsg(User me, User user,String msg){
//        IpMsg ipMsg = new IpMsg(me.getName(),IpMsgCommand.IPMSG_SENDMSG);
//        ipMsg.setAddr(user.getIpAddr());
//        ipMsg.setText(msg);
//        us.sendMsg(ipMsg.toDatagramPacket());
//    }
//    /**
//    * 群发消息
//    *
//    * */
//    public void sendAll(User me,String msg) {
//
//    }
//    /**
//    * 请求发送文件
//    *
//    * */
//    public void fileTransferRequest(User me, User user,File file) {
//
//    }
//
//}
///**
//* 负责响应消息的处理
//*
//* */
//class MsgDispatcher{
//    private UdpService us;
//    private User me;
//
//    public MsgDispatcher(User me,UdpService us) {
//        this.us = us;
//        this.me = me;
//    }
//    /**
//    * 请求列表的响应
//    *
//    * */
//    public void getListResponse() {
//
//    }
//    /**
//    * 收到群发消息的响应
//    *
//    * */
//    public void receiveGroupMsgResponse() {
//
//    }
//    /**
//    * 收到私聊消息的响应
//    *
//    *
//    * */
//    public void receiveMsgResponse(IpMsg ipMsg) {
//        System.out.println(ipMsg.getText());
//    }
//    /*
//    *
//    *
//    * */
//}
