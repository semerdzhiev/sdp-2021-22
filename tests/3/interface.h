#include <iostream>
#include <set>
#include <string>

///
/// Represents a multiset of words
///
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
/// Implement all methods of this class
/// 
class WordsMultiset {
public:
	/// Adds times occurences of word to the container
	///
	/// For example, add("abc") adds the word "abc" once,
	/// while add("abc", 4) adds 4 occurrances.
	void add(const std::string& word, size_t times = 1);

	/// Checks whether word is contained in the container
	bool contains(const std::string& word) const;

	/// Number of occurrances of word 
	size_t countOf(const std::string& word) const;

	/// Number of unique words in the container
	size_t countOfUniqueWords() const;

	/// Returns a multiset of all words in the container
	std::multiset<std::string> words() const;
	
	// You can add additional members if you need to
};

///
/// Results of the comparison of two streams of words
/// DO NOT modify this class
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
class ComparisonReport {
public:
	/// A multiset of all words that exist in both streams
	WordsMultiset commonWords;

	/// Multisets of words unique to the two streams
	/// The first element of the array contains the words that are unique
	/// to the first stream (a) and the second one -- to the second stream (b)
	WordsMultiset uniqueWords[2];
};

/// 
/// Can be used to compare two streams of words
///
class Comparator {
public:
	ComparisonReport compare(std::istream& a, std::istream& b);

	// You can add additional members if you need to
};
