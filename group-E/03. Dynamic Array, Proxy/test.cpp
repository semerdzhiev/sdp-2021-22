#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include "dynamic_array.cpp"

TEST_CASE("copy constructor allocations")
{
     DynamicArray<int, DebugAllocator<int>> da(10);
     REQUIRE(da.get_alloc().allocations_count() == 1);
     DynamicArray<int, DebugAllocator<int>> db = da;
     REQUIRE(da.get_alloc().allocations_count() == 1);
    REQUIRE(db.get_alloc().allocations_count() == 1);
}

TEST_CASE("copy operator= allocations")
{
    DynamicArray<int, DebugAllocator<int>> da(10);
    REQUIRE(da.get_alloc().allocations_count() == 1);
    DynamicArray<int, DebugAllocator<int>> db(20);
    REQUIRE(db.get_alloc().allocations_count() == 1);

    db = da;
    REQUIRE(da.get_alloc().allocations_count() == 1);
    REQUIRE(db.get_alloc().allocations_count() == 1);
}