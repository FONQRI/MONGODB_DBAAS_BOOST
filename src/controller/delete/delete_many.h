#ifndef CONTROLLER_DELETE_MANY_H
#define CONTROLLER_DELETE_MANY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {

void delete_many(http::server::reply &rep, http::server::request request);
}
}

#endif // CONTROLLER_DELETE_MANY_H
