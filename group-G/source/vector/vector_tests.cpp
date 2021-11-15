#define CATCH_CONFIG_MAIN

#include "catch_utils.hpp"
#include "mem_inspect.hpp"
#include "vector.hpp"

#include <vector>

/// If the user did not define USER_VECTOR, run tests on std::vector
#ifndef USER_VECTOR

template <typename T>
using vector = std::vector<T, stl_allocator<T>>;

#endif

/// Run all tests once on int, and once on the InstanceCounter
#define TEST_TYPES int, InstanceCounter

/// Tests begin

TEMPLATE_TEST_CASE("Vector create/destroy", "[vector][lifetime]", TEST_TYPES) {
	Registry<TestType> &memory = Registry<TestType>::get();

	SECTION("Default constructor") {
		vector<TestType> instance;
		REQUIRE(instance.size() == 0);
		REQUIRE(instance.capacity() == 0);
		REQUIRE_FALSE(memory.hasLeakedMemory());
	}

	SECTION("Copy constructor / operator=") {
		vector<TestType> instance;
		vector<TestType> copy(instance);
		vector<TestType> assign;
		assign = instance;
		REQUIRE(instance.size() == 0);
		REQUIRE(instance.capacity() == 0);
		REQUIRE(copy.capacity() == 0);
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(memory.allocatedObjectCount == 0);
	}

	SECTION("Constructor with count") {
		vector<TestType> instance(15);
		REQUIRE(instance.size() == 15);
		CHECK_THAT(instance.capacity(), IsBetween(15, 16));
		CHECK_THAT(memory.allocatedObjectCount, IsBetween(15, 16));
	}

	SECTION("Constructor with count and value") {
		{
			vector<TestType> instance(17, TestType(5));
			REQUIRE(instance.size() == 17);
			CHECK_THAT(instance.capacity(), IsBetween(17, 32));
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(17, 32));

			REQUIRE(instance.front() == TestType(5));
			REQUIRE(instance.back() == TestType(5));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Copy and assign non empty vector") {
		{
			vector<TestType> instance(10, TestType{});
			REQUIRE(instance.size() == 10);
			REQUIRE(instance.capacity() == 10);
			
			vector<TestType> copy(instance);
			REQUIRE(copy.size() == 10);
			REQUIRE(copy.capacity() == 10);

			vector<TestType> assign;
			assign.reserve(100);
			
			REQUIRE(assign.capacity() == 100);
			REQUIRE(assign.size() == 0);

			assign = copy;

			REQUIRE(assign.capacity() == 100);
			REQUIRE(assign.size() == copy.size());
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Clear and shrink_to_fit after constructor with count") {
		{
			vector<TestType> instance(31, TestType());

			CHECK_THAT(instance.capacity(), IsBetween(31, 32));
			REQUIRE(instance.size() == 31);

			instance.clear();

			REQUIRE(instance.size() == 0);
			CHECK_THAT(instance.capacity(), IsBetween(31, 32));
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(31, 32));

			instance.shrink_to_fit();

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 0);
			REQUIRE(memory.allocatedObjectCount == 0);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Reservation and shrink_to_fit") {
		{
			vector<TestType> instance;

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 0);

			instance.reserve(15);

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 15);

			instance.reserve(15);

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 15);

			instance.shrink_to_fit();

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 0);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Resize clear and shrink_to_fit") {
		{
			vector<TestType> instance;
			instance.resize(137);

			REQUIRE(instance.size() == 137);
			REQUIRE(instance.capacity() == 137);

			instance.clear();

			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == 137);

			instance.resize(100);
			
			REQUIRE(instance.size() == 100);
			REQUIRE(instance.capacity() == 137);

			instance.shrink_to_fit();

			REQUIRE(instance.size() == 100);
			REQUIRE(instance.capacity() == 100);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Resize with value") {
		{
			vector<TestType> instance;
			instance.resize(10, TestType(0));

			REQUIRE(instance.size() == 10);
			REQUIRE(instance.capacity() == 10);
			REQUIRE(instance.back() == TestType(0));

			instance.resize(5);

			REQUIRE(instance.size() == 5);
			REQUIRE(instance.capacity() == 10);
			REQUIRE(instance.back() == TestType(0));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}

TEMPLATE_TEST_CASE("Vector back modify", "[vector][modify_end]", TEST_TYPES) {
	Registry<TestType> &memory = Registry<TestType>::get();
	SECTION("Push and pop all") {
		{
			vector<TestType> instance;
			for (int c = 0; c < 21; c++) {
				instance.push_back(TestType());
			}
			REQUIRE(instance.size() == 21);
			CHECK_THAT(instance.capacity(), IsBetween(21, 32));
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(21, 32));

			const int capacityBeforePop = instance.capacity();
			const int allocatedObjectBeforePop = memory.allocatedObjectCount;
			for (int c = 0; c < 21; c++) {
				instance.pop_back();
			}
			REQUIRE(instance.size() == 0);
			REQUIRE(instance.capacity() == capacityBeforePop);
			REQUIRE(memory.allocatedObjectCount == allocatedObjectBeforePop);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_back/pop_back") {
		{
			vector<TestType> instance;
			for (int c = 0; c < 100; c++) {
				instance.push_back(TestType());
				instance.pop_back();
			}
			REQUIRE(instance.size() == 0);
			CHECK_THAT(instance.capacity(), IsBetween(1, 2));
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(1, 2));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_back/back") {
		{
			vector<TestType> instance;
			TestType value(0);
			for (int c = 0; c < 100; c++) {
				instance.push_back(value);
				REQUIRE(instance.back() == value);
				++value;
			}
			REQUIRE(instance.size() == 100);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Reserve before push_back") {
		{
			vector<TestType> instance;
			TestType value(0);
			for (int c = 0; c < 100; c++) {
				instance.push_back(value);
				REQUIRE(instance.back() == value);
				++value;
			}
			REQUIRE(instance.size() == 100);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Resize strategy") {
		{
			vector<TestType> instance;
			const int steps = 1000;
			int currentCapacity = int(instance.capacity());
			double totalRatio = 0;
			int incrementSteps = 0;
			for (int c = 0; c < steps; c++) {
				instance.push_back(TestType());
				if (instance.capacity() != currentCapacity) {
					double ratio = 0;
					if (currentCapacity == 0) {
						ratio = 0;
					} else {
						ratio = double(instance.capacity()) / currentCapacity;
					}
					totalRatio += ratio;
					++incrementSteps;
					currentCapacity = instance.capacity();
				}
			}
			const double averageStep = totalRatio / incrementSteps;
			CHECK_THAT(averageStep, IsBetween(1.1, 2.0));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}

TEMPLATE_TEST_CASE("Vector element access", "[vector][index_access]", TEST_TYPES) {
	Registry<TestType> &memory = Registry<TestType>::get();

	SECTION("front/back and operator[]") {
		{
			vector<TestType> instance;
			TestType value{0};
			const int itemCount = 10;
			for (int c = 0; c < itemCount; c++) {
				instance.push_back(value);
				REQUIRE(instance.back() == value);
				++value;
			}

			value = TestType(0);
			REQUIRE(instance.front() == value);

			for (int c = 0; c < itemCount; c++) {
				REQUIRE(instance[c] == value);
				++value;
			}
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("operator[]") {
		{
			vector<TestType> instance;
			REQUIRE_THROWS(instance.at(0));
			REQUIRE_THROWS(instance.at(-1));

			TestType value{0};
			const int itemCount = 10;
			for (int c = 0; c < itemCount; c++) {
				instance.push_back(value);
				++value;
			}

			value = TestType(0);
			for (int c = 0; c < itemCount; c++) {
				REQUIRE(instance.at(c) == value);
				++value;
			}
			REQUIRE_THROWS(instance.at(itemCount));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}


TEMPLATE_TEST_CASE("Vector iterator access", "[vector][iterator]", TEST_TYPES) {
	Registry<TestType> &memory = Registry<TestType>::get();

	SECTION("Iterator creation and operators") {
		{
			vector<TestType> instance(3, TestType{0});
			typename vector<TestType>::iterator it = instance.begin();
			REQUIRE(*it == TestType{0});
			REQUIRE(it == instance.begin());
			typename vector<TestType>::iterator end = instance.end();
			REQUIRE(it < end);
			REQUIRE(end == instance.end());
			REQUIRE(++(--end) == instance.end());
			REQUIRE(++(++(++it)) == end);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Iterator value modification") {
		{
			vector<TestType> instance(3);
			TestType value{0};
			for (typename vector<TestType>::iterator it = instance.begin(); it != instance.end(); ++it) {
				*it = ++value;
			}

			value = TestType{0};
			REQUIRE(instance[0] == ++value);
			REQUIRE(instance[1] == ++value);
			REQUIRE(instance[2] == ++value);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
	
	SECTION("Iterator insert/erase") {
		{
			vector<TestType> instance(1, TestType{0});

			TestType value{0};

			instance.insert(instance.begin(), ++value);
			REQUIRE(instance[0] == value);

			instance.insert(instance.end(), ++value);
			REQUIRE(instance.back() == value);

			vector<TestType> copy = instance;

			instance.erase(instance.begin());
			REQUIRE(instance.front() == TestType{0});

			instance.erase(--instance.end());
			REQUIRE(instance.back() == TestType{0});
			REQUIRE(instance.size() == 1);

			copy.erase(copy.begin(), copy.end());
			REQUIRE(copy.empty());
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}