// ??1Gen_dtor_003c9b30@@UAE@XZ
// partial score=0.3 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Real (complete-object) destructor reached by the scalar-deleting-destructor
// thunk already scaffolded as Gen_dtor_003c9b30 (Code/gen_small/dtors_005.cpp,
// 0x003C9B30, calling ILT 0x00018A2F straight through with no this-adjustment).
// Retail 0x003C97B0, 366 bytes. Tears down: a vector of owned polymorphic
// pointers (elements deleted then buffer freed), one owned Gen_003C55F0
// pointer (non-virtual dtor + operator delete), an embedded Gen_003BA740 tree
// (already landed, 0x003BA740), a second vector of 8-byte POD elements
// (buffer only, no element dtor), and seven BFMERetailAsciiString members.
//
// STATUS: partial -- structure/offsets below reproduce the field reads and
// call targets in the disassembly, but retail's body has NO vtable-pointer
// store anywhere (a plain user-written virtual destructor in this shape
// always emits one here), so byte match was not reached before the body's
// per-target time budget ran out. See reverse/re_attempts.log for the note.

#include "ascii_string.h"
#include <vector>
#include <map>

class BFMERetailAsciiString : public AsciiString
{
public:
	~BFMERetailAsciiString();
};

class Gen_003C55F0
{
public:
	~Gen_003C55F0();
};

class Gen003C97B0PolyElement
{
public:
	virtual ~Gen003C97B0PolyElement();
};

// upstream layout: reverse-established in Gen_003BA740TreeOwnerDtor.cpp
struct Gen_003BA740Object
{
	virtual ~Gen_003BA740Object();
};
struct Gen_t_003b9fa0_p4pod
{
	Gen_003BA740Object *m_value;
};
typedef _STL::pair<const int, Gen_t_003b9fa0_p4pod> Gen_003BA740Pair;
typedef _STL::_Rb_tree<int, Gen_003BA740Pair,
	_STL::_Select1st<Gen_003BA740Pair>, _STL::less<int>,
	_STL::allocator<Gen_003BA740Pair> > Gen_003BA740Tree;
class Gen_003BA740 : public Gen_003BA740Tree
{
public:
	~Gen_003BA740();
};

struct Gen003C97B0Pod8
{
	int m_a;
	int m_b;
};

class Gen003C97B0VecAOwner
{
public:
	~Gen003C97B0VecAOwner()
	{
		for (std::vector<Gen003C97B0PolyElement *>::iterator it = m_vecA.begin();
			it != m_vecA.end(); ++it)
		{
			if (*it)
				delete *it;
		}
		m_vecA.clear();
	}

private:
	std::vector<Gen003C97B0PolyElement *> m_vecA;
};

class Gen003C97B0OwnedPtrOwner
{
public:
	~Gen003C97B0OwnedPtrOwner()
	{
		if (m_ownedPtr)
			delete m_ownedPtr;
	}

private:
	Gen_003C55F0 *m_ownedPtr;
};

class Gen003C97B0Base
{
public:
	virtual ~Gen003C97B0Base() {}
};

class Gen_dtor_003c9b30 : public Gen003C97B0Base
{
private:
	BFMERetailAsciiString m_str04;
	BFMERetailAsciiString m_str0c;
	BFMERetailAsciiString m_str10;
	BFMERetailAsciiString m_str14;
	std::vector<Gen003C97B0Pod8> m_vecB;			// +0x20..+0x2c
	BFMERetailAsciiString m_str2c;
	Gen003C97B0VecAOwner m_vecA;				// +0x30..+0x3c
	Gen003C97B0OwnedPtrOwner m_ownedPtr;			// +0x3c
	Gen_003BA740 m_tree;					// +0x40
	unsigned char m_gap[8];
	BFMERetailAsciiString m_str54;
	BFMERetailAsciiString m_selfStr;
};

void gen003c97b0_force_instantiation()
{
	Gen_dtor_003c9b30 v;
	(void)v;
}
