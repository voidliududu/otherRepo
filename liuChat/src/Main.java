import cn.liududu.liuchat.base.BroadcastService;
import cn.liududu.liuchat.base.IpMsgLayer;
import cn.liududu.liuchat.base.UdpService;
import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;
import cn.liududu.liuchat.entity.User;
import cn.liududu.liuchat.view.MainWindow;

import javax.swing.*;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class Main {
    public static Main main;
    private MainWindow mainWindow;
    private IpMsgLayer ipMsgLayer;
    private User me;
    public static void main(String[] args) {
        System.out.println("Hello World!");
        Main.getInstance();
    }

    //todo 登录操作放哪里？
    public Main() {
        //启动广播服务
        BroadcastService bs = BroadcastService.getInstance();
        bs.start();
        //启动udp服务
        UdpService us = UdpService.getInstance();
        us.start();
        //获取用户信息并设置当前用户
        me = getUserInfo();
        User.setCurrentUser(me);

        //实例化ipMsg层
        ipMsgLayer = IpMsgLayer.getInstance(me,us,bs);

        //绘制窗口
        mainWindow = MainWindow.getInstance();

        Logger.log("发送存活请求");
        ipMsgLayer.login();
    }
    public static Main getInstance() {
        if (main != null) {
            return main;
        } else {
            main = new Main();
            return main;
        }
    }
    /**
    * 确认用户信息
    * fixme test
    * */
    private User getUserInfo() {
        try {
            String name =  JOptionPane.showInputDialog("请输入昵称");
            if (name == null || name.equals("")) {
                System.exit(0);
            }
            return new User(name, InetAddress.getByName(Config.serveHost));
        } catch (UnknownHostException e) {

        }
        return null;
    }
}
