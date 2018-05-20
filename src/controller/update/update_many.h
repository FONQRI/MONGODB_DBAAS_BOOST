#ifndef CONTROLLER_UPDATE_MANY_H
#define CONTROLLER_UPDATE_MANY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>
namespace dbaas {
namespace core {

void update_many(http::server::reply &rep, http::server::request request);
}
}

#endif // CONTROLLER_UPDATE_MANY_H
