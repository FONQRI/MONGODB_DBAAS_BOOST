#include "user_methods.h"

// std
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "reply.h"

// mongocxx
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/stdx.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;

// TODO p[2] check duplicate kesy with error struct
std::string dbaas::database::create_user(std::string username,
					 std::string password,
					 std::string primary_phone_number,
					 std::string primary_email,
					 std::vector<std::string> phone_numbers,
					 std::vector<std::string> emails)
{
	// reply message
	std::string reply;

	// connect to database

	// create connection

	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document user_document{};
		// create new user
		user_document.append(kvp("username", username));
		user_document.append(kvp("password", password));
		user_document.append(
		kvp("primary_phone_number", primary_phone_number));
		user_document.append(kvp("primary_email", primary_email));

		user_document.append(
		kvp("phone_numbers", [phone_numbers](sub_array child) {
			for (size_t i = 0; i < phone_numbers.size(); i++) {
			bsoncxx::stdx::string_view d = phone_numbers.at(i);
			child.append(d);
			}
		}));

		user_document.append(kvp("emails", [emails](sub_array child) {
		for (size_t i = 0; i < emails.size(); i++) {
			bsoncxx::stdx::string_view d = emails.at(i);
			child.append(d);
		}
		}));

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string signup_date_time = oss.str();

		user_document.append(kvp("signup_date_time", signup_date_time));

		collection.insert_one(user_document.view());
		// return seccess message
		return reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		std::clog << e.code() << std::endl;
		return reply::error(e.what());
	}

	return reply;
}

std::string dbaas::database::update_user(std::string username,
					 std::string password,
					 std::vector<std::string> phone_numbers,
					 std::vector<std::string> emails,
					 std::string signup_date_time)
{
}

std::string dbaas::database::get_user(std::string username,
					  std::string password)
{
}

std::string dbaas::database::delete_user(std::string username,
					 std::string password)
{
}

std::string dbaas::database::create_key(std::string username,
					std::string password, std::string name,
					std::string valid_request_per_day,
					int request_per_day, int read_size,
					int write_size,
					std::vector<std::string> access)
{
}

std::string dbaas::database::update_key(
	std::string username, std::string password, optional_string name,
	optional_string valid_request_per_day, optional_size request_per_day,
	optional_size read_size, optional_size write_size,
	optional_string_array access)
{
}

std::string dbaas::database::get_user_key(std::string username,
					  std::string name)
{
}

std::string dbaas::database::get_user_keys(std::string username,
					   std::string password)
{
}

std::string dbaas::database::delete_user_key(std::string username,
						 std::string password,
						 std::string name)
{
}

std::string dbaas::database::delete_user_keys(std::string username,
						  std::string password)
{
}

std::string dbaas::database::create_payment(
	std::string username, std::string password, size_t main_value,
	size_t discount_value, std::string discount_type, size_t time,
	size_t expiration_time, size_t request_numbers_per_day, size_t read_size,
	size_t write_size)
{
}

std::string dbaas::database::get_payments(std::string username,
					  std::string password)
{
}
