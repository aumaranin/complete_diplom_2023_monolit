#include "global.h"

const vector<shared_ptr<Configuration> > &Global::getListConfiguration() const
{
    return listConfiguration;
}

void Global::setListConfiguration(const vector<shared_ptr<Configuration> > &newListConfiguration)
{
    listConfiguration = newListConfiguration;
}

void Global::setDataBase(string url, string username, string password)
{
    std::string dbName = "ExpertSystem";
    if (Global::getInstance().db != nullptr)
        Global::getInstance().db->connect(url, username, password, dbName);
    else
        db = make_shared<Mongodb>(url, username, password, dbName);
}
