#pragma once
#include <iostream>
#include <algorithm>
#include <unordered_map>
class Reference;
typedef unsigned int Block;
enum Trit
{
	False,               // 00
	Unknown,			 // 01
	True				 // 11
};

class TritSet
{
	friend class Reference;
public:
	TritSet(size_t);
	TritSet();
	TritSet(TritSet const &);
	~TritSet();
	const size_t capacity() const;
	Reference operator[](size_t);
	TritSet & operator=(TritSet const &);
	TritSet operator~() const;
	void shrink();
	const size_t cardinality(Trit) const;
	const std::unordered_map<Trit, int, std::hash<int>> cardinality() const;
	const size_t length() const;
	void trim(size_t);
	friend TritSet operator&(TritSet const & a, TritSet const & b);
	friend TritSet operator|(TritSet const & a, TritSet const & b);
	
private:
	void swap(TritSet &);
	const Trit operator[](size_t) const;
	const size_t maxTritsCnt() const;
	Block emptyBlock() const;
	Block* Allocate(size_t);
	const size_t mostSignificantTrit() const;
	size_t getBlocksCnt(size_t) const;
	Block & getBlock(size_t) const;
	const size_t whichBlock(size_t) const;
	Block *trits;
	size_t blocks_cnt;
	const size_t BITS_PER_BLOCK;
};

