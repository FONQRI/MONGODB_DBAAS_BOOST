#ifndef DATABASE_INIT_VALUES_H
#define DATABASE_INIT_VALUES_H
#include <string>
#include <vector>

namespace dbaas {
namespace database {

bool initialize();
bool create_indexes();

// std::vector<std::string> m_database_urls_and_ports;
} // dbaas
} // database
#endif // DATABASE_INIT_VALUES_H
