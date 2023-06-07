#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

#include <configuration.h>
#include <DataBase.h>
#include <memory>

enum class Mode{NONE=0, ALL_CAMS=1, DETECTION=2, DETECTION_STOP=3};

using namespace std;

class Global
{
    Global() {}
    Global(Global const&) = delete;
    void operator=(Global const&) = delete;

    shared_ptr<DataBase> db;
    vector<shared_ptr<Configuration>> listConfiguration;
public:
    static Global &getInstance()
    {
        static Global instance;
        return instance;
    }
    shared_ptr<DataBase> getDataBase() {return db;}
    void setDataBase(string url, string username, string password);

    const vector<shared_ptr<Configuration> > &getListConfiguration() const;
    void setListConfiguration(const vector<shared_ptr<Configuration> > &newListConfiguration);
    Mode mode = Mode::NONE;
};

#endif // GLOBAL_H
