package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.view.ContactsItem;
import cn.liududu.liuchat.view.MainWindow;
import cn.liududu.liuchat.view.MessageBoard;

public class UserListener {

    /*
    * 如果用户不在列表，不做操作，否则从列表删除,并删除对应消息窗
    *
    * */
    public void userExit(User user) {
        MainWindow mw = MainWindow.getInstance();
        if (mw.getContacts().findItemByIp(user.getIpAddr().toString().split("/")[1]) != null) {
            ContactsItem ci = new ContactsItem(user);
            mw.getContacts().removeContactsItem(ci);
//            MessageBoard mb = new MessageBoard(user.getIpAddr().toString());
            mw.getChatFrame().getMw().removeMessageBoard(user.getIpAddr().toString().split("/")[1]);
        }
    }

    /**
    * 如果用户在列表中，不做操作，否则加入列表，并创建对应消息窗
    *
    * */
    public void userEntry(User user) {
        MainWindow mw =  MainWindow.getInstance();
        if (mw.getContacts().findItemByIp(user.getIpAddr().toString().split("/")[1]) == null) {
            ContactsItem ci = new ContactsItem(user);
            mw.getContacts().addContactsItem(ci);
            MessageBoard mb = new MessageBoard(user.getIpAddr().toString().split("/")[1]);
            mw.getChatFrame().getMw().addMessageBoard(mb);
        }
    }
}
