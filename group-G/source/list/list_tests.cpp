#define CATCH_CONFIG_MAIN

#include "catch_utils.hpp"
#include "mem_inspect.hpp"
#include "list.hpp"

#include <vector>
#include <list>


#ifndef USER_LIST
// run tests on std::list

// std::list allocates 1 extra element on heap for MSVC
#define LIST_EXTRA_ELEMENT
template <typename T>
using TestList = std::list<T, stl_allocator<T>>;

// std::list's Node is this for MSVC
#ifdef __MINGW32__

template <typename T>
using ListNode = std::_List_node<T>;


#elif _MSC_VER

template <typename T>
using ListNode = std::_List_node<T, typename std::allocator_traits<stl_allocator<T>>::void_pointer>;

#else
#error "Unknown compiler, ask for support for it"
#endif


#else

/// Your list type
template <typename T>
using TestList = list<T>;

/// Your list Node
template <typename T>
using ListNode = typename list<T>::Node;

#endif


/// Get the number of allocated objects for given number of elements
int getMaxListObjects(const int count) {
#ifdef LIST_EXTRA_ELEMENT
	return count + 1; // list allocates 1 dummy
#endif
	return count; // list does not allocate dummy node
}

/// Run all tests once on int, and once on the InstanceCounter
#define TEST_TYPES int, InstanceCounter


/// Tests begin

TEMPLATE_TEST_CASE("List create/destroy", "[list][lifetime]", TEST_TYPES) {
	Registry<ListNode<TestType>> &memory = Registry<ListNode<TestType>>::get();

	SECTION("Default constructor") {
		{
			TestList<TestType> instance;
			REQUIRE(instance.size() == 0);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
	}

	SECTION("Copy constructor / operator=") {
		{
			TestList<TestType> instance;
			TestList<TestType> copy(instance);
			TestList<TestType> assign;
			assign = instance;
			REQUIRE(instance.size() == 0);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(memory.allocatedObjectCount == 0);
	}

	SECTION("Constructor with count") {
		TestList<TestType> instance(15);
		REQUIRE(instance.size() == 15);
		CHECK_THAT(memory.allocatedObjectCount, IsBetween(15, getMaxListObjects(15)));
	}

	SECTION("Constructor with count and value") {
		{
			TestList<TestType> instance(17, TestType(5));
			REQUIRE(instance.size() == 17);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(17, getMaxListObjects(17)));

			REQUIRE(instance.front() == TestType(5));
			REQUIRE(instance.back() == TestType(5));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Copy and assign non empty list") {
		{
			TestList<TestType> instance(10, TestType{});
			REQUIRE(instance.size() == 10);
			
			TestList<TestType> copy(instance);
			REQUIRE(copy.size() == 10);

			TestList<TestType> assign;
			
			REQUIRE(assign.size() == 0);

			assign = copy;

			REQUIRE(assign.size() == copy.size());
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Clear after constructor with count") {
		{
			TestList<TestType> instance(31, TestType());

			REQUIRE(instance.size() == 31);

			instance.clear();

			REQUIRE(instance.size() == 0);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(0, getMaxListObjects(0)));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

}

TEMPLATE_TEST_CASE("List back modify", "[list][modify_end]", TEST_TYPES) {
	Registry<ListNode<TestType>>& memory = Registry<ListNode<TestType>>::get();
	SECTION("Push_back and pop_back all") {
		{
			TestList<TestType> instance;
			for (int c = 0; c < 21; c++) {
				instance.push_back(TestType());
			}
			REQUIRE(instance.size() == 21);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(21, getMaxListObjects(21)));

			for (int c = 0; c < 21; c++) {
				instance.pop_back();
			}
			REQUIRE(instance.size() == 0);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(0, getMaxListObjects(0)));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_back/pop_back") {
		{
			TestList<TestType> instance;
			for (int c = 0; c < 100; c++) {
				instance.push_back(TestType());
				instance.pop_back();
			}
			REQUIRE(instance.size() == 0);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(0, getMaxListObjects(0)));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_back/back") {
		{
			TestList<TestType> instance;
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

	SECTION("Push_front and pop_front all") {
		{
			TestList<TestType> instance;
			for (int c = 0; c < 21; c++) {
				instance.push_front(TestType());
			}
			REQUIRE(instance.size() == 21);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(21, getMaxListObjects(21)));

			for (int c = 0; c < 21; c++) {
				instance.pop_front();
			}
			REQUIRE(instance.size() == 0);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(0, getMaxListObjects(0)));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_front/pop_front") {
		{
			TestList<TestType> instance;
			for (int c = 0; c < 100; c++) {
				instance.push_front(TestType());
				instance.pop_front();
			}
			REQUIRE(instance.size() == 0);
			CHECK_THAT(memory.allocatedObjectCount, IsBetween(0, getMaxListObjects(0)));
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Repeated push_front/front") {
		{
			TestList<TestType> instance;
			TestType value(0);
			for (int c = 0; c < 100; c++) {
				instance.push_front(value);
				REQUIRE(instance.front() == value);
				++value;
			}
			REQUIRE(instance.size() == 100);
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}

TEMPLATE_TEST_CASE("List iterator access", "[list][iterator]", TEST_TYPES) {
	Registry<ListNode<TestType>>& memory = Registry<ListNode<TestType>>::get();

	SECTION("Iterator creation and operators") {
		{
			TestList<TestType> instance(3, TestType{0});
			typename TestList<TestType>::iterator it = instance.begin();
			REQUIRE(*it == TestType{0});
			REQUIRE(it == instance.begin());
			typename TestList<TestType>::iterator end = instance.end();
			REQUIRE(end == instance.end());
			REQUIRE(++(--end) == instance.end());
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Iterator value modification") {
		{
			TestList<TestType> instance(3);
			TestType value{0};
			for (typename TestList<TestType>::iterator it = instance.begin(); it != instance.end(); ++it) {
				*it = ++value;
			}

			value = TestType{0};
			for (typename TestList<TestType>::iterator it = instance.begin(); it != instance.end(); ++it) {
				REQUIRE(*it == ++value);
			}
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
	
	SECTION("Iterator insert/erase") {
		{
			TestList<TestType> instance(1, TestType{0});

			TestType value{0};

			instance.insert(instance.begin(), ++value);
			REQUIRE(instance.front() == value);

			instance.insert(instance.end(), ++value);
			REQUIRE(instance.back() == value);

			TestList<TestType> copy = instance;

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

TEMPLATE_TEST_CASE("List element operations", "[list][advanced]", TEST_TYPES) {
	Registry<ListNode<TestType>>& memory = Registry<ListNode<TestType>>::get();

	SECTION("Splice") {
		{
			TestList<TestType> source;
			TestList<TestType> destination;
			std::vector<TestType*> sourceItems;
			TestType value{ 0 };
			const int itemCount = 2;
			
			for (int c = 0; c < itemCount; c++) {
				destination.push_back(value);
				++value;
			}

			for (int c = 0; c < itemCount; c++) {
				source.push_back(value);
				sourceItems.push_back(&source.back());
				++value;
			}

			typename TestList<TestType>::iterator begin1 = destination.begin();
			destination.splice(++begin1, source);

			REQUIRE(destination.size() == 4);
			REQUIRE(source.size() == 0);

			typename TestList<TestType>::iterator it = destination.begin();
			REQUIRE(&*(++it) == sourceItems[0]);
			REQUIRE(&*(++it) == sourceItems[1]);

		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Merge") {
		{
			TestList<TestType> destination;
			TestList<TestType> source;
			std::vector<TestType*> sourceItems;
			TestType value{ 0 };
			const int itemCount = 10;

			for (int c = 0; c < itemCount; c++) {
				if (c % 2 == 0) {
					destination.push_back(value);
				}
				else {
					source.push_back(value);
					sourceItems.push_back(&source.back());
				}
				++value;
			}

			destination.merge(source);

			REQUIRE(destination.size() == 10);
			REQUIRE(source.size() == 0);

			typename TestList<TestType>::iterator current = destination.begin();
			typename TestList<TestType>::iterator next = ++destination.begin();
			for (; next != destination.end(); ++current, ++next) {
				REQUIRE(*current <= *next);
			}

			current = destination.begin();
			int sourceItemIx = 0;
			for (int i = 0; current != destination.end(); ++i, ++current) {
				if (i % 2 == 1) {
					REQUIRE(&(*current) == sourceItems[sourceItemIx]);
					sourceItemIx++;
				}
			}

		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}

	SECTION("Unique") {
		{
			TestList<TestType> instance;
			std::vector<TestType*> itemsLeft;
			TestType value{ 0 };
			const int itemCount = 10;

			for (int c = 0; c < itemCount; c++) {
				instance.push_back(value);

				if (c % 2 == 0) {
					itemsLeft.push_back(&instance.back());
				}
				else {
					++value;
				}
			}

			instance.unique();

			REQUIRE(instance.size() == 5);

			int itemsLeftIx = 0;
			for (typename TestList<TestType>::iterator it = instance.begin(); it != instance.end(); ++it) {
				REQUIRE(&(*it) == itemsLeft[itemsLeftIx]);
				++itemsLeftIx;
			}
		}
		REQUIRE_FALSE(memory.hasLeakedMemory());
		REQUIRE(InstanceCounter::instanceCount == 0);
	}
}
