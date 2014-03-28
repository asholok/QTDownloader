#include "downloader.h"

Downloader::Downloader(QString strUrl, QObject *parent) :
    QObject(parent){
    QUrl url = QUrl::fromUserInput(strUrl);

    manager = new QNetworkAccessManager();
    fileName = QFileInfo(strUrl).fileName();
    reply = manager->get(QNetworkRequest(url));
    target = new QFile(QDir::homePath()+"/"+fileName);

    qDebug() << QDir::homePath()+"/"+fileName << " downloading.";
    connect(reply, SIGNAL(readyRead()), this, SLOT(isAvailable()));
    //connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress()));
    connect(reply, SIGNAL(finished()), this, SLOT(downliading()));

}

Downloader::~Downloader(){
    reply->deleteLater();
    target->close();
    manager->deleteLater();
}

void Downloader::downliading(){
    if ( !target->open(QIODevice::WriteOnly) ) {
        qDebug() << fileName << " unavailable.";
    } else {
        QByteArray content = reply->readAll();
        target->write(content);
        qDebug() << fileName << " successfully downloaded.";
    }
}

void Downloader::isAvailable() {
    qDebug() << " download.";
    if ( reply->error() ) {
        qDebug() << fileName << " download faild.";
    }
}

//void Downloader::downloadProgress(){
//    qDebug() <<
//}
