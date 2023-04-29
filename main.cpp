#include "oatpp/network/Server.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "MyController.hpp"
#include "SwaggerComponent.hpp"

void run() {

	oatpp::base::Environment::init();

	auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

	auto router = oatpp::web::server::HttpRouter::createShared();

	auto myController = std::makeshared<MyController>(objectMapper);
	myController->addEndpointsToRouter(router);
	auto swaggerComponent = std::make_shared<SwaggerComponent>();

	oatpp::swagger::Controller::addEndpointsToRouter(router);

	oatpp::network::Address address("tcp://0.0.0.0:8000");
	auto server = oatpp::network::Server::createShared(router, 1);

	pqxx::connection conn("dbname=mydb user=postgres password=1234 hostaddr=127.0.0.1 port=5432");

	server->run();
	oatpp::base::Environment::destroy();
}