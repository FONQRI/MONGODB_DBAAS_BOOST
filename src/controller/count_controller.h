#ifndef CONTROLLER_COUNT_CONTROLLER_H
#define CONTROLLER_COUNT_CONTROLLER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"
#include <string>

namespace dbaas {
namespace core {

class count_controller {
  public:
	count_controller(http::server::reply &rep, http::server::request request);
};
}
}
#endif // CONTROLLER_COUNT_CONTROLLER_H
