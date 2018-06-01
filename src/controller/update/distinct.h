#ifndef DISTINCT_H
#define DISTINCT_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {
/**
* @brief distinct	:  <a href =
* "https://docs.mongodb.com/manual/reference/method/db.collection.distinct/">
* distinct mongodb <a>
* @param rep			: reply of http
* @param request		: request of http
*/
void distinct(http::server::reply &rep, http::server::request request);
} // dbaas
} // core

#endif // DISTINCT_H
