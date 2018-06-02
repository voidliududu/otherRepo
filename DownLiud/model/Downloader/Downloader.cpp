//
// Created by liududu on 17-9-30.
//

#include "../../include/Downloader.h"

Downloader::Downloader(const Url& resourceUrl) {
    this->url = Url(resourceUrl);
}

/*
 * @param Url
 * @throw ProtocolException
 * */
Downloader* Downloader::getInstance(Url &resourceUrl) throw(ProtocolException) {
    string& protocol = resourceUrl.getProtocol();
    if(protocol == "http:"){
        //return new HttpDownloader(resourceUrl);
    }else if(protocol == "ftp:"){
        //return new FtpDownloader(resourceUrl);
    }else{
        throw ProtocolException();
    }
}