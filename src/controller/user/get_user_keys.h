#ifndef CONTROLLER_GET_USER_KEYS_H
#define CONTROLLER_GET_USER_KEYS_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {

/**
* @brief get_user_keys	: create json for get_user_keys of user database
* functions
* @param rep			: reply of http
* @param request		: request of http
*/
void get_user_keys(http::server::reply &rep, http::server::request request);
} // controller
} // dbaas

#endif // CONTROLLER_GET_USER_KEYS_H
