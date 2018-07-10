#ifndef LIST_INDEXES_H
#define LIST_INDEXES_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {
/**
* @brief list_indexes	: gets list of indexes of collection
* @param rep          : reply of http
* @param request      : request of http
*/
void list_indexes(http::server::reply &rep, http::server::request request);
} // core
} // dbaas

#endif // LIST_INDEXES_H
