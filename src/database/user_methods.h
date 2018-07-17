#ifndef DATABASE_USER_METHODS_H
#define DATABASE_USER_METHODS_H

// mongo includes
#include <bsoncxx/array/element.hpp>
#include <bsoncxx/array/value.hpp>
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/array/view_or_value.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/model/insert_one.hpp>
#include <mongocxx/options/count.hpp>
#include <mongocxx/result/insert_one.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

// boost
#include <boost/optional.hpp>

// typedefs
typedef boost::optional<bool> optional_bool;
typedef boost::optional<bsoncxx::types::b_document> optional_ducument;
typedef boost::optional<std::string> optional_string;
typedef boost::optional<std::vector<std::string>> optional_string_array;
typedef boost::optional<int> optional_int;
typedef boost::optional<size_t> optional_size;

namespace dbaas {
namespace database {

/**
* @brief create_user			: create a user in database
* @param username				: unique username
* @param password				: user password
* @param primary_phone_number	: primary phone number for saving user in
* database
* @param primary_email			: primary email for saving user in
* database
* @param phone_numbers			: optional phone numbers array
* @param emails					: optional emails array
* @return						: json that if creation
* was
* successful or not
*/
std::string create_user(std::string username, std::string password,
			std::string primary_phone_number,
			std::string primary_email,
			optional_string_array phone_numbers,
			optional_string_array emails);

/**
 * @brief update_user			: update user in datanase
 * @param username				: unique username
 * @param password				: user password
 * @param update_username		: optional password if there is change
 * @param update_password		: optional password if there is change
 * @param primary_phone_number	: optional primary phone number for saving
 * user in database
 * @param primary_email			: optional primary email for saving user
 * in database
 * @param phone_numbers			: optional phone numbers array
 * @param emails				: optional emails array
 * @return 						: json that if update was successful
 * or
 * not
 */
std::string
update_user(std::string username, std::string password,
		optional_string update_username, optional_string update_password,
		optional_string primary_phone_number, optional_string primary_email,
		optional_string_array phone_numbers, optional_string_array emails);

/**
 * @brief get_user	: get user struct from database
 * @param username	: username for finding user
 * @param password	: password for checking access
 * @return			: user in json if there is such user and failed json
 * if
 * there is no such user
 */
std::string get_user(std::string username, std::string password);

/**
 * @brief delete_user	: deletes user if there is such user
 * @param username		: username of user
 * @param password		: password
 * @return				: delete was successful or not
 */
std::string delete_user(std::string username, std::string password);

/**
 * @brief create_key			: create a key of user to user for
 * requests
 * @param username				: username of user
 * @param password				: password of user
 * @param name					: name of key
 * @param valid_request_per_day	: valid request per day for this user
 * @param valid_read_size		: valid read size in kb
 * @param valid_write_size		: valid write size in kb
 * @param access				: access array that specifies key access
 * to
 * collections api functions
 * @return						: key creation was successful
 * or
 * not
 */
std::string create_key(std::string username, std::string password,
			   std::string name, std::string database_name,
			   int valid_request_per_day, int valid_read_size,
			   int valid_write_size, std::vector<std::string> access);

/**
 * @brief update_key			: update given properties in json
 * @param username				: username for finding user
 * @param password				: password for check access
 * @param name					: name of key
 * @param update_name			: optional new name for key if needs to
 * be
 * update
 * @param valid_request_per_day	: optional valid_request_per_day for key if
 * needs to be update
 * @param request_per_day		: optional request_per_day if needs to
 * be
 * update
 * @param valid_read_size		: optional valid_read_size if needs to
 * be
 * update
 * @param valid_write_size		: optional valid_write_size if needs to
 * be
 * update
 * @param access				: optional access array if needs to
 * be
 * update
 * @return 						: update was successful
 * or
 * not
 */
std::string
update_key(std::string username, std::string password, std::string name,
	   optional_string update_name, optional_string database_name,
	   optional_int valid_request_per_day, optional_int request_per_day,
	   optional_int valid_read_size, optional_int valid_write_size,
	   optional_string_array access);

/**
 * @brief get_user_key	: internal function user can not get access to key by
 * this function
 * @param username		: username for finding user
 * @param name			: name for finding key
 * @return				: users key
 */
std::string get_user_key(std::string username, std::string name);

/**
 * @brief get_user_keys	: get all keys of a user
 * @param username		: username of user
 * @param password		: password of user
 * @return				: all keys in json
 */
std::string get_user_keys(std::string username, std::string password);

/**
 * @brief delete_user_key	: delete a key of user
 * @param username			: username of user
 * @param password			: password of user
 * @param name				: name of key
 * @return 					: key in json
 */
std::string delete_user_key(std::string username, std::string password,
				std::string name);

/**
 * @brief delete_user_keys	: delete all keys of user
 * @param username			: username of user
 * @param password			: password of user
 * @return					: return all keys of user in
 * json
 */
std::string delete_user_keys(std::string username, std::string password);

/**
 * @brief create_payment			: create a payment
 * @param username					: username of user
 * @param password					: password of user
 * @param main_value				: main_value of payment
 * @param discount_value			: discount_value of payment
 * @param discount_type				: discount_type	of payment
 * @param expiration_time			: expiration_time of payment
 * @param request_numbers_per_day	: request_numbers_per_day of payment
 * @param read_size					: read_size of payment
 * @param write_size				: write_size of payment
 * @return 							: was successful
 * or
 * not
 */
std::string create_payment(std::string username, std::string password,
			   int main_value, optional_int discount_value,
			   optional_string discount_type, int expiration_time,
			   int request_numbers_per_day, int read_size,
			   int write_size);

/**
 * @brief get_payments	: get payment list
 * @param username		: username of user
 * @param password		: password of user
 * @return				: get all payments in json
 */
std::string get_payments(std::string username, std::string password);

} // dbaas
} // database

#endif // DATABASE_USER_METHODS_H
