#ifndef FIND_AND_DELETE_ONE_H
#define FIND_AND_DELETE_ONE_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {
/**
* @brief find_one_and_delete	: gets request content json and prepare it for
* find_one_and_delete function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void find_one_and_delete(http::server::reply &rep,
			 http::server::request request);
} // core
} // dbaas

#endif // CONTROLLER_FIND_AND_DELETE_ONE_H
