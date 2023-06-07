#include "global.h"

void Global::setDataBase(string url, string username, string password)
{
    std::string dbName = "ExpertSystem";
    if (Global::getInstance().db != nullptr)
        Global::getInstance().db->connect(url, username, password, dbName);
    else
        db = new Mongodb(url, username, password, dbName);
}
