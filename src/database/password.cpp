#include "password.h"

std::string password::create_key(std::string username)
{
	// TODO [1]get id from db and use as key
	key_mapper["key"] = username;
	return username;
}

std::string password::check_key(std::string key) { return key_mapper[key]; }
