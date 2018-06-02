package cn.liududu.liuchat.entity;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.common.exception.UnresolvedMsgStringException;

import java.net.DatagramPacket;
import java.net.InetAddress;

public class IpMsg {
    private int version;

    private int no;

    private String nickname;

    private int command;

    private String text;

    private InetAddress addr;
    /**
    * 提取msg字符串中的各字段
     * @param msg 协议字符串
    *
    * */
    private void resolveIpMsg(String msg) throws UnresolvedMsgStringException{
        String[] words = msg.split(":");
        if (words.length < 5) {
            throw new UnresolvedMsgStringException();
        }
        version = Integer.parseInt(words[0]);
        no = Integer.parseInt(words[1]);
        nickname = words[2];
        command = Integer.parseInt(words[3]);
        text = words[4];
    }
    /**
    *
    *
    * */
    public IpMsg() {

    }
    public IpMsg(String nickname, int command) {
        version = 0;
        no = 0;
        this.nickname = nickname;
        this.command = command;
    }
    /**
    * 数据报和IpMsg的转化
    *
    * */
    public IpMsg(DatagramPacket dp) throws UnresolvedMsgStringException{
        String msg = new String(dp.getData(),0,dp.getLength());
        resolveIpMsg(msg);
        addr = dp.getAddress();
    }
    /**
    * IpMsg转数据报
    *
    * */
    public DatagramPacket toDatagramPacket() {
        String msg = new Integer(version).toString() + ":"
                + new Integer(no).toString() + ":"
                + nickname + ":"
                + new Integer(command).toString() + ":"
                + text;
        byte[] bitmsg = msg.getBytes();
        DatagramPacket dp = new DatagramPacket(bitmsg,bitmsg.length);
        dp.setPort(Config.udpPort);
        dp.setAddress(addr);
        return dp;
    }

    /**
    * 通过IpMsg获取用户信息
    * */
    public User getUserInfo() {
        return new User(this.nickname,this.getAddr());
    }

    public int getVersion() {
        return version;
    }

    public int getNo() {
        return no;
    }

    public String getNickname() {
        return nickname;
    }

    public int getCommand() {
        return command;
    }

    public String getText() {
        return text;
    }

    public InetAddress getAddr() {
        return addr;
    }

    public void setVersion(int version) {
        this.version = version;
    }

    public void setNo(int no) {
        this.no = no;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public void setCommand(int command) {
        this.command = command;
    }

    public void setText(String text) {
        this.text = text;
    }

    public void setAddr(InetAddress addr) {
        this.addr = addr;
    }
}
