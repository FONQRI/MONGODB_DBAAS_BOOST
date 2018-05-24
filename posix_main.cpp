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

// TODO remove test code
#include "src/database/password.h"

#include "src/controller/delete/delete_many.h"
#include "src/controller/delete/delete_one.h"
#include "src/controller/delete/find_one_and_delete.h"
#include "src/controller/find/find.h"
#include "src/controller/find/find_one.h"
#include "src/controller/get_info/count.h"
#include "src/controller/insert/insert_many.h"
#include "src/controller/insert/insert_one.h"
#include "src/controller/update/find_one_and_replace.h"
#include "src/controller/update/find_one_and_update.h"
#include "src/controller/update/update_many.h"
#include "src/controller/update/update_one.h"

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
	// init controller map
	controller_mapper["find"] = dbaas::core::find;
	controller_mapper["find_one"] = dbaas::core::find_one;
	controller_mapper["insert_one"] = dbaas::core::insert_one;
	controller_mapper["insert_many"] = dbaas::core::insert_many;
	controller_mapper["count"] = dbaas::core::count;
	controller_mapper["delete_one"] = dbaas::core::delete_one;
	controller_mapper["delete_many"] = dbaas::core::delete_many;
	controller_mapper["find_one_and_delete"] = dbaas::core::find_one_and_delete;
	controller_mapper["update_one"] = dbaas::core::update_one;
	controller_mapper["update_many"] = dbaas::core::update_many;
	controller_mapper["find_one_and_update"] = dbaas::core::find_one_and_update;
	controller_mapper["find_one_and_replace"] =
	dbaas::core::find_one_and_replace;

	mongocxx::instance inst{};
	dbaas::database::password::create_key("dbname");

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
	catch (std::exception &e) {
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}
