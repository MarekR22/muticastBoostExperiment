cmake_minimum_required(VERSION 3.25)

project(Muticast VERSION 1.0 LANGUAGES CXX)

find_package(Boost 1.80 REQUIRED system)

add_executable(upd_broadcast sender.cpp)
target_link_libraries(upd_broadcast PRIVATE Boost::system)

add_executable(upd_observer receiver.cpp)
target_link_libraries(upd_observer PRIVATE Boost::system)

