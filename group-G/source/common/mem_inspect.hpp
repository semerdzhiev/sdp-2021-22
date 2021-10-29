#pragma once

#include <unordered_map>
#include <type_traits>

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

	T *allocate(int count) {
		T *ptr = new T[count];
		allocatedObjectCount += count;
		allocations.insert(std::make_pair(ptr, count));
		++allocateCalls;
		return ptr;
	}

	void deallocate(T *ptr) {
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
		delete[] ptr;
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
		return Registry<T>::get().allocate(n);
	}

	void deallocate(T *ptr, std::size_t) const {
		deallocate(ptr);
	}

	void deallocate(T *ptr) const {
		return Registry<T>::get().deallocate(ptr);
	}

	bool operator==(const stl_allocator &) const {
		return true;
	}

	bool operator!=(const stl_allocator &) const {
		return false;
	}
};
