#include "webappview.h"

#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QWebSettings>
//#include <QtWebkit/QWebSettings>

#include <QApplication>

#include <stdlib.h>

#include <qjson/parser.h>

#include <QVariant>
#include <QThread>

#include <iostream>

WebAppView::WebAppView(QWidget *parent)
    : QWebView(parent)
{
    reply = NULL;
    manager = new QNetworkAccessManager;
    if(QApplication::argc() < 2)
    {
        this->load(QString("https://marketplace.firefox.com/"));
    }
    else
    {
        jsonUrl = QApplication::arguments()[1];
        LoadJson();
    }
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(onPageLoad(bool)));
    QWebSettings::enablePersistentStorage();
    QWebSettings::globalSettings()->setAttribute(QWebSettings::WebGLEnabled,true);
}

WebAppView::~WebAppView()
{
    
}

void WebAppView::LoadJson()
{
    std::cout << jsonUrl.toString().toStdString().c_str() << std::endl;
    if(reply != NULL)
        disconnect(reply,SIGNAL(finished()),this,SLOT(LoadApplication()));
    reply = manager->get(QNetworkRequest(jsonUrl));
    if(reply->error() != QNetworkReply::NoError)
        return;
    std::cout << "Requested" << std::endl;
    connect(reply,SIGNAL(finished()),this,SLOT(LoadApplication()));
}

void WebAppView::LoadApplication()
{
    QString json = reply->readAll();
    std::cout << json.toStdString().c_str() << std::endl;

    QJson::Parser *parser = new QJson::Parser;
    bool ok;
    QVariantMap result = parser->parse (json.toAscii(), &ok).toMap();
    if(!ok)
    {
        reply->deleteLater();
        reply = NULL;
        load(jsonUrl);
        return;
    }
    if(result["launch_path"].toString() == "")
    {
        QUrl appUrl = QUrl(jsonUrl);
        appUrl.setPath(appUrl.path().remove(appUrl.path().lastIndexOf("/")+1,appUrl.path().length()-appUrl.path().lastIndexOf("/")));
        this->load(appUrl);
    }
    else if(result["launch_path"].toString().startsWith("http",Qt::CaseInsensitive))
    {
        this->load(result["launch_path"].toString());
    }
    else
    {
        QUrl appUrl = QUrl(jsonUrl);
        appUrl.setPath(appUrl.path().remove(appUrl.path().lastIndexOf("/")+1,appUrl.path().length()-appUrl.path().lastIndexOf("/"))+result["launch_path"].toString());
        this->load(appUrl);
    }
    reply->deleteLater();
    reply = NULL;
}

void WebAppView::onPageLoad(bool ok)
{
    if(ok)
    {
        this->page()->mainFrame()->addToJavaScriptWindowObject("AppView",this);
        this->page()->mainFrame()->evaluateJavaScript(
                    ""
                    );
    }
}
