package cn.liududu.liuchat.view;

import cn.liududu.liuchat.common.Theme;

import javax.swing.*;
import java.awt.*;

public class MessageBoard extends JPanel {
    private String id;
    private JScrollPane pcontainer;
    private JList<MessageBox> list;
    private DefaultListModel<MessageBox> listModel;

    public MessageBoard(String id) {
        super();

        this.id = id;
        listModel = new DefaultListModel<MessageBox>();
        list = new JList<>(listModel);
        list.setCellRenderer(new MessageRender());
        this.setBackground(Color.decode(Theme.ChatFrameBackgroundColor));
        pcontainer = new JScrollPane(list);
        pcontainer.setPreferredSize(new Dimension(600,400));
        this.add(pcontainer);
    }

    public void addMessage(MessageBox mb) {
        this.listModel.addElement(mb);
    }

    public String getId() {
        return id;
    }

}
class MessageRender implements ListCellRenderer<MessageBox> {
        @Override
        public Component getListCellRendererComponent(JList<? extends MessageBox> jList, MessageBox messageBox, int i, boolean b, boolean b1) {

            return messageBox;
        }
}
