#include "DataBase.h"

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
