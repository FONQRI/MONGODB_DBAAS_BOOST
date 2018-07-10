#ifndef DATABASE_PASSWORD_H
#define DATABASE_PASSWORD_H

#include <map>
#include <string>

namespace dbaas {
namespace database {
/**
* @brief The password class : create key and ckeck access to system by key
* @author b.sabaghi
* @version 0.9 12/5/2018
*
*/
namespace password {

/* TODO [2] check key check key for limitation of request numbers and
 database name*/

bool m_check_key(std::string key, std::string &reply,
		 std::string function_name);
#define check_key(x, y) m_check_key(x, y, __FUNCTION__)
};
} // dbaas
} // database
#endif // DATABASE_PASSWORD_H
