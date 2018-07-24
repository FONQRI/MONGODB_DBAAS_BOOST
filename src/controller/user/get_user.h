#ifndef CONTROLLER_GET_USER_H
#define CONTROLLER_GET_USER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {

/**
* @brief get_user	: create json for get_user of user database functions
* @param rep		: reply of http
* @param request	: request of http
*/
void get_user(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas
#endif // CONTROLLER_GET_USER_H
