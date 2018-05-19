#include "password.h"

std::string dbaas::database::password::create_key(std::string username)
{
	// TODO [1]get id from db and use as key
	key_mapper["key"] = username;
	return username;
}

std::string dbaas::database::password::check_key(std::string key)
{
	return key_mapper[key];
}

// private for private members
dbaas::database::password::password() {}

// init static members
std::map<std::string, std::string> dbaas::database::password::key_mapper;
