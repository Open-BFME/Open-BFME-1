// Sorted pointer-vector insertion used by BfmeObjHC::bfmeDoHC's helper
// cluster at retail 0x003C58E0.  The caller passes the STLport vector as the
// first stack argument and the record as the second; this is not a thiscall.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS
#define _M_insert_overflow j_000100d7
#include <vector>
#undef _M_insert_overflow

class Rva003C5890Item
{
public:
	char m_pad00[0x24];
	float m_sortKey;
};

class Rva003C56F0Vector
{
public:
	_STL::vector<Rva003C5890Item *> m_items;
};

// ?Rva003C58E0Insert@@YGXPAVRva003C56F0Vector@@PAVRva003C5890Item@@@Z
void __stdcall Rva003C58E0Insert( Rva003C56F0Vector *vector,
	Rva003C5890Item *item )
{
	unsigned int index = 0;
	Rva003C5890Item **begin = vector->m_items.begin();
	if( vector->m_items.size() > 0 )
	{
		while( index < vector->m_items.size() )
		{
			if( item->m_sortKey < vector->m_items[index]->m_sortKey )
			{
				vector->m_items.insert( begin + index, item );
				return;
			}
			++index;
		}
	}
	vector->m_items.push_back( item );
}
