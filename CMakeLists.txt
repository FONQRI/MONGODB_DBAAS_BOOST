cmake_minimum_required(VERSION 2.8.12)

project(MONGODB_DBAAS_BOOST)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(./src)


#seting file pathes
file(GLOB ServerHeaders ./src/server/*.h)
file(GLOB ServerCpp ./src/server/*.cpp)
file(GLOB ServerHpp ./src/server/*.hpp)

file(GLOB RequestHeaders ./src/controller/*.h)
file(GLOB RequestCpp ./src/controller/*.cpp)
file(GLOB RequestHpp ./src/controller/*.hpp)

#************************

file(GLOB DeleteHeaders   ./src/controller/delete/*.h)
file(GLOB DeleteCpp       ./src/controller/delete/*.cpp)
file(GLOB DeleteHpp       ./src/controller/delete/*.hpp)


file(GLOB FindHeaders     ./src/controller/find/*.h)
file(GLOB FindCpp         ./src/controller/find/*.cpp)
file(GLOB FindHpp         ./src/controller/find/*.hpp)


file(GLOB GetInfoHeaders  ./src/controller/get_info/*.h)
file(GLOB GetInfoCpp      ./src/controller/get_info/*.cpp)
file(GLOB GetInfoHpp      ./src/controller/get_info/*.hpp)


file(GLOB InsertHeaders   ./src/controller/insert/*.h)
file(GLOB InsertCpp       ./src/controller/insert/*.cpp)
file(GLOB InsertHpp       ./src/controller/insert/*.hpp)


file(GLOB UpdateHeaders   ./src/controller/update/*.h)
file(GLOB UpdateCpp       ./src/controller/update/*.cpp)
file(GLOB UpdateHpp       ./src/controller/update/*.hpp)


file(GLOB OprationsHeaders ./src/controller/oprations/*.h)
file(GLOB OprationsCpp     ./src/controller/oprations/*.cpp)
file(GLOB OprationsHpp     ./src/controller/oprations/*.hpp)


file(GLOB DatabaseHeaders  ./src/database/*.h)
file(GLOB DatabaseCpp      ./src/database/*.cpp)
file(GLOB DatabaseHpp      ./src/database/*.hpp)


#library
add_library(Server
  ${ServerHeaders}
  ${ServerCpp}
  ${ServerHpp}
  )

add_library(Request

  ${RequestHeaders}
  ${RequestCpp}
  ${RequestHpp}

  ${DeleteHeaders}
  ${DeleteCpp}
  ${DeleteHpp}


  ${FindHeaders}
  ${FindCpp}
  ${FindHpp}


  ${GetInfoHeaders}
  ${GetInfoCpp}
  ${GetInfoHpp}


  ${InsertHeaders}
  ${InsertCpp}
  ${InsertHpp}


  ${UpdateHeaders}
  ${UpdateCpp}
  ${UpdateHpp}


  ${OprationsHeaders}
  ${OprationsCpp}
  ${OprationsHpp}


  ${DatabaseHeaders}
  ${DatabaseCpp}
  ${DatabaseHpp}

  )

add_library(Database
  ${DatabaseHeaders}
  ${DatabaseCpp}
  ${DatabaseHpp}
  )


set (CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++14 -D__STRICT_ANSI__")

find_package (Threads)
find_package(libbsoncxx)
find_package(libmongocxx)

include_directories(${LIBBSONCXX_INCLUDE_DIRS} ${LIBMONGOCXX_INCLUDE_DIRS} )


find_package(Boost 1.58 REQUIRED COMPONENTS
  date_time
  filesystem
  iostreams
  thread
  )

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_NAME} "posix_main.cpp" )
  target_link_libraries(${PROJECT_NAME}
    Boost::date_time
    Boost::filesystem
    Boost::iostreams
    Boost::thread

    ${CMAKE_THREAD_LIBS_INIT}
    ${LIBBSONCXX_LIBRARIES}
    ${LIBMONGOCXX_LIBRARIES}

    Server
    Request
    Database
    )

  target_link_libraries(Database
    Boost::date_time
    Boost::iostreams
    ${LIBBSONCXX_LIBRARIES}
    ${LIBMONGOCXX_LIBRARIES}
    )
endif(Boost_FOUND)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

