cmake_minimum_required(VERSION 3.10)

project(lib_test LANGUAGES CXX)
set(SUMMARY on)

#find_library(USB_LIB usb_com_bf)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_SOURCE_DIR})
list(APPEND EXTRA_LIBS usb_com_bf)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

if (${SUMMARY})
	message(STATUS "-------------------------------------------------")
	message(STATUS "[ Build summary ]")
	message(STATUS "CMAKE_GENERATOR       : ${CMAKE_GENERATOR}")
	message(STATUS "Compiler ID           : ${CMAKE_CXX_COMPILER_ID}")
	message(STATUS "Compiler version      : ${CMAKE_CXX_COMPILER_VERSION}")
	message(STATUS "Compiler path         : ${CMAKE_CXX_COMPILER}")
	message(STATUS "llvm-config           : ${LLVM_CONFIG_PATH}")
	message(STATUS "Min LLVM major version: ${INSIGHTS_MIN_LLVM_MAJOR_VERSION}")
	message(STATUS "Install path          : ${CMAKE_INSTALL_PREFIX}")
	message(STATUS "Clang resource dir    : ${INSIGHTS_CLANG_RESOURCE_DIR}")
    message(STATUS "CMAKE_SOURCE_DIR      : ${CMAKE_SOURCE_DIR}")
    message(STATUS "PROJECT_SOURCE_DIR    : ${PROJECT_SOURCE_DIR}")
	message(STATUS "CMAKE_BINARY_DIR      : ${CMAKE_BINARY_DIR}")
	message(STATUS "Git repo url          : ${GIT_REPO_URL}")
	message(STATUS "Git commit hash       : ${GIT_COMMIT_HASH}")
	message(STATUS "Debug                 : ${DEBUG}")
	message(STATUS "-------------------------------------------------")
endif()
