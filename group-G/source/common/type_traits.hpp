#pragma once

/// Value result template, true when argument is const qualified
template <typename T>
struct is_const {
	enum {
		value = false,
	};
};

/// Specialization for const
template <typename T>
struct is_const<const T> {
	enum {
		value = true,
	};
};

// sanity checks
static_assert(is_const<int>::value == false, "int should be non const");
static_assert(is_const<const int>::value == true, "const int should be non const");
static_assert(is_const<char *>::value == false, "char * should be non const");
static_assert(is_const<char * const>::value == true, "char * const should be non const");


template <bool test, typename T>
struct enable_if {
	typedef T type;
};

/// Specialization for false case
template <typename T>
struct enable_if<false, T> {
};
