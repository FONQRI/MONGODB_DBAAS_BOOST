#ifndef CONTROLLER_DELETE_USER_KEY_H
#define CONTROLLER_DELETE_USER_KEY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {
/**
* @brief delete_user_key	: create json for delete_user_key of user
* database
* functions
* @param rep				: reply of http
* @param request			: request of http
*/
void delete_user_key(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas
#endif // CONTROLLER_DELETE_USER_KEY_H
