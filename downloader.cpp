#include "downloader.h"

Downloader::Downloader(QString strUrl, QObject *parent) :
    QObject(parent){
    QUrl url = QUrl::fromUserInput(strUrl);

    manager = new QNetworkAccessManager();
    fileName = QFileInfo(strUrl).fileName();
    reply = manager->get(QNetworkRequest(url));

    qDebug() << QDir::homePath()+"/"+fileName << " downloading.";
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downliading()));
}

Downloader::~Downloader(){
    reply->deleteLater();
    manager->deleteLater();
}

void Downloader::downliading(){
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray content = reply->readAll();

    if ( code >= 200 && code <= 300 ) {
        QFile* target = new QFile(QDir::homePath()+"/"+fileName);

        target->open(QIODevice::WriteOnly);
        target->write(content);
        target->close();
        qDebug() << fileName << " successfully downloaded.";
    } else {
        qDebug() << fileName << " unavailable! Error: " << code;
    }
    QCoreApplication::instance()->quit();
}

void Downloader::downloadProgress(qint64 recieved, qint64 total){
    if ( recieved == total ) {
        std::cout << "\r Recived " << int(double(recieved)/total*100) << " %\n";
    } else {
        std::cout << "\r Recived " << int(double(recieved)/total*100) << " %";
    }
}
