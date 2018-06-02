package cn.liududu.liuchat.common;

public class Config {
    public static final String serveHost = "192.168.43.169";
    public static final int udpPort = 6000;

    public static final int broadcastPort = 2334;
    public static final String broadcastGroup = "233.0.0.1";

    public static final int fileTransferPort = 2335;
    public static final int fileClientPort = 2336;
    public static final String fileSaveLocation = "./resource/file_recv/";

    public static final String defaultAvator = "";
    public static final int msgQueueSize = 10;
    public static final int maxDatagramPacketSize = 2048;
    public static final String groupName = "群聊";
}
