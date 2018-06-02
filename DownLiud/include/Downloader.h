//
// Created by liududu on 17-9-30.
//

#ifndef DOWNLIUD_DOWNLOADER_H
#define DOWNLIUD_DOWNLOADER_H


#include "Url.h"

class Downloader {
protected:
    Url url;

public:
    Downloader(const Url&);
    static Downloader* getInstance(Url&) throw(ProtocolException);
    virtual string download() = 0;
};

#endif //DOWNLIUD_DOWNLOADER_H
