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
#include <QStringList>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT

private:
    QString fileName;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;

public:
    Downloader(QString strUrl, QObject *parent = 0);
    ~Downloader();
    
public slots:
    void downliading();
    void downloadProgress(qint64 recieved, qint64 total);

};

#endif // DOWNLOADER_H
