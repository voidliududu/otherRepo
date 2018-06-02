package cn.liududu.liuchat.base;

import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.common.Logger;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

class SendFileClient extends Thread{
    private static  String SERVERIP = "127.0.0.1";
    private static final int SERVERPORT = Config.fileTransferPort;
    private static final int CLIENTPORT = Config.fileClientPort;
    private String fileName;

    public SendFileClient(String serverIp,String fileName) {
        this.fileName = fileName;
        SERVERIP = serverIp;
    }


    @Override
    public  void run() {

        //TODO Auto-generated method stub
        //用来接受传输过来的字符
        byte[] buf = new byte[100];
        Socket s = new Socket();
        try{
            //建立连接
            s.connect(new InetSocketAddress(SERVERIP,SERVERPORT));
            InputStream is = s.getInputStream();
//            //接收传输来的文件名
//            int len = is.read(buf);
//            String fileName = new String(buf,0,len);
            System.out.println("文件名：" + fileName);
            //接收传输来的文件
            Logger.log(Config.fileSaveLocation + fileName);
            FileOutputStream fos = new FileOutputStream(Config.fileSaveLocation + fileName);
            int data;
            while(-1!=(data= is.read()))
            {
                System.out.println(data);
                fos.write(data);
            }
            is.close();
            s.close();
        }catch (IOException e) {
            //TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
