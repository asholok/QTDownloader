#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT

private:
    QString fileName;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QFile* target;

public:
    Downloader(QString strUrl, QObject *parent = 0);
    ~Downloader();
    
public slots:
    void downliading();
    void isAvailable();
    //void downloadProgress();

};

#endif // DOWNLOADER_H
