#ifndef CONTROLLER_GET_PAYMENTS_H
#define CONTROLLER_GET_PAYMENTS_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief get_payments	: create json for get_payments of user database
* functions
* @param rep			: reply of http
* @param request		: request of http
*/
void get_payments(http::server::reply &rep, http::server::request request);
} // core
} // dbaas

#endif // CONTROLLER_GET_PAYMENTS_H
