#ifndef CONTROLLER_COUNT_H
#define CONTROLLER_COUNT_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief count	: gets request content json and prepare it for
* count function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void count(http::server::reply &rep, http::server::request request);
} // core
} // dbaas
#endif // CONTROLLER_COUNT_H
