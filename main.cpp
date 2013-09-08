#include "webappview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Anthon Web App Runner ( Like Firefox OS or iPad )");
    a.setApplicationVersion("1.0");
    WebAppView w;
    w.show();
    
    return a.exec();
}
