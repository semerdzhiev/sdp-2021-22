project(VectorTest)

set(SOURCES
	../common/catch.hpp
	../common/mem_inspect.hpp

	vector_tests.cpp
	vector.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ../common)

