#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
void aggregate(http::server::reply &rep, http::server::request request);
} // dbaas
} // core
#endif // AGGREGATE_H
