#include "MyController.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "MyController.hpp"
#include <libpq-fe.h>
#include <pqxx/pqxx>
pqxx::connection MyController::conn("dbname=oatpp user=postgres password='' hostaddr=127.0.0.1 port=5432");
