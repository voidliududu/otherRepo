package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.Logger;
import org.junit.Test;

import java.io.File;
import java.net.InetAddress;
import java.net.UnknownHostException;

import static org.junit.Assert.*;

public class SendFileServerTest {
    @Test
    public void SendFile() {
        SendFileServer.server(new File("./resource/img/stadium.png"));
    }
    @Test
    public void getFile() {
        try {
            SendFileClient sfc = new SendFileClient(InetAddress.getLocalHost().toString().split("/")[1],"test.png");
            sfc.start();
        } catch (UnknownHostException e){
            Logger.log("未知主机名");
        }
    }
}