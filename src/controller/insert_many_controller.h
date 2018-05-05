#ifndef CONTROLLER_INSERT_MANY_CONTROLLER_H
#define CONTROLLER_INSERT_MANY_CONTROLLER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>
namespace dbaas {
namespace core {

class insert_many_controller {
  public:
	insert_many_controller(http::server::reply &rep,
			   http::server::request request);
};
}
}
#endif // CONTROLLER_INSERT_MANY_CONTROLLER_H
