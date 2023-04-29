#pragma once

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "MyController.hpp"
#include <libpq-fe.h>
#include <pqxx/pqxx>
#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController : public oatpp::web::server::api::ApiController {
public:

    MyController(const std::shared_ptr<ObjectMapper>& objectMapper)
        : oatpp::web::server::api::ApiController(objectMapper)
    {}

    ENDPOINT("GET", "/", root) {
        return createResponse(Status::CODE_200, "text/html", getRootHtml());
    }

    ENDPOINT("POST", "/country", createCountry,
        BODY_STRING(String, body)) {

        auto dto = MyDto::createShared();
        oatpp::parser::json::mapping::ObjectMapper::parseJson(body, dto);

        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "INSERT INTO yname (name, capital, population, gdp, leader, currency) "
            "VALUES ($1, $2, $3, $4, $5, $6)",
            dto->getCountry(),
            dto->getCapital(),
            dto->getPopulation(),
            dto->getGdp(),
            dto->getLeader(),
            dto->getCurrency()
        );

        txn.commit();

        return createResponse(Status::CODE_200, "text/plain", "Data saved to PostgreSQL");
    }

    ENDPOINT("GET", "/countries", getCountries) {
        try {
            pqxx::work txn(conn);

            pqxx::result res = txn.exec("SELECT name, capital, population, gdp, leader, currency FROM uname");

            oatpp::data::stream::ChunkedBuffer buffer;

            for (auto row : res) {
                buffer.write("");
                buffer.write("Страна: " + row[0].c_str());
                buffer.write("");
                buffer.write("Столица: " + row[1].c_str());
                buffer.write("");
                buffer.write("Население: " + std::to_string(row[2].as<int>()));
                buffer.write("");
                buffer.write("ВВП: " + std::to_string(row[3].as<double>()));
                buffer.write("");
                buffer.write("Лидер: " + row[4].c_str());
                buffer.write("");
                buffer.write("Валюта: " + row[5].c_str());
                buffer.write("");
            }
        }
        catch (err) {
            return createResponse(Status::CODE_200, "Таблицы не существует", buffer.toString());
        }
    }

    ENDPOINT("GET", "/edit", getCountries) {
        try {
            pqxx::work txn(conn);

            pqxx::result res = txn.exec("UPDATE uname SET type = 'edit' WHERE name = 'country'");

            oatpp::data::stream::ChunkedBuffer buffer;
    }

    ENDPOINT("GET", "/delete", getCountries) {
            pqxx::work txn(conn);

            pqxx::result res = txn.exec("DELETE FROM uname WHERE name = 'country'");
            oatpp::data::stream::ChunkedBuffer buffer;
    }

private:

    static pqxx::connection conn;

    oatpp::String getRootHtml() {
        std::ifstream inFile("index.html");
        std::stringstream strStream;
        strStream << inFile.rdbuf();
        return strStream.str().c_str();
    }

};
#include OATPP_CODEGEN_END(ApiController)