package cn.liududu.liuchat.view;

import cn.liududu.liuchat.common.Theme;

import javax.swing.*;
import java.awt.*;
import java.util.Date;

public class ChatFrame extends JPanel {
    private MessageWindow mw;
    private TextBar tb;

    public ChatFrame() {
        mw = new MessageWindow();
        mw.setBackground(Color.decode(Theme.ChatFrameBackgroundColor));
//        mw.addMessage(new MessageBox("void","hello",new Date()));
        tb = TextBar.getInstance();
        tb.setBackground(Color.decode(Theme.ChatFrameBackgroundColor));
        this.setLayout(new BorderLayout());
        this.setBackground(Color.decode(Theme.ChatFrameBackgroundColor));
        this.add(mw,"North");
        this.add(tb,"South");
    }

    public MessageWindow getMw() {
        return mw;
    }

    public TextBar getTb() {
        return tb;
    }
}

