#ifndef CONTROLLER_DELETE_USER_KEYS_H
#define CONTROLLER_DELETE_USER_KEYS_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {
/**
* @brief delete_user_keys	: create json for delete_user_keys of user
* database functions
* @param rep			: reply of http
* @param request		: request of http
*/
void delete_user_keys(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas
#endif // CONTROLLER_DELETE_USER_KEYS_H
