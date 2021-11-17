#include <cstdint>
#include <cstring>
#include <iostream>
#include <type_traits>
#include <cassert>

struct StaticBitset {
private:
	// implementation details for the container type
	using ContainerType = uint32_t;
	constexpr static size_t containerTypeBytesSize = sizeof(ContainerType);
	constexpr static size_t containerTypeBitsSize = containerTypeBytesSize * 8;
	static_assert(std::is_integral_v<ContainerType>, "The container type must be integral!");
	static_assert(std::is_unsigned_v<ContainerType>, "The container type must be unsigned!");

private:
	// fields of the bitset
	ContainerType* data;
	int bitCount;
public:
	StaticBitset(int bitCount, bool value)
		: data(new ContainerType[getCountOfContainerType(bitCount)])
		, bitCount(bitCount) {

		if (value) {
			// set *all* bits to 1
			memset(data, 0b11111111, getCountOfContainerType(bitCount) * containerTypeBytesSize);
		}
		else {
			// set *all* bits to 0
			memset(data, 0, getCountOfContainerType(bitCount) * containerTypeBytesSize);
		}
	}

	StaticBitset(const StaticBitset& other)
		: data(new ContainerType[getCountOfContainerType(other.bitCount)])
		, bitCount(other.bitCount)
	{
		memcpy(data, other.data, getCountOfContainerType(other.bitCount));
		// Equivalent to:
		//for (size_t i = 0; i < getCountOfContainerType(other.bitCount); ++i)
		//{
		//	// no concerns as Container type is integral => trivially (operator=)-able
		//	data[i] = other.data[i];
		//}
	}

	~StaticBitset()
	{
		delete[] data;
	}

	StaticBitset& operator=(const StaticBitset& other)
	{
		// if the next line throws we are better off to leave it and pass it up
		ContainerType* newData = new ContainerType[getCountOfContainerType(other.bitCount)];

		memcpy(data, other.data, getCountOfContainerType(other.bitCount));
		// Equivalent to:
		//for (size_t i = 0; i < getCountOfContainerType(other.bitCount); ++i)
		//{
		//	// no concerns as Container type is integral => trivially (operator=)-able
		//	data[i] = other.data[i];
		//}

		delete[] data;
		data = newData;
		bitCount = other.bitCount;
		return *this;
	}

	// All named functions throw on error
	// operators [] just assert, as per convention

	/// Set value at @index to true
	void set(int index) {
		if (0 > index || index >= bitCount)
		{
			throw std::out_of_range("Access outside bitfield");
		}

		const IndexingPair idxPair = getIndexingPairForBitIndex(index);
		data[idxPair.containerTypeIndex] |= idxPair.getMask();
	}

	/// Set value at @index to false
	void clear(int index) {
		if (0 > index || index >= bitCount)
		{
			throw std::out_of_range("Access outside bitfield");
		}

		const IndexingPair idxPair = getIndexingPairForBitIndex(index);
		data[idxPair.containerTypeIndex] &= idxPair.getMaskInverted();
	}

	/// Flip the value at @index
	void flip(int index) {
		if (0 > index || index >= bitCount)
		{
			throw std::out_of_range("Access outside bitfield");
		}

		const IndexingPair idxPair = getIndexingPairForBitIndex(index);
		data[idxPair.containerTypeIndex] ^= idxPair.getMask();
	}

	/// Get value at @index
	bool get(int index) const {
		if (0 > index || index >= bitCount)
		{
			throw std::out_of_range("Access outside bitfield");
		}
		return this->operator[](index);
	}

	/// Get number of bits
	int size() const {
		return bitCount;
	}

	/// Proxy of 1 bit of the StaticBitset
	struct proxy {
	private:
		StaticBitset* bitset;
		const int index;
		friend struct StaticBitset;
		proxy(StaticBitset* owner, int index)
			: bitset(owner)
			, index(index)
		{
			if (index < 0 || bitset->size() <= index)
			{
				throw std::out_of_range("The proxy must point to an element in the bitset!");
			}
		}
	public:
		proxy& operator=(bool value) {
			if (value) {
				bitset->set(index);
			}
			else {
				bitset->clear(index);
			}
			return *this;
		}

		proxy& operator&=(bool value) {
			if (value && bitset->get(index)) {
				bitset->set(index);
			}
			else {
				bitset->clear(index);
			}
			return *this;
		}

		proxy& operator|=(bool value) {
			if (value || bitset->get(index)) {
				bitset->set(index);
			}
			else {
				bitset->clear(index);
			}
			return *this;
		}

		proxy& operator^=(bool value) {
			if (value ^ bitset->get(index)) {
				bitset->set(index);
			}
			else {
				bitset->clear(index);
			}
			return *this;
		}

		void flip()
		{
			bitset->flip(index);
		}

		operator bool() const {
			return bitset->get(index);
		}
	};

	/// Read/write access to a specific bit in the set
	proxy operator[](int index) {
		assert(0 <= index && index < bitCount && "The index has to be inside the bitfield");
		return proxy(this, index);
	}

	/// Const overload, read only access
	bool operator[](int index) const {
		assert(0 <= index && index < bitCount && "The index has to be inside the bitfield");

		const IndexingPair idxPair = getIndexingPairForBitIndex(index);
		return data[idxPair.containerTypeIndex] & idxPair.getMask();
	}
private:
	// Returns the least amount of container types
	// that will have enough bits to contain the bit count
	constexpr static size_t getCountOfContainerType(int bitCount)
	{
		return (bitCount + containerTypeBitsSize - bitCount % containerTypeBytesSize) / containerTypeBitsSize;
	}

	// Returns a mask for the bit at the supplied index
	// Asserts that the index is strictly-less than
	// the bit count of the container type
	// E.g.
	// index == 0 => 0b1
	// index == 1 => 0b10
	// index == 2 => 0b100
	// etc
	constexpr static ContainerType getMaskForIdx(size_t bitIndex)
	{
		assert(bitIndex < containerTypeBitsSize && "Cannot mask outside the bits of the container type!");
		return ContainerType(1) << bitIndex;
	}

	// A structure analogous to std::pair<size_t, size_t>
	// but with named fields
	// Represents the indeces
	// in the container type array that we have to access
	// as well as the bit index inside the memory of the container type
	// Can produce masks for the bit index
	struct IndexingPair
	{
		const size_t containerTypeIndex;
		const size_t bitIndex;

		ContainerType getMask() const { return getMaskForIdx(bitIndex); }
		ContainerType getMaskInverted() const { return ~getMask(); }
	};

	// Returns the indexing pair for the given bit index
	constexpr static IndexingPair getIndexingPairForBitIndex(int bitIdx)
	{
		return IndexingPair{ bitIdx / containerTypeBitsSize, bitIdx % containerTypeBitsSize };
	}

};

int main() {
	StaticBitset v(1000, false);
	StaticBitset v2(33, false);
	StaticBitset v3(0, false);

	try {
		v3.set(0);
		return 1; // should not get here
	}
	catch (...)
	{
		// should catch
	}

	v2.set(0);
	v2.set(1);
	v2.set(2);
	v2.set(32);

	//StaticBitset::proxy p; // Compiler error - proxy is meaningless without bitset

	for (int c = 0; c < v.size(); c++) {
		if (c % 2 == 0) {
			v[c] = true; // write
		}
		// Alternatives in the case when v is initialized to all false:
		// v[c] = c % 2 == 0;
		// v[c] |= c % 2 == 0;
		 //v[c] ^= c % 2 == 0;
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

