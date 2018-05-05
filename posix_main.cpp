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

int main(int argc, char *argv[])
{
	mongocxx::instance inst{};

	// NOTE MONGODB usage example
	// mongocxx::instance inst{};
	//	mongocxx::client conn{mongocxx::uri{}};

	//	bsoncxx::builder::stream::document document{};

	//	auto collection = conn["testdb"]["testcollection"];
	//	document << "hello"
	//		 << "world";

	//	collection.insert_one(document.view());
	//	auto cursor = collection.find({});

	//	for (auto &&doc : cursor) {
	//		std::cout << bsoncxx::to_json(doc) << std::endl;
	//	}

	// NOTE exampel of usage from_json
	//	bsoncxx::document::value document1 = bsoncxx::from_json("{}");

	try {
		// Check command line arguments.
		if (argc != 4) {
			std::cerr
			<< "Usage: http_server <address> <port> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 .\n";
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
