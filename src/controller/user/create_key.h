#ifndef CONTROLLER_CREATE_KEY_H
#define CONTROLLER_CREATE_KEY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {

/**
* @brief create_key	: create json for create_key of user database functions
* @param rep		: reply of http
* @param request	: request of http
*/
void create_key(http::server::reply &rep, http::server::request request);

} // core
} // dbaas
#endif // CONTROLLER_CREATE_KEY_H
