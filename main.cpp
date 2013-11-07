#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *unicode = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(unicode);
    QTranslator appTransl;
    appTransl.load(":/" + QLocale::system().name());
    a.installTranslator(&appTransl);
    MainWindow w;
    w.show();

    return a.exec();
}
