#ifndef CONTROLLER_INSERT_MANY_H
#define CONTROLLER_INSERT_MANY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>
namespace dbaas {
namespace core {

void insert_many(http::server::reply &rep, http::server::request request);
}
}
#endif // CONTROLLER_INSERT_MANY_H
