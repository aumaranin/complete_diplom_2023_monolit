#include "operatorstackedwindow.h"
#include "global.h"
#include "DataBase.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    using namespace std;
    QApplication a(argc, argv);
    string url = R"(mongodb://localhost:27017)";
    Global::getInstance().setDataBase(url, "", "");
    OperatorStackedWindow w;
    w.show();
    return a.exec();
}
