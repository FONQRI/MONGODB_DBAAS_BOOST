#ifndef CONTROLLER_CREATE_USER_H
#define CONTROLLER_CREATE_USER_H
#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief create_user	: gets request content json and prepare it for
* create_user function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void create_user(http::server::reply &rep, http::server::request request);
} // core
} // dbaas

#endif // CONTROLLER_CREATE_USER_H
