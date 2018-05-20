#ifndef CONTROLLER_COUNT_H
#define CONTROLLER_COUNT_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {

void count(http::server::reply &rep, http::server::request request);
}
}
#endif // CONTROLLER_COUNT_H
