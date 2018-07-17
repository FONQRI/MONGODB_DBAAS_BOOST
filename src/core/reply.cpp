#include "reply.h"

std::string dbaas::core::reply::error(size_t code, std::string what)
{
	return "{\"isSuccessful\":false,\"code\":" + std::to_string(code) +
	   ",\"Message\":\"" + what + "\"}";
}

std::string dbaas::core::reply::answer(std::string answer)
{
	return "{\"isSuccessful\":true,\"code\":100,\"Response\":" + answer + "}";
}

std::string dbaas::core::reply::answer_done()
{
	return "{\"isSuccessful\":true,\"code\":100}";
}

std::string dbaas::core::reply::missing_item_error(std::string item_name)
{
	return "{\"isSuccessful\":false,\"code\":200,\"Message\":\"missing " +
	   item_name + "\"}";
}

std::string dbaas::core::reply::wrong_item_type(std::string item_name)
{
	return "{\"isSuccessful\":false,\"code\":300,\"Message\":\"wrong type " +
	   item_name + "\"}";
}

std::string dbaas::core::reply::access_denied(std::string why)
{
	return "{\"isSuccessful\":false,\"code\":400,\"Message\":\" access "
	   "denied " +
	   why + "\"}";
}

std::string dbaas::core::reply::client_key_not_found(std::string client_key)
{
	return "{\"isSuccessful\":false,\"code\":500,\"Message\":\" client key not "
	   "found : " +
	   client_key + "\"}";
}

std::string dbaas::core::reply::key_does_not_have_access_to_function(
	std::string function_name)
{
	return "{\"isSuccessful\":false,\"code\":501,\"Message\":\" The key does "
	   "not have access to the function : " +
	   function_name + "\"}";
}

std::string dbaas::core::reply::key_does_not_have_access_to_request()
{
	return "{\"isSuccessful\":false,\"code\":502,\"Message\":\" The key does "
	   "not have access to request : \"}";
}

std::string dbaas::core::reply::user_creation_failed(std::string why)
{
	return "{\"isSuccessful\":false,\"code\":610,\"Message\":\" user creation "
	   "failed " +
	   why + "\"}";
}

std::string dbaas::core::reply::user_update_failed(std::string why)
{
	return "{\"isSuccessful\":false,\"code\":620,\"Message\":\" user update "
	   "failed " +
	   why + "\"}";
}

std::string dbaas::core::reply::user_does_not_exist(std::string which)
{
	return "{\"isSuccessful\":false,\"code\":601,\"Message\":\" User does not "
	   "exist : " +
	   which + "\"}";
}

std::string dbaas::core::reply::http_error(std::string what)
{
	return "{\"isSuccessful\":false,\"code\":700,\"Message\":\"" + what + "\"}";
}

std::string dbaas::core::reply::wrong_request_content_type(std::string what)
{
	return "{\"isSuccessful\":false,\"code\":800,\"Message\":\"" + what + "\"}";
}

std::string dbaas::core::reply::database_error(std::string what)
{
	return "{\"isSuccessful\":false,\"code\":900,\"Message\":\"" + what + "\"}";
}

std::string dbaas::core::reply::duplicate_index(std::string what)
{
	return "{\"isSuccessful\":false,\"code\":601,\"Message\":\"" + what + "\"}";
}

std::string dbaas::core::reply::answer_not_found(std::string answer)
{
	return "{\"isSuccessful\":true,\"code\":101,\"Response\":\"" + answer +
	   "\"}";
}
