#ifndef CONTROLLER_FIND_ONE_CONTROLLER_H
#define CONTROLLER_FIND_ONE_CONTROLLER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief find_one	: gets request content json and prepare it for
* find_one function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void find_one(http::server::reply &rep, http::server::request request);
} // core
} // dbaas
#endif // CONTROLLER_FIND_ONE_CONTROLLER_H
