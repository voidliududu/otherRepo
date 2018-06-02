package cn.liududu.liuchat.base;


import cn.liududu.liuchat.common.Config;
import cn.liududu.liuchat.listener.FileTransferRequest;

import java.io.*;

import java.net.InetSocketAddress;
import java.net.ServerSocket;

import java.net.Socket;


public class FileTransferService extends Thread{
    public static final boolean SERVER = true;
    public static final boolean CLIENT = false;
    private SendFileClient sfc;
    private SendFileServer sfs;
    private String serverip;
    private File file;
    private String fileName;
    private boolean toggle;

    public FileTransferService() {
//        sfc = new SendFileClient();
//        sfs = new SendFileServer();
    }

    @Override
    public void run() {
        if (toggle) {
            createServer(file);
        } else {
            createClient();
        }
    }

    public void setService(boolean service) {
        toggle = service;
    }

    public void createClient() {
        new SendFileClient(serverip,fileName).start();
    }

    public void createServer(File file) {
            SendFileServer.server(file);
    }

    public void setFile(File file) {
        this.file = file;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public void setServerip(String ip) {
        serverip = ip;
    }



    public FileTransferService(File file) {
        this.file = file;
    }

    public SendFileServer getFileServer() {
        return sfs;
    }

    public SendFileClient getFileClient() {
        return sfc;
    }

}

