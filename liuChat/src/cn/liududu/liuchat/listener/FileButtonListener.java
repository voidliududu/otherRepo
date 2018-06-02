package cn.liududu.liuchat.listener;

import cn.liududu.liuchat.base.FileTransferService;
import cn.liududu.liuchat.base.IpMsgLayer;
import cn.liududu.liuchat.base.SendFileServer;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.IpMsg;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.view.MainWindow;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class FileButtonListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        JFileChooser jfc = new JFileChooser();
        int flag = jfc.showOpenDialog(MainWindow.getInstance());
        if (flag == JFileChooser.APPROVE_OPTION) {
            File file = jfc.getSelectedFile();
            IpMsgLayer.getInstance().getPh().fileTransferRequest(User.getCurrentUser(),MainWindow.getInstance().getSessionUser(),file);
            FileTransferService ftf = new FileTransferService();
            ftf.setService(FileTransferService.SERVER);
            ftf.setFile(file);
            Logger.log("启动文件传输服务");
            ftf.start();
        }
    }
}
