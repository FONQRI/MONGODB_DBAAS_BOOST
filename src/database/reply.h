/**
* reply.h
* reply namespace contain reply functions to make json reply
* @author b.sabaghi
* @version 0.9 12/5/2018
*/

#ifndef REPLY_H
#define REPLY_H

#include <string>

namespace dbaas {
namespace database {
namespace reply {

/**
* @brief error
* @param code
* @param what
* @return
*/
std::string error(size_t code, std::string what);

/**
 * @brief enter_item_error	: create error reply json for missing item in
 * query
 * @param item_name			: missing item name
 * @return					: json of reply
 */
std::string missing_item_error(std::string item_name);

/**
 * @brief wrong_item_type	: create error reply json for wrong item in
 * query
 * @param item_name			: missing item name
 * @return					: json of reply
 */
std::string wrong_item_type(std::string item_name);
/**
 * @brief answer	: create answer reply json
 * @param answer	: answer message
 * @return			: json of reply
 */
std::string answer(std::string answer);

std::string answer_not_found(std::string answer);

/**
 * @brief answer_done	: write done answer
 * @return				: done reply sjon
 */
std::string answer_done();

/**
 * @brief access_denied : client_key access denied
 * @param why			: reason of access denied
 * @return				: json for answer
 */
std::string access_denied(std::string why);

/**
 * @brief client_key_not_found
 * @param client_key
 * @return						: json error
 */
std::string client_key_not_found(std::string client_key);

/**
 * @brief user_creation_failed
 * @param why
 * @return : json error
 */
std::string user_creation_failed(std::string why);

std::string user_update_failed(std::string why);

/**
 * @brief http_error
 * @param what
 * @return : json error
 */
std::string http_error(std::string what);

/**
 * @brief wrong_request_content_type
 * @param what
 * @return : json error
 */
std::string wrong_request_content_type(std::string what);

/**
 * @brief database_error
 * @param what
 * @return : json error
 */
std::string database_error(std::string what);

std::string duplicate_index(std::string what);

} // reply
} // dbaas
} // database
#endif // REPLY_H
