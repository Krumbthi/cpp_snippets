cmake_minimum_required(VERSION 3.5)

project(cb_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    ${CMAKE_SOURCE_DIR}/../../common/AppLogger.cpp
    ${CMAKE_SOURCE_DIR}/../../common/FrameDispatcher.cpp
    ${CMAKE_SOURCE_DIR}/../devicechangenotifier.cpp
    ${CMAKE_SOURCE_DIR}/../usbaccesslayer.cpp
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
