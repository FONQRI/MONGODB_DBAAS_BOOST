#ifndef CONTROLLER_UPDATE_USER_H
#define CONTROLLER_UPDATE_USER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {

/**
* @brief update_user: create json for update_user of user database functions
* @param rep		: reply of http
* @param request	: request of http
*/
void update_user(http::server::reply &rep, http::server::request request);

} // core
} // dbaas

#endif // CONTROLLER_UPDATE_USER_H
