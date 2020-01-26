#pragma once
#include <iostream>
#include <algorithm>
#include "TritSet.h"

class Reference
{
public:
	Reference(TritSet &, size_t);
	Reference(Reference const &);
	~Reference();
	Reference & operator=(Trit const &);
	Reference & operator=(Reference const &);
	Trit getTrit() const;
	size_t getpos() const;
	operator Trit();
	friend bool operator==(Trit const & a, Reference const & b);
	friend bool operator==(Reference const & b, Trit const & a);
	friend bool operator==(Reference const & a, Reference const & b);
private:
	Reference();
	size_t getIndInBlock() const;
	static Block getMask(size_t);
	TritSet & tritset;
	size_t pos;
	friend std::ostream& operator<<(std::ostream &, const Trit &);
	friend std::ostream& operator<<(std::ostream &, const Reference &);
};

