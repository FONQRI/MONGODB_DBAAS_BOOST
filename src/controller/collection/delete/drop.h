#ifndef CONTROLLER_DROP_H
#define CONTROLLER_DROP_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>
namespace dbaas {
namespace core {

/**
* @brief drop		: drop collection
* @param rep		: reply of http
* @param request	: request of http
*/
void drop(http::server::reply &rep, http::server::request request);

} // core
} // dbaas

#endif // CONTROLLER_DROP_H
