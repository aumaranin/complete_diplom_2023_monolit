#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

#include <configuration.h>
#include <DataBase.h>


using namespace std;

class Global
{
    Global() {}
    Global(Global const&) = delete;
    void operator=(Global const&) = delete;

    DataBase *db;
    Configuration *configuration;
public:
    static Global &getInstance()
    {
        static Global instance;
        return instance;
    }

    Configuration* getConfiguration() {return configuration;}
    void setConfiguration(Configuration *configuration) {this->configuration = configuration;}
    DataBase* getDataBase() {return db;}
    void setDataBase(string url, string username, string password);
};

#endif // GLOBAL_H
