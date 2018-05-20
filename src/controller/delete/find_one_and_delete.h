#ifndef FIND_AND_DELETE_ONE_H
#define FIND_AND_DELETE_ONE_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {

void find_one_and_delete(http::server::reply &rep,
			 http::server::request request);
}
}

#endif // CONTROLLER_FIND_AND_DELETE_ONE_H
