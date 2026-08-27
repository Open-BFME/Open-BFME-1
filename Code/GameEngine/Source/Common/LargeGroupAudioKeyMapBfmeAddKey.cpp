// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: behavior-derived LargeGroupAudioKeyMap key registration,
// retail 0x003D46A0, 205 bytes. Two callers feed it AsciiString tokens; the
// method interns the token in the global no-case tree, retains its record and
// sets the record's numbered bit in this map.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
// Pull the real STLport tree/iterator implementation (its operator-> inlining
// is byte-significant), while leaving vector available for the retail by-value
// resize declaration below. STLport's stock vector declares the fill by const
// reference and would create a four-byte temporary that retail does not have.
#define _STLP_INTERNAL_VECTOR_H
#include "Common/AsciiString.h"
#include <stl/_tree.h>

namespace _STL
{

template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return m_wordsBegin; }
	unsigned int size() const { return m_wordsEnd - m_wordsBegin; }
	void resize(unsigned int count, Type value);

protected:
	Type *m_wordsBegin;
	Type *m_wordsEnd;
	Type *m_wordsCapacity;
};

}

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

struct Rva003D3F90Value
{
	unsigned int m_key;
	unsigned int m_useCount;
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;
typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair,
	_STL::_Select1st<Rva003D3F90Pair>, BfmeStringNoCaseLess,
	_STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

extern Rva003D3F90Tree g_lgaKeyRecords;
extern unsigned int g_lgaNextKey;

class LargeGroupAudioKeyMap :
	public _STL::vector<void *, _STL::allocator<void *> >
{
public:
	void bfmeAddKey(const AsciiString &name);
};

// ?bfmeAddKey@LargeGroupAudioKeyMap@@QAEXABVAsciiString@@@Z
void LargeGroupAudioKeyMap::bfmeAddKey(const AsciiString &name)
{
	Rva003D3F90Value empty = { 0, 0 };
	Rva003D3F90Pair value(name, empty);
	_STL::pair<Rva003D3F90Tree::iterator, bool> inserted =
		g_lgaKeyRecords.insert_unique(value);

	++inserted.first->second.m_useCount;
	if (inserted.second)
		inserted.first->second.m_key = g_lgaNextKey++;

	unsigned int key = inserted.first->second.m_key;
	unsigned int word = key >> 5;
	unsigned int mask = 1 << (key & 0x1F);
	if (word >= size())
		resize(word + 1, 0);
	((unsigned int *)begin())[word] |= mask;
}
