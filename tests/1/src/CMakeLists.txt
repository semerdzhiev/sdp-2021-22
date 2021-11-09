cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(tests)

set(SOURCES
	../../../group-G/source/common/catch.hpp

	interface.h
	tests.cpp

	implementation.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ../../../group-G/source/common)