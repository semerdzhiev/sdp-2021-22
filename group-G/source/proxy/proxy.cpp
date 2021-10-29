#include <cstdint>
#include <cstring>
#include <iostream>

// change to 1 to compile StaticBitset
#if 0

struct StaticBitset {
private:
	uint32_t *data;
	int count;
public:
	StaticBitset(int count, bool value)
		: data(new uint32_t[/*TODO*/])
		, count(count) {

		if (value) {
			// set *all* bits to 1
			memset(data, /*TODO*/, /*TODO*/);
		} else {
			// set *all* bits to 0
			memset(data, 0, /*TODO*/);
		}
	}

	/// Set value at @index to true
	void set(int index) {
		// TODO
	}

	/// Set value at @index to false
	void clear(int index) {
		// TODO
	}

	/// Get value at @index
	bool get(int index) const {
		// TODO
	}

	/// Get number of bits
	int size() const {
		return count;
	}

	/// Proxy of 1 bit of the StaticBitset
	struct proxy {
	private:
		StaticBitset *bitset;
		const int index;
		friend struct StaticBitset;
		proxy(StaticBitset *owner, int index)
			: bitset(owner)
			, index(index)
		{}
	public:
		proxy& operator=(bool value) {
			if (value) {
				bitset->set(index);
			} else {
				bitset->clear(index);
			}
			return *this;
		}

		operator bool () const {
			return bitset->get(index);
		}
	};

	/// Read/write access to a specific bit in the set
	proxy operator[](int index) {
		return proxy{this, index};
	}

	/// Const overload, read only access
	bool operator[](int index) const {
		return get(index);
	}
};

int main() {
	StaticBitset v(1000, false);

	// StaticBitset::proxy p; // Compiler error - proxy is meaningless without bitset

	for (int c = 0; c < v.size(); c++) {
		if (c % 2 == 0) {
			v[c] = true; // write
		}
	}

	int setCount = 0;
	for (int c = 0; c < v.size(); c++) {
		if (v[c]) { // read
			++setCount;
		}
	}

	std::cout << "Number of set bits = " << setCount;
	
	return 0;
}


#else

int main() {
	return 0;
}

#endif
