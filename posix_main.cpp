#include "src/server/file_handler.hpp"
#include "src/server/server.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <signal.h>

// mongo includes
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

// delete controllers
#include "src/controller/collection/delete/delete_many.h"
#include "src/controller/collection/delete/delete_one.h"
#include "src/controller/collection/delete/find_one_and_delete.h"

// find controllers
#include "src/controller/collection/find/aggregate.h"
#include "src/controller/collection/find/find.h"
#include "src/controller/collection/find/find_one.h"

// get info controllers
#include "src/controller/collection/get_info/count.h"
#include "src/controller/collection/get_info/list_indexes.h"
#include "src/controller/collection/get_info/name.h"

// insert controllers
#include "src/controller/collection/insert/insert_many.h"
#include "src/controller/collection/insert/insert_one.h"

// update controllers
#include "src/controller/collection/update/create_index.h"
#include "src/controller/collection/update/distinct.h"
#include "src/controller/collection/update/find_one_and_replace.h"
#include "src/controller/collection/update/find_one_and_update.h"
#include "src/controller/collection/update/update_many.h"
#include "src/controller/collection/update/update_one.h"

// user controllers
#include "src/controller/user/create_key.h"
#include "src/controller/user/create_payment.h"
#include "src/controller/user/create_user.h"
#include "src/controller/user/delete_user.h"
#include "src/controller/user/delete_user_key.h"
#include "src/controller/user/delete_user_keys.h"
#include "src/controller/user/get_payments.h"
#include "src/controller/user/get_user.h"
#include "src/controller/user/get_user_keys.h"
#include "src/controller/user/update_key.h"
#include "src/controller/user/update_user.h"

// init database
#include "src/database/database_init_values.h"

// TODO remove test code
#include "src/database/security/password.h"

/**
 * @brief controller	: a function for controller mapping
 * @param rep			: reply of http
 * @param request		: request of http
 */
typedef void controller(http::server::reply &rep,
			http::server::request request);

/**
 * @brief function_mapper : controller mapper type
 */
typedef std::map<std::string, controller *> function_mapper;

/**
 * @brief controller_mapper
 */
function_mapper controller_mapper;

int main(int argc, char *argv[])
{
	// database init
	mongocxx::instance inst{};
	dbaas::database::initialize();

	// init controller map
	// find
	controller_mapper["find"] = dbaas::controller::find;
	controller_mapper["find_one"] = dbaas::controller::find_one;
	controller_mapper["aggregate"] = dbaas::controller::aggregate;

	// insert
	controller_mapper["insert_one"] = dbaas::controller::insert_one;
	controller_mapper["insert_many"] = dbaas::controller::insert_many;

	// get_info
	controller_mapper["count"] = dbaas::controller::count;
	controller_mapper["name"] = dbaas::controller::name;
	controller_mapper["list_indexes"] = dbaas::controller::list_indexes;

	// delete
	controller_mapper["delete_one"] = dbaas::controller::delete_one;
	controller_mapper["delete_many"] = dbaas::controller::delete_many;
	controller_mapper["find_one_and_delete"] =
	dbaas::controller::find_one_and_delete;

	// update
	controller_mapper["update_one"] = dbaas::controller::update_one;
	controller_mapper["update_many"] = dbaas::controller::update_many;
	controller_mapper["create_index"] = dbaas::controller::create_index;
	controller_mapper["distinct"] = dbaas::controller::distinct;
	controller_mapper["find_one_and_replace"] =
	dbaas::controller::find_one_and_replace;

	// user
	controller_mapper["create_user"] = dbaas::controller::create_user;
	controller_mapper["create_key"] = dbaas::controller::create_key;
	controller_mapper["update_key"] = dbaas::controller::update_key;
	controller_mapper["create_payment"] = dbaas::controller::create_payment;
	controller_mapper["delete_user"] = dbaas::controller::delete_user;
	controller_mapper["delete_user_key"] = dbaas::controller::delete_user_key;
	controller_mapper["delete_user_keys"] = dbaas::controller::delete_user_keys;
	controller_mapper["get_payments"] = dbaas::controller::get_payments;
	controller_mapper["get_user"] = dbaas::controller::get_user;
	controller_mapper["get_user_keys"] = dbaas::controller::get_user_keys;
	controller_mapper["update_user"] = dbaas::controller::update_user;

	try {
		// Check command line arguments.
		if (argc != 4) {
			std::cerr
			<< "Usage: http_server <address> <port> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 127.0.0.1 8000 doc.\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver ::1 80 doc.\n";
			return 1;
		}

		boost::asio::io_service io_service;

		// Launch the initial server coroutine.
		http::server::server(io_service, argv[1], argv[2],
				 http::server::request_handler(argv[3]))();

		// Wait for signals indicating time to shut down.
		boost::asio::signal_set signals(io_service);
		signals.add(SIGINT);
		signals.add(SIGTERM);
#if defined(SIGQUIT)
		signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
		signals.async_wait(
		boost::bind(&boost::asio::io_service::stop, &io_service));

		// Run the server.
		io_service.run();
	}
	catch (const std::exception &e) {
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}
