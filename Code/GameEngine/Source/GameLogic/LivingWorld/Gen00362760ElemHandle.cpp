// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x00362550, 219 bytes.  Reached only through ILT 0x0001D0E8 from the
// generated caller at 0x00362760, which bounds-checks an index into a vector of
// 0x58-byte elements at +0x18 and calls this with the element as `this`.
// The element's vector at +0x30 holds 0xB4-byte LivingWorldArmy records: each
// is passed to ?getName@LivingWorldArmy (ILT 0x000041D3, pinned from the
// currentCommandPoints call site) and its +0x34 count, and both go to the
// visitor's slot +4.  A null visitor throws FunctorNotSet (vtable 0x010766DC,
// RTTI .?AVFunctorNotSet@@).  Owner and method names stay address-derived.

#define _STLP_USE_NEWALLOC 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <vector>
#include "Common/AsciiString.h"

#include <exception>

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};

// 0xB4-byte record. +0x28..+0x33 are plain words and +0x34 an int, as the
// matched copyFrom 0x00361B30 (LivingWorldArmyAssign.cpp) copies them.
class LivingWorldArmy
{
public:
	AsciiString getName() const;

	int getCount() const
	{
		return *reinterpret_cast<const int *>( reinterpret_cast<const char *>( this ) + 0x34 );
	}

private:
	char m_header[ 4 ];
	char m_unmodelled04[ 0x38 ];
	char m_unmodelled3C[ 0x78 ];
};

class Rva00362550ArmyVisitor
{
public:
	virtual void slot0();
	virtual void visit( const AsciiString &name, int count );
};

// Functor-style holder: the call operator throws FunctorNotSet on a null
// target, then forwards to vtable slot +4.  The arguments are evaluated
// before the inlined null check, which is why retail loads the count
// before the branch.
class Rva00362550ArmyVisitorPtr
{
public:
	void operator()( const AsciiString &name, int count ) const
	{
		if( m_ptr == 0 )
			throw FunctorNotSet();
		m_ptr->visit( name, count );
	}

	Rva00362550ArmyVisitor *m_ptr;
};

class Gen00362760Elem
{
public:
	void handle( void *visitor );

private:
	char m_unmodelled[ 0x30 ];
	_STL::vector<LivingWorldArmy> m_armies;
};

void Gen00362760Elem::handle( void *visitor )
{
	const Rva00362550ArmyVisitorPtr &functor =
		*(const Rva00362550ArmyVisitorPtr *)visitor;
	for( _STL::vector<LivingWorldArmy>::size_type i = 0; i < m_armies.size(); ++i )
	{
		const LivingWorldArmy &army = m_armies[ i ];
		functor( army.getName(), army.getCount() );
	}
}
