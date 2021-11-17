#pragma once

#include "catch.hpp"

/// Utility for matching values in range for catch
template <typename T>
struct NumberRange : public Catch::MatcherBase<T> {
	T low, high;
	NumberRange(T low, T high) : low(low), high(high) {}

	bool match(const T & i) const override {
		return i >= low && i <= high;
	}

	std::string describe() const override {
		std::ostringstream ss;
		ss << "is between " << low << " and " << high;
		return ss.str();
	}
};

template <typename T>
NumberRange<T> IsBetween(T low, T high) {
	return NumberRange<T>(low, high);
}
