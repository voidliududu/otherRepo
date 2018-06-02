package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.Message;
import cn.liududu.liuchat.view.ContactsItem;
import cn.liududu.liuchat.view.MainWindow;
import cn.liududu.liuchat.view.MessageBox;

public class MessageListener {

    public void groupMessageCome(Message message) {
        MainWindow mv =  MainWindow.getInstance();
        mv.getContacts().findItemByIp(Config.broadcastGroup).setState(ContactsItem.NOTIFY);
        mv.getChatFrame().getMw().getMessageBoard(Config.broadcastGroup).addMessage(new MessageBox(message,false));
    }

    public void messageCome(Message message) {
        MainWindow mv =  MainWindow.getInstance();
        Logger.log("消息内容" + message.getText());
        Logger.log("消息地址" + message.getAddress());
        mv.getContacts().findItemByIp(message.getAddress()).setState(ContactsItem.NOTIFY);
        mv.getChatFrame().getMw().getMessageBoard(message.getAddress()).addMessage(new MessageBox(message,false));
    }
}
