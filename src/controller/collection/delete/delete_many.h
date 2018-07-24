#ifndef CONTROLLER_DELETE_MANY_H
#define CONTROLLER_DELETE_MANY_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace controller {
/**
* @brief delete_many	: gets request content json and prepare it for
* delete_many function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void delete_many(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas

#endif // CONTROLLER_DELETE_MANY_H
