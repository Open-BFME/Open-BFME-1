// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: LGA_MemberObj's member release helper, retail 0x003D4080,
// 264 bytes. The destructor at 0x003D4490 calls its ILT at 0x00034DC9 before
// releasing the bitmap vector at offset zero.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "Common/AsciiString.h"
#include <stl/_tree.h>

namespace _STL
{

template <class Type, class Allocator>
class vector
{
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
	int m_useCount;
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;
typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair,
	_STL::_Select1st<Rva003D3F90Pair>, BfmeStringNoCaseLess,
	_STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

extern Rva003D3F90Tree g_lgaKeyRecords;
extern unsigned int g_lgaNextKey;

class LGA_MemberObj
{
public:
	unsigned int *m_wordsBegin;
	unsigned int *m_wordsEnd;
	unsigned int *m_wordsCapacity;
};

// ?bfmeClearMembers@@YAXPAVLGA_MemberObj@@@Z
void bfmeClearMembers(LGA_MemberObj *self)
{
	Rva003D3F90Tree::iterator record = g_lgaKeyRecords.begin();
	bool rebuildNextKey = false;

	while (record != g_lgaKeyRecords.end())
	{
		unsigned int key = record->second.m_key;

		if (self->m_wordsEnd - self->m_wordsBegin > key >> 5)
		{
			unsigned int mask = 1 << (key & 0x1F);
			if (self->m_wordsBegin[key >> 5] & mask)
			{
				--record->second.m_useCount;
				if (record->second.m_useCount > 0)
				{
					++record;
					continue;
				}
				else
				{
					if (key == g_lgaNextKey)
						rebuildNextKey = true;

					Rva003D3F90Tree::iterator next = record;
					++record;
					g_lgaKeyRecords.erase(next);
					continue;
				}
			}
		}

		++record;
	}

	if (rebuildNextKey)
	{
		g_lgaNextKey = 0;
		record = g_lgaKeyRecords.begin();
		while (record != g_lgaKeyRecords.end())
		{
			if ((int)record->second.m_key >= (int)g_lgaNextKey)
				g_lgaNextKey = record->second.m_key + 1;
			++record;
		}
	}
}
