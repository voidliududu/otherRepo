package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.base.IpMsgLayer;
import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.IpMsg;
import cn.liududu.liuchat.entity.Message;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.view.MainWindow;
import cn.liududu.liuchat.view.MessageBox;
import cn.liududu.liuchat.view.TextBar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class MessageSubmitListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        TextBar textBar = TextBar.getInstance();
        MainWindow mainWindow = MainWindow.getInstance();
        User receiver = mainWindow.getSessionUser();
        String text = textBar.getText();
        if (receiver == null) {
            IpMsgLayer.getInstance().getPh().sendAll(User.getCurrentUser(),text);
            textBar.clearText();
            Message msg =  new Message(User.getCurrentUser().getName(),User.getCurrentUser().getIpAddr().toString(),text);
            MainWindow mv =  MainWindow.getInstance();
            mv.getChatFrame().getMw().getMessageBoard(Config.broadcastGroup).addMessage(new MessageBox(msg,true));
        } else {
            IpMsgLayer.getInstance().getPh().sendMsg(User.getCurrentUser(),receiver,text);
            textBar.clearText();
            MainWindow mv =  MainWindow.getInstance();
            Message msg =  new Message(User.getCurrentUser().getName(),mv.getSessionUser().getIpAddr().toString(),text);
            Logger.log("消息地址 " + msg.getAddress());
            mv.getChatFrame().getMw().getMessageBoard(msg.getAddress().split("/")[1]).addMessage(new MessageBox(msg,true));
        }
    }
}
