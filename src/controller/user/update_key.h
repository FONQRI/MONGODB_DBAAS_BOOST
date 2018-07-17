#ifndef CONTROLLER_UPDATE_KEY_H
#define CONTROLLER_UPDATE_KEY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {

/**
* @brief update_key		: create json for update_key of user database
* functions
* @param rep			: reply of http
* @param request		: request of http
*/
void update_key(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas

#endif // CONTROLLER_UPDATE_KEY_H
