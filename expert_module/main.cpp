#include "configurationlistwindow.h"
#include "DataBase.h"
#include <QVariant>

#include <QApplication>
//#include <iostream>
#include "global.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigurationListWindow w;
    w.show();
    return a.exec();
}
