#ifndef CONTROLLER_CREATE_USER_H
#define CONTROLLER_CREATE_USER_H
#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {
/**
* @brief create_user	: create json for create_user of user database functions
* @param rep			: reply of http
* @param request		: request of http
*/
void create_user(http::server::reply &rep, http::server::request request);
} // controller
} // dbaas

#endif // CONTROLLER_CREATE_USER_H
