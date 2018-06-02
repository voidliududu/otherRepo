package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.base.IpMsgLayer;
import cn.liududu.liuchat.entity.User;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class WindowWatcher extends WindowAdapter {
    @Override
    public void windowClosing(WindowEvent windowEvent) {
        super.windowClosing(windowEvent);
        IpMsgLayer.getInstance().getPh().sendOfflineRequest(User.getCurrentUser());
    }
}
