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
