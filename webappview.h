#ifndef WEBAPPVIEW_H
#define WEBAPPVIEW_H

#include <QMainWindow>
#include <QtWebKit/QWebView>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class WebAppView : public QWebView
{
    Q_OBJECT
    
public:
    WebAppView(QWidget *parent = 0);
    ~WebAppView();

public slots:
    void LoadJson();
    void LoadApplication();
    void onPageLoad(bool);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl jsonUrl;
};

#endif // WEBAPPVIEW_H
