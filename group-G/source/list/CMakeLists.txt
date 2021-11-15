project(ListTestS)

set(SOURCES
	../common/catch_utils.hpp
	../common/mem_inspect.hpp
	../common/type_traits.hpp

	list_tests.cpp
	list.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ../common)
