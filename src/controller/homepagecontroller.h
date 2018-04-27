#ifndef CONTROLLER_HOMEPAGECONTROLLER_H
#define CONTROLLER_HOMEPAGECONTROLLER_H

#include "src/server/reply.hpp"
#include <string>

namespace iotdb {
namespace core {

class homePageController {
  public:
	homePageController(http::server::reply &rep, std::string params);
};
}
}
#endif // CONTROLLER_HOMEPAGECONTROLLER_H
