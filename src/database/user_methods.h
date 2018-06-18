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

std::string create_user(std::string username, std::string password,
			std::string primary_phone_number,
			std::string primary_email,
			std::vector<std::string> phone_numbers,
			std::vector<std::string> emails);

std::string update_user(std::string username, std::string password,
			std::vector<std::string> phone_numbers,
			std::vector<std::string> emails,
			std::string signup_date_time);

std::string get_user(std::string username, std::string password);

std::string delete_user(std::string username, std::string password);

std::string create_key(std::string username, std::string password,
			   std::string name, std::string valid_request_per_day,
			   int request_per_day, int read_size, int write_size,
			   std::vector<std::string> access);

std::string update_key(std::string username, std::string password,
			   optional_string name,
			   optional_string valid_request_per_day,
			   optional_size request_per_day, optional_size read_size,
			   optional_size write_size, optional_string_array access);

// internal function user can not get access to key by this function
std::string get_user_key(std::string username, std::string name);

std::string get_user_keys(std::string username, std::string password);

// delete a key of user
std::string delete_user_key(std::string username, std::string password,
				std::string name);

// delete all keys of user
std::string delete_user_keys(std::string username, std::string password);

// create a payment
std::string create_payment(std::string username, std::string password,
			   size_t main_value, size_t discount_value,
			   std::string discount_type, size_t time,
			   size_t expiration_time,
			   size_t request_numbers_per_day, size_t read_size,
			   size_t write_size);

// get payment list
std::string get_payments(std::string username, std::string password);

} // dbaas
} // database

#endif // DATABASE_USER_METHODS_H
