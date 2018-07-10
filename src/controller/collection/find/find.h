#ifndef CONTROLLER_FIND_H
#define CONTROLLER_FIND_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief find	: gets request content json and prepare it for
* find function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void find(http::server::reply &rep, http::server::request request);
} // core
} // dbaas
#endif // CONTROLLER_FIND_H
