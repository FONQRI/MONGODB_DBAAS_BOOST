/**
  @link
  https://docs.mongodb.com/manual/reference/method/db.collection.deleteOne/#db.collection.deleteOne
  */

#ifndef CONTROLLER_DELETE_ONE_H
#define CONTROLLER_DELETE_ONE_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {
/**
* @brief delete_one	: gets request content json and prepare it for
* delete_one function in database namespace
* @param rep			: reply of http
* @param request		: request of http
*/
void delete_one(http::server::reply &rep, http::server::request request);
} // core
} // dbaas

#endif // CONTROLLER_DELETE_ONE_H
