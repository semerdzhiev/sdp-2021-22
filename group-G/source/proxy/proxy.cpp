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

private:
	// fields of the bitset
	ContainerType* data;
	const int bitCount;
public:
	StaticBitset(int bitCount, bool value)
		: data(new ContainerType[getCountOfContainerType(bitCount)])
		, bitCount(bitCount) {

		if (bitCount == 0)
		{
			delete[] data;
			throw std::exception("A static bitset cannot be initialized with a count of zero(doesn't make sense)!");
		}

		if (value) {
			// set *all* bits to 1
			memset(data, 0b11111111, getCountOfContainerType(bitCount) * containerTypeBytesSize);
			// relying on the fact we are in two's complement
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
		for (size_t i = 0; i < getCountOfContainerType(other.bitCount); ++i)
		{
			data[i] = other.data[i];
		}
	}

	~StaticBitset()
	{
		delete[] data;
	}

	StaticBitset& operator=(const StaticBitset& other)
	{
		if (bitCount != other.bitCount)
		{
			throw std::exception("Attempting to assign static bitsets of different arity. Cannot do that as it is ambiguous which bits to copy - least significant or most significant");
		}

		for (size_t i = 0; i < getCountOfContainerType(bitCount); ++i)
		{
			data[i] = other.data[i];
		}
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

		const IndexingPair idxPair = getIndexingPairForBitIndex(index);
		return data[idxPair.containerTypeIndex] & idxPair.getMask();
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
		return proxy{ this, index };
	}

	/// Const overload, read only access
	bool operator[](int index) const {
		assert(0 <= index && index < bitCount && "The index has to be inside the bitfield");
		return get(index);
	}
private:
	static size_t getCountOfContainerType(int bitCount)
	{
		return (bitCount + containerTypeBitsSize - bitCount % containerTypeBytesSize) / containerTypeBitsSize;
	}

	constexpr static ContainerType getMaskForIdx(size_t bitIndex)
	{
		assert(bitIndex <= containerTypeBitsSize && "Cannot mask outside the bits of the container type!");
		return 1 << bitIndex;
	}

	struct IndexingPair
	{
		const size_t containerTypeIndex;
		const size_t bitIndex;

		ContainerType getMask() const { return getMaskForIdx(bitIndex); }
		ContainerType getMaskInverted() const { return ~getMask(); }
	};

	static IndexingPair getIndexingPairForBitIndex(int idx)
	{
		return IndexingPair{ idx / containerTypeBitsSize, idx % containerTypeBitsSize };
	}

};

int main() {
	StaticBitset v(1000, false);
	StaticBitset v2(33, false);

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