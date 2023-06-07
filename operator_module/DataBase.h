#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <reportfromdb.h>


enum class DatabaseTypes{POSTGRESQL=0, MONGODB=1};

class DataBase
{    
protected:
    std::string url;
    std::string username;
    std::string password;
    std::string databaseName;
public:
    DataBase(std::string url, std::string username, std::string password, std::string databaseName) : url(url), username(username), password(password), databaseName(databaseName) {}
    std::string getUrl() {return url;}
    std::string getUsername() {return username;}
    std::string getPassword() {return password;}
    std::string getDatabaseName() {return databaseName;}
    virtual void connect(std::string url, std::string username, std::string password, std::string databaseName) = 0;
    virtual void writeConfiguration(std::string configurationName, std::string jsonStr) = 0;
    virtual std::string readConfiguration(std::string configurationName) = 0;
    virtual void removeConfiguration(std::string configurationName) = 0;
    virtual std::vector<std::string> getListConfigurationNames() = 0;

    virtual std::vector<ReportFromDb> readAllReports() = 0;
    virtual void writeReport(ReportFromDb report) = 0;
};

class Mongodb : public DataBase
{
    mongocxx::instance instance{};
public:
    Mongodb(std::string url, std::string username, std::string password, std::string databaseName) : DataBase(url, username, password, databaseName) {}
    Mongodb(const Mongodb& copy) = delete;
    virtual void connect(std::string url, std::string username, std::string password, std::string databaseName) override;
    virtual void writeConfiguration(std::string configurationName, std::string jsonStr) override;
    virtual std::string readConfiguration(std:: string configurationName) override;
    virtual void removeConfiguration(std::string configurationName) override;
    virtual std::vector<std::string> getListConfigurationNames() override;

    virtual std::vector<ReportFromDb> readAllReports() override;
    virtual void writeReport(ReportFromDb report) override;
};

#endif // DATABASE_H
