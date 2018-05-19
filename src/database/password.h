#ifndef DATABASE_PASSWORD_H
#define DATABASE_PASSWORD_H
#include <map>
#include <string>
/**
 * @brief The Device class
 *  Create key
 *  Check key
 *
 */

namespace dbaas {
namespace database {

class password {

  public:
	static std::string create_key(std::string username);
	static std::string check_key(std::string key);

  private:
	password();
	static std::map<std::string, std::string> key_mapper;
};
}
}
#endif // DATABASE_PASSWORD_H
