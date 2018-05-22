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
class password {

  public:
	/**
	 * @brief create_key	: create key for user to access special database
	 * and
	 * specify limitation of requests
	 * @param username		: get username for create key workaround it
	 * should
	 * get
	 * name of key and generate a key
	 * @return				: gnerated key
	 */
	// TODO [2] get a name for key
	// TODO [2] create a struct for key
	// TODO [2] save keys into database
	static std::string create_key(std::string username);

	/**
	 * @brief check_key	: check key for limitation of request numbers and
	 * database name [working]
	 * @param key		: user key
	 * @return			: name of database
	 */
	/* TODO [2] check key check key for limitation of request numbers and
	 database name*/
	static std::string check_key(std::string key);

  private:
	password();

	// map for keys and database name
	// TODO [2] create a full mapping system that read from database
	static std::map<std::string, std::string> key_mapper;
};
} // dbaas
} // database
#endif // DATABASE_PASSWORD_H
