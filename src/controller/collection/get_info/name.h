#ifndef CONTROLLER_NAME_H
#define CONTROLLER_NAME_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief name	: gets request name of collection
* @param rep			: reply of http
* @param request		: request of http
*/
void name(http::server::reply &rep, http::server::request request);

} // core
} // dbaas
#endif // CONTROLLER_NAME_H
