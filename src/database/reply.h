#ifndef REPLY_H
#define REPLY_H
#include <string>

namespace dbaas {
namespace database {
namespace reply {
/**
* @brief not_found
* @return
*/
std::string error(std::string what);
std::string answer(std::string answer);
std::string answer_done();
}
}
}
#endif // REPLY_H
