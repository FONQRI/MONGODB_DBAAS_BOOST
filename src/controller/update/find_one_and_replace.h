#ifndef CONTROLLER_FIND_ONE_AND_REPLACE_H
#define CONTROLLER_FIND_ONE_AND_REPLACE_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>
namespace dbaas {
namespace core {

void find_one_and_replace(http::server::reply &rep,
			  http::server::request request);
}
}

#endif // CONTROLLER_FIND_ONE_AND_REPLACE_H
