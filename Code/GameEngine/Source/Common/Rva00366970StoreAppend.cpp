// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The embedded Living World store keeps 0x58-byte records in the vector at
// this+0x18.  The append path initializes the new record only when STLport
// grows the vector.  Retail writes the new index and copies the two trailing
// strings after the reallocating insert.

#include "Common/AsciiString.h"

struct Rva00366890Element
{
	char m_body[ 0x58 ];
};

class Rva00366970Store;

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl BfmeElementConstruct( Type *destination, const Type &value );

template <class Type, class Allocator>
class vector
{
public:
	friend class ::Rva00366970Store;

protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

public:
	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};
}

class Rva00366970Store
{
public:
	void append( const Rva00366890Element *value,
		const AsciiString &first, const AsciiString &second );

private:
	char m_beforeVector[ 0x18 ];
	_STL::vector<Rva00366890Element, _STL::allocator<Rva00366890Element> > m_entries;
};

void Rva00366970Store::append( const Rva00366890Element *value,
	const AsciiString &first, const AsciiString &second )
{
	typedef _STL::vector<Rva00366890Element,
		_STL::allocator<Rva00366890Element> > EntryVector;
	Rva00366970Store *owner = this;
	EntryVector *entries = &owner->m_entries;
	Rva00366890Element *finish = owner->m_entries.m_finish;

	if ( finish != entries->m_end_of_storage )
	{
		_STL::BfmeElementConstruct( finish, *value );
		entries->m_finish = entries->m_finish + 1;
	}
	else
	{
		const _STL::__false_type &tag =
			*reinterpret_cast<const _STL::__false_type *>( &value );
		entries->_M_insert_overflow( finish, *value, tag, 1, true );
	}

	unsigned int index =
		(unsigned int)( entries->m_finish - entries->m_start ) - 1;
	Rva00366890Element *last = owner->m_entries.m_finish - 1;
	*reinterpret_cast<unsigned int *>( last->m_body + 4 ) = index;
	*reinterpret_cast<AsciiString *>( last->m_body + 0x10 ) = first;
	*reinterpret_cast<AsciiString *>( last->m_body + 0x14 ) = second;
}
