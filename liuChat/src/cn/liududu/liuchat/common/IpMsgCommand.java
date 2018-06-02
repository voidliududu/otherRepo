package cn.liududu.liuchat.common;

import org.omg.CORBA.PUBLIC_MEMBER;

public class IpMsgCommand {
    //广播消息
    public static final int IPMSG_NOOPERATION = 0; // 不进行任何操作
    public static final int IPMSG_BR_ENTRY = 1; // 用户上线
    public static final int IPMSG_BR_EXIT = 2; // 用户退出
    public static final int IPMSG_ANSENTRY = 3; // 通报在线
    public static final int IPMSG_BR_ABSENCE = 4; // 改为缺席模式

    public static final int IPMSG_BR_ISGETLIST = 16; // 寻找有效的可以发送用户列表的成员
    public static final int IPMSG_OKGETLIST = 17; // 通知用户列表已经获得
    public static final int IPMSG_GETLIST = 18; // 用户列表发送请求
    public static final int IPMSG_ANSLIST = 19; // 应答用户列表发送请求
    public static final int IPMSG_FILE_MTIME = 20; //
    public static final int IPMSG_FILE_CREATETIME = 22; //
    public static final int IPMSG_BR_ISGETLIST2 = 24; //

    public static final int IPMSG_SENDMSG = 32; // 发送消息
    public static final int IPMSG_SENDMSGTOALL = 34; // 发送消息
    public static final int IPMSG_RECVMSG = 33; // 通报收到消息
    public static final int IPMSG_READMSG = 48; // 消息打开通知
    public static final int IPMSG_DELMSG = 49; // 消息丢弃通知
    public static final int IPMSG_ANSREADMSG = 50; // 消息打开确认通知（version-8中添加）

    public static final int IPMSG_GETFILEDATA = 96; // 文件传输请求
    public static final int IPMSG_RELEASEFILES = 97; // 丢弃附加文件
    public static final int IPMSG_GETDIRFILES = 98; // 附着统计文件请求
    public static final int IPMSG_ACCEPTFILEDATA = 99; //同意文件发送请求
    public static final int IPMSG_DECLINEFILEDATA = 100; //拒绝文件发送请求

}
