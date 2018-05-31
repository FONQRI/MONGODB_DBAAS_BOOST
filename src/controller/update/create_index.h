#ifndef CONTROLLER_CREATE_INDEX_H
#define CONTROLLER_CREATE_INDEX_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {

void create_index(http::server::reply &rep, http::server::request request);

} // dbaas
} // core
#endif // CONTROLLER_CREATE_INDEX_H
