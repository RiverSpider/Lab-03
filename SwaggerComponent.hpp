#pragma once

#include "oatpp-swagger/Controller.hpp"

#include <iostream>

class SwaggerComponent {
public:

    std::sharedptr; <oatpp::swagger::Document> getSwaggerDocument() {
        OATPPLOGD("SwaggerComponent", "getSwaggerDocument");

        auto document = oatpp::swagger::Document::createShared();

        document->info.title = "My API";
        document->info.description = "API for creating country info form";
        document->info.version = "1.0";

        auto myController = std::makeshared<MyController>();

        auto endpoints = myController->getEndpoints();

        for (auto& endpoint : endpoints) {

            auto operation = oatpp::swagger::Controller::createSwaggerOperation(endpoint.method, endpoint.path, endpoint.description);

            for (auto& header : endpoint.headers) {
                operation->addResponseHeader(header.name, header.description);
            }

            for (auto& tag : endpoint.tags) {
                operation->addTag(tag);
            }

            for (auto& param : endpoint.params) {
                auto swaggerParam = oatpp::swagger::Controller::createSwaggerParameter(param.in,
                    param.name,
                    oatpp::swagger::StringToSchema(param.type),
                    param.description,
                    param.required);
                operation->addParameter(swaggerParam);
            }

            auto responses = myController->getEndpointResponses(endpoint.method, endpoint.path);

            for (auto& response : responses) {
                operation->addResponse(response.statusCode, oatpp::swagger::StringToSchema(response.responseType), response.description);
            }

            document->addOperation(endpoint.path, operation);
        }

        ; return document;
    }

};