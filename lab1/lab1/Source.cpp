#include <iostream>
#include "TritSet.h"
#include "Reference.h"
#include <assert.h>




int main(int argc, char **argv) {
	size_t size = 100;
	TritSet set(size);
	size_t allocLen = set.capacity();
	assert(allocLen >= (size * 2 / 8 / sizeof(Block)));       // count of allocated blocks

	set[1000000] = Unknown;
	assert(allocLen == set.capacity());       // do not allocate memory

	assert(set[100000000] == Unknown);        // Unknown trits out of range
	if ((set[2000000]) == True) { assert(0); }  // false

	assert(allocLen == set.capacity());       // do not allocate memory

	set[10000] = True;
	assert(allocLen < set.capacity());        // allocate memory to store setted trit

	allocLen = set.capacity();

	set[10000] = Unknown;
	assert(allocLen == set.capacity());       // no memory operations

	set[5000] = False;
	assert(set[5000] == False);               // set trit
	assert(allocLen == set.capacity());       // no memory operations

	set.shrink();
	assert(allocLen > set.capacity());        // free memory to the value necessary to store last setted trit (set[5000]==False)

	{  /////////////////////////////////// operations tests start
		TritSet A(30);
		TritSet B(60);
		for (int i = 0; i < 30; i++) {
			B[i + 30] = False;
			if (i % 6 == 0) {
				A[i] = False;
				B[i] = True;
			}
			if (i % 6 == 1) {
				A[i] = Unknown;
				B[i] = True;
			}
			if (i % 6 == 2) {
				A[i] = True;
				B[i] = True;
			}
			if (i % 6 == 3) {
				A[i] = False;
				B[i] = Unknown;
			}
			if (i % 6 == 4) {
				A[i] = False;
				B[i] = False;
			}
			if (i % 6 == 5) {
				A[i] = Unknown;
				B[i] = Unknown;
			}
		}
		TritSet C = A & B;
		TritSet D = A | B;
		TritSet E = ~B;
		assert(C.capacity() == B.capacity());       // memory to store result

		for (int i = 0; i < 60; i++) {
			if (i >= 30) {						// Unknown , False
				assert(C[i] == False);			// A&B = false
				assert(D[i] == Unknown);		// A|B = unknown
				assert(E[i] == True);			// ~B = true
				continue;
			}
			if (i % 6 == 0) {					// False , True
				assert(C[i] == False);			// A&B = false
				assert(D[i] == True);			// A|B = true
				assert(E[i] == False);			// ~B = False
			}
			if (i % 6 == 1) {					// Unknown , True            
				assert(C[i] == Unknown);		// A&B = unknown
				assert(D[i] == True);			// A|B = true
				assert(E[i] == False);			// ~B = false
			}
			if (i % 6 == 2) {					// True , True
				assert(C[i] == True);			// A&B = true
				assert(D[i] == True);			// A|B = true
				assert(E[i] == False);			// ~B = false
			}
			if (i % 6 == 3) {					// False , Unknown
				assert(C[i] == False);			// A&B = false
				assert(D[i] == Unknown);		// A|B = unknown
				assert(E[i] == Unknown);		// ~B = unknown
			}
			if (i % 6 == 4) {					// False , False
				assert(C[i] == False);			// A&B = false
				assert(D[i] == False);			// A|B = false
				assert(E[i] == True);			// ~B = true
			}
			if (i % 6 == 5) {					// Unknown , Unknown
				assert(C[i] == Unknown);		// A&B = unknown
				assert(D[i] == Unknown);		// A|B = unknown
				assert(E[i] == Unknown);		// ~B = unknown
			}
		}
	}   ////////////////////////////////////////// operations tests end.

	{   // cardinality, trim, length  tests
		TritSet A(40);
		for (int i = 0; i < 20; i++)A[i] = True;
		for (int i = 20; i < 35; i++)A[i] = Unknown;
		for (int i = 35; i < 40; i++)A[i] = False;
		assert(A.cardinality(True) == 20);
		assert(A.cardinality(False) == 5);
		assert(A.cardinality(Unknown) == 15);
		std::unordered_map<Trit, int, std::hash<int>>trits_counts = A.cardinality();
		assert(trits_counts[True] == 20);
		assert(trits_counts[False] == 5);
		assert(trits_counts[Unknown] == 15);

		A.trim(35);
		for (int i = 35; i < 40; i++)assert(A[i] == Unknown);
		assert(A.length() == 20);
	}

	return 0;
}