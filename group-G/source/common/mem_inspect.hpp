#pragma once

#include <unordered_map>
#include <type_traits>

#include <vector>
#include <list>

#ifdef _MSC_VER
#define massert(test) ( (test) ? (void)0 : __debugbreak() )
#else
#define massert(test) assert(test)
#endif


/// Registry used to track all allocations and deallocations, used after scopes to ensure all memory is deallocated
/// Singleton by the template type
template <typename T>
struct Registry {
	typedef std::unordered_map<T *, int> MemSize;
	MemSize allocations;
	int allocatedObjectCount = 0;
	int allocateCalls = 0;

	/// Check if there is any allocation pointers left in the registry
	bool hasLeakedMemory() const {
		return !allocations.empty();
	}

	/// Get the number of objects allocated for a given pointer, returns -1 if not found
	int getCountFor(T *ptr) const {
		typename MemSize::const_iterator it = allocations.find(ptr);
		if (it == allocations.end()) {
			return -1;
		}
		return it->second;
	}

	/// Add pointer with count to the registry
	void add(T *ptr, int count) {
		allocatedObjectCount += count;
		allocations.insert(std::make_pair(ptr, count));
		++allocateCalls;
	}

	/// Remove a pointer from the registry, asserts on pointers not previously added to registry
	void remove(T* ptr) {
		if (!ptr) {
			return;
		}
		typename MemSize::iterator iter = allocations.find(ptr);
		const bool validPtr = iter != allocations.end();
		massert(validPtr && "Deallocating invalid pointer");
		if (validPtr) {
			allocatedObjectCount -= iter->second;
			allocations.erase(iter);
		}
	}

	/// Reset the allocation calls counter
	void reset() {
		allocateCalls = 0;
	}

	static Registry<T> &get() {
		static Registry<T> reg;
		return reg;
	}
};

/// Bare minimum implementation of the STL allocator used to proxy calls to the Registry
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


template <typename T>
T removePtr(T *ptr);

#undef DELETE
#undef NEW

#define NEW(T, count) stl_allocator<T>().allocate(count)

template <typename T>
void DELETE(T *ptr) {
	if (!ptr) {
		return;
	}
	const int count = Registry<T>::get().getCountFor(ptr);
	if (count == -1) {
		massert(count >= 0 && "Deallocation of invalid pointer");
	}
	stl_allocator<T>().deallocate(ptr, count);
}


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
