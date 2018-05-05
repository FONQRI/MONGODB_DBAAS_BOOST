#ifndef CONTROLLER_REQUEST_HANDLER_H
#define CONTROLLER_REQUEST_HANDLER_H

#include "src/server/reply.hpp"
#include "src/server/request.hpp"

#include <string>

namespace dbaas {
namespace core {

class handler {
  public:
	handler(http::server::request request, http::server::reply &rep);

  private:
};
}
}
#endif // CONTROLLER_REQUEST_HANDLER_H
