#include "TritSet.h"
#include "Reference.h"

const size_t TritSet::maxTritsCnt() const {
	return this->blocks_cnt * BITS_PER_BLOCK / 2;   // 4 trits in 1 byte;
}

size_t TritSet::getBlocksCnt(size_t size) const
{
	return (2 * size / BITS_PER_BLOCK) + (2 * size % BITS_PER_BLOCK != 0);
}

Block & TritSet::getBlock(size_t pos) const
{
	return trits[whichBlock(pos)];
}

const size_t TritSet::whichBlock(size_t ind) const
{
	return 2 * ind / BITS_PER_BLOCK;
}

Reference TritSet::operator[](size_t ind) {

	return Reference(*this, ind);
}

void TritSet::swap(TritSet & tritset)
{
	std::swap(this->blocks_cnt, tritset.blocks_cnt);
	std::swap(this->trits, tritset.trits);
}

const Trit TritSet::operator[](size_t ind) const
{
	Block block = getBlock(ind);
	size_t pos = (ind % (BITS_PER_BLOCK / 2)) * 2;
	if (ind >= maxTritsCnt())return Unknown;
	Block bit1 = 0;
	Block bit2 = 0;
	bit1 = (block >> pos) & 1;
	bit2 = (block >> (pos + 1)) & 1;
	if (bit1 == 0 && bit2 == 0) {
		return False;
	}
	if (bit1 == 1 && bit2 == 0) {
		return Unknown;
	}
	if (bit1 == 1 && bit2 == 1) {
		return True;
	}
	return Unknown;
}

TritSet & TritSet::operator=(TritSet const & a)
{
	if (this != &a) {
		TritSet(a).swap(*this);
	}
	return *this;
}

const size_t TritSet::mostSignificantTrit() const
{
	if (blocks_cnt == 0)return this->maxTritsCnt();
	for (int it = blocks_cnt - 1; it >= 0; it--) {
		if (trits[it] != emptyBlock()) {
			for (int tritInBlock = BITS_PER_BLOCK / 2 - 1; tritInBlock >= 0; tritInBlock--) {
				size_t index = it*(BITS_PER_BLOCK / 2) + tritInBlock;
				if ((*this)[index] != Unknown)return index;
			}
		}
	}
	return this->maxTritsCnt();
}

Block TritSet::emptyBlock() const
{
	Block mask = 0;
	for (size_t bit = 0; bit < BITS_PER_BLOCK; bit++) {
		if (!(bit & 1)) {
			mask |= (1 << bit);
		}
	}
	return mask;
}

Block * TritSet::Allocate(size_t new_size)
{
	Block* new_ptr = new Block[getBlocksCnt(new_size)];

	for (size_t it = 0; it < std::min(this->blocks_cnt, getBlocksCnt(new_size)); it++) {
		new_ptr[it] = trits[it];
	}
	Block mask = emptyBlock();
	for (size_t it = this->blocks_cnt; it < getBlocksCnt(new_size); it++) {
		new_ptr[it] = mask;
	}
	delete[] this->trits;
	this->trits = nullptr;
	this->blocks_cnt = getBlocksCnt(new_size);
	return new_ptr;
}

void TritSet::shrink()
{
	size_t last = mostSignificantTrit() + 1;
	if (last == maxTritsCnt() + 1)last = 0;
	this->trits = Allocate(last);
}

const size_t TritSet::cardinality(Trit trit) const
{
	size_t last = mostSignificantTrit();
	if (last == maxTritsCnt())return 0;
	size_t cnt = 0;
	for (size_t it = 0; it <= last; it++) {
		if (trit == (*this)[it])cnt++;
	}
	return cnt;
}

const std::unordered_map<Trit, int, std::hash<int>> TritSet::cardinality() const
{
	std::unordered_map<Trit, int, std::hash<int>> counts;
	size_t last = mostSignificantTrit();
	if (last == maxTritsCnt())return counts;
	size_t cnt = 0;
	for (size_t it = 0; it <= last; it++) {
		counts[(*this)[it]]++;
	}
	return counts;
}

const size_t TritSet::length() const
{
	size_t last = mostSignificantTrit();
	return  last == maxTritsCnt() ? 0 : last + 1;
}

void TritSet::trim(size_t ind)
{
	size_t first = whichBlock(ind);
	for (size_t tritInBlock = ind % (BITS_PER_BLOCK / 2); tritInBlock < BITS_PER_BLOCK / 2; tritInBlock++) {
		size_t index = first*(BITS_PER_BLOCK / 2) + tritInBlock;
		(*this)[index] = Unknown;
	}
	if (mostSignificantTrit() == maxTritsCnt())return;
	size_t last = whichBlock(mostSignificantTrit());
	for (size_t current = first + 1; current <= last; current++) {
		trits[current] = emptyBlock();
	}
}



const size_t TritSet::capacity() const
{
	return this->blocks_cnt;
}


TritSet::TritSet(size_t size = 0) : BITS_PER_BLOCK(sizeof(Block) * 8)
{
	this->trits = this->Allocate(size);
}

TritSet::TritSet() : BITS_PER_BLOCK(sizeof(Block) * 8) , trits(nullptr) , blocks_cnt(0)
{
}

TritSet::TritSet(TritSet const & a) : BITS_PER_BLOCK(sizeof(Block) * 8) , blocks_cnt(a.blocks_cnt) , trits(new Block[a.blocks_cnt])
{
	for (size_t i = 0; i < blocks_cnt; i++) {
		trits[i] = a.trits[i];
	}
}


TritSet::~TritSet()
{
	delete[] this->trits;
	this->trits = nullptr;
}

TritSet operator&(TritSet const & a, TritSet const & b)
{
	size_t max_len = std::max(a.maxTritsCnt(), b.maxTritsCnt());
	TritSet result(max_len);
	for (size_t it = 0; it < result.blocks_cnt; it++) {
		Block b1 = a.blocks_cnt > it ? a.trits[it] : a.emptyBlock();
		Block b2 = b.blocks_cnt > it ? b.trits[it] : b.emptyBlock();
		result.trits[it] = (b1 & b2);
	}
	return result;
}


TritSet operator|(TritSet const & a, TritSet const & b)
{
	size_t max_trits = std::max(a.maxTritsCnt(), b.maxTritsCnt());
	TritSet result(max_trits);
	for (size_t it = 0; it < result.blocks_cnt; it++) {
		Block b1 = a.blocks_cnt > it ? a.trits[it] : a.emptyBlock();
		Block b2 = b.blocks_cnt > it ? b.trits[it] : b.emptyBlock();
		result.trits[it] = (b1 | b2);
	}
	return result;
}

TritSet TritSet::operator~() const
{
	TritSet res(*this);
	for (size_t it = 0; it < this->capacity(); it++) {
		res.trits[it] = ~trits[it];
		for (size_t tritInBlock = 0; tritInBlock < BITS_PER_BLOCK / 2; tritInBlock++) {
			size_t index = it*(BITS_PER_BLOCK / 2) + tritInBlock;
			if (res[index] == Unknown)res[index] = Unknown;
		}
	}
	return res;
}

