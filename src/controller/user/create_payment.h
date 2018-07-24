#ifndef CONTROLLER_CREATE_PAYMENT_H
#define CONTROLLER_CREATE_PAYMENT_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace controller {

/**
* @brief create_payment	: create json for create_payment of user database
* functions
* @param rep			: reply of http
* @param request		: request of http
*/
void create_payment(http::server::reply &rep, http::server::request request);

} // controller
} // dbaas
#endif // CONTROLLER_CREATE_PAYMENT_H
