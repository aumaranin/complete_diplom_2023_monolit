#include "DataBase.h"

using bsoncxx::builder::basic::kvp;

void Mongodb::connect(std::string url, std::string username, std::string password, std::string databaseName)
{
    this->url = url;
    this->username = username;
    this->password = password;
    this->databaseName = databaseName;
}

void Mongodb::writeConfiguration(std::string configurationName, std::string jsonStr)
{
    mongocxx::uri uri(getUrl());
    mongocxx::client client(uri);
    auto db = client[getDatabaseName()];

    auto collection = db[configurationName];
    collection.drop();

    auto bson = bsoncxx::from_json(jsonStr);
    auto result = collection.insert_one(bson.view());
}

std::string Mongodb::readConfiguration(std:: string configurationName)
{
    std::string jsonResult;
    mongocxx::uri uri(this->getUrl());
    mongocxx::client client(uri);
    auto db = client[getDatabaseName()];
    auto collection = db[configurationName];
    auto findResult = collection.find_one({});
    jsonResult = bsoncxx::to_json(findResult->view());
    return jsonResult;
}

void Mongodb::removeConfiguration(std::string configurationName)
{
    mongocxx::uri uri(getUrl());
    mongocxx::client client(uri);
    auto db = client[getDatabaseName()];
    auto collection = db[configurationName];
    collection.drop();
}

std::vector<std::string> Mongodb::getListConfigurationNames()
{
    mongocxx::uri uri(getUrl());
    mongocxx::client client(uri);
    auto db = client[getDatabaseName()];
    return db.list_collection_names();
}

std::vector<ReportFromDb> Mongodb::readAllReports()
{
    vector<ReportFromDb> listReports;

    mongocxx::uri uri(getUrl());
    mongocxx::client client(uri);
    auto db = client["reports"];
    auto collection = db["reports"];
    auto cursor_all = collection.find({});
    for (auto doc : cursor_all)
    {
        ReportFromDb newReport;
        std::string date(doc["date"].get_string().value);
        newReport.setDate(date);
        std::string configName(doc["configName"].get_string().value);
        newReport.setConfigName(configName);
        std::string zone(doc["zone"].get_string().value);
        newReport.setZone(zone);
        std::string object(doc["classObject"].get_string().value);
        newReport.setClassObject(object);
        std::string reason(doc["reason"].get_string().value);
        newReport.setReason(reason);
        listReports.push_back(newReport);
    }
    return listReports;
}

void Mongodb::writeReport(ReportFromDb report)
{
    mongocxx::uri uri(getUrl());
    mongocxx::client client(uri);
    auto db = client["reports"];
    auto collection = db["reports"];
    auto doc_value = bsoncxx::builder::basic::make_document(
                kvp("date", report.getDate()),
                kvp("configName", report.getConfigName()),
                kvp("zone", report.getZone()),
                kvp("classObject", report.getClassObject()),
                kvp("reason", report.getReason())
                );
    auto result = collection.insert_one(doc_value.view());
}
