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
* @brief error	: create error reply json
* @param what	: error message
* @return		: json of reply
*/
std::string error(std::string what);

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

/**
 * @brief answer_done	: write done answer
 * @return				: done reply sjon
 */
std::string answer_done();
} // reply
} // dbaas
} // database
#endif // REPLY_H
