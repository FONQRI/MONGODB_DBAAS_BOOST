#ifndef CONTROLLER_FIND_CONTROLLER_H
#define CONTROLLER_FIND_CONTROLLER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {

class find_controller {
  public:
	find_controller(http::server::reply &rep, http::server::request request);
};
}
}
#endif // CONTROLLER_FIND_CONTROLLER_H
