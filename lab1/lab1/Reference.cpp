#include "Reference.h"


Block Reference::getMask(size_t pos)
{
	Block mask = 1;
	return (mask << pos);
}

Reference::Reference(TritSet & tritset, size_t pos) : tritset(tritset), pos(pos)
{
}

Reference::Reference(Reference const &ref) : pos(ref.pos) , tritset(ref.tritset)
{
}





Reference::~Reference()
{
}


size_t Reference::getIndInBlock() const
{
	return (this->pos % (tritset.BITS_PER_BLOCK / 2)) * 2;
}

Trit Reference::getTrit() const
{
	if (pos >= tritset.maxTritsCnt())return Unknown;
	Block bit1 = 0;
	Block bit2 = 0;
	bit1 = (tritset.getBlock(pos) >> getIndInBlock()) & 1;
	bit2 = (tritset.getBlock(pos) >> (getIndInBlock() + 1)) & 1;
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

size_t Reference::getpos() const
{
	return this->pos;
}

Reference::operator Trit()
{
	return this->getTrit();
}

Reference & Reference::operator=(Trit const & trit)
{
	if (pos >= tritset.maxTritsCnt() && trit == Unknown)return *this;
	if (pos >= tritset.maxTritsCnt()) {
		tritset.trits = tritset.Allocate(pos+1);
	}
	switch (trit) {
	case False:  tritset.getBlock(pos) &= ~getMask(getIndInBlock()); tritset.getBlock(pos) &= ~getMask(getIndInBlock() + 1); break;
	case Unknown: tritset.getBlock(pos) &= ~getMask(getIndInBlock() + 1); tritset.getBlock(pos) |= getMask(getIndInBlock()); break;
	case True: tritset.getBlock(pos) |= getMask(getIndInBlock() + 1); tritset.getBlock(pos) |= getMask(getIndInBlock()); break;
	default: break;
	}
	return *this;
}

Reference & Reference::operator=(Reference const &ref)
{
	*this = ref.getTrit();
	return *this;
}


bool operator==(Trit const & a, Reference const & b) {
	return a == b.getTrit();
}

bool operator==(Reference const & b, Trit const & a) {
	return a == b.getTrit();
}

bool operator==(Reference const & a, Reference const & b)
{
	return a.getTrit() == b.getTrit();
}



std::ostream & operator<<(std::ostream &out,Trit const & trit)
{
	switch (trit)
	{
	case False: out << "False"; break;
	case Unknown: out << "Unknown"; break;
	case True: out << "True"; break;
	default:
		break;
	}
	return out;
}

std::ostream & operator<<(std::ostream & out, Reference const & ref)
{
	Trit trit = ref.getTrit();
	switch (trit)
	{
	case False: out << "False"; break;
	case Unknown: out << "Unknown"; break;
	case True: out << "True"; break;
	default:
		break;
	}
	return out;
}
