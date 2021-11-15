#pragma once

#include <unordered_map>
#include <type_traits>

#include <vector>
#include <list>

#ifdef _MSC_VER
#define require(test) ( (test) ? (void)0 : __debugbreak() )
#else
#define require(test) assert(test)
#endif


template <typename T>
struct Registry {
	typedef std::unordered_map<T *, int> MemSize;
	MemSize allocations;
	int allocatedObjectCount = 0;
	int allocateCalls = 0;

	bool hasLeakedMemory() const {
		return !allocations.empty();
	}

	void add(T *ptr, int count) {
		allocatedObjectCount += count;
		allocations.insert(std::make_pair(ptr, count));
		++allocateCalls;
	}

	void remove(T* ptr) {
		if (!ptr) {
			return;
		}
		typename MemSize::iterator iter = allocations.find(ptr);
		const bool validPtr = iter != allocations.end();
		require(validPtr && "Deallocating invalid pointer");
		if (validPtr) {
			allocatedObjectCount -= iter->second;
			allocations.erase(iter);
		}
	}

	void reset() {
		allocateCalls = 0;
	}

	static Registry<T> &get() {
		static Registry<T> reg;
		return reg;
	}
};

template <typename T>
T removePtr(T *ptr);

#undef DELETE
#undef NEW

#define NEW(T, count) Registry<T>::get().allocate(count)
#define DELETE(ptr) Registry<decltype(removePtr(ptr))>::get().deallocate(ptr)

template <typename T>
struct stl_allocator {
	typedef T value_type;
	typedef T *pointer;
	typedef const T *const_pointer;

	typedef T &reference;
	typedef const T &const_reference;

	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;

	template <typename U> struct rebind {
		typedef stl_allocator<U> other;
	};

	constexpr stl_allocator() noexcept {}

	constexpr stl_allocator(const stl_allocator &) = default;

	template <class U>
	constexpr stl_allocator(const stl_allocator<U> &) {}

	pointer allocate(size_type n, const void *) const {
		return allocate(n);
	}

	pointer allocate(size_type n) const {
		pointer ptr = std::allocator<T>().allocate(n);
		Registry<T>::get().add(ptr, n);
		return ptr;
	}

	void deallocate(T *ptr, std::size_t count) const {
		Registry<T>::get().remove(ptr);
		std::allocator<T>().deallocate(ptr, count);
	}

	bool operator==(const stl_allocator &) const {
		return true;
	}

	bool operator!=(const stl_allocator &) const {
		return false;
	}
};


/// Object that counts the number of instances of itself
/// Used to verify vector allocates and deallocates
struct InstanceCounter {
	int value = 0; ///< Some value to enable comparisons and different values
	static int instanceCount; ///< The counter for the instances

	static void incref() {
		++instanceCount;
	}

	static void decref() {
		--instanceCount;
	}

	InstanceCounter() {
		incref();
	}

	InstanceCounter(int value)
		: value(value) {
		incref();
	}

	~InstanceCounter() {
		decref();
	}

	InstanceCounter(const InstanceCounter &other)
		: value(other.value) {
		incref();
	}

	InstanceCounter(InstanceCounter &&other)
		: value(other.value) {
		incref();
	}

	InstanceCounter &operator=(const InstanceCounter &other) = default;
	InstanceCounter &operator=(InstanceCounter &&other) = default;

	InstanceCounter &operator++() {
		++value;
		return *this;
	}

	bool operator==(const InstanceCounter &other) const {
		return value == other.value;
	}

	bool operator<=(const InstanceCounter &other) const {
		return value <= other.value;
	}

	bool operator<(const InstanceCounter &other) const {
		return value < other.value;
	}
};

int InstanceCounter::instanceCount = 0;
