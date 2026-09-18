// ?handle@Gen00362760Elem@@QAEXPAX@Z
// partial score=0.93 date=2026-09-12
// The retail caller at 0x00362760 (ledger symbol address-derived) walks
// 0x58-byte army elements and calls ILT 0x0001D0E8, which routes to this
// body.  That proves the address-derived dispatch relation; no semantic
// method name is proven, so no real-name pin is added.
// LivingWorldArmy's +0x04 name, +0x34 count, and 0xB4 element size are
// witnessed by INILivingWorldPlayerArmy.cpp and LivingWorldArmyAssign.cpp.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

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

class LivingWorldArmy
{
public:
	virtual ~LivingWorldArmy();
	AsciiString getName() const;

	int getCount() const
	{
		return *reinterpret_cast<const int *>( reinterpret_cast<const char *>( this ) + 0x34 );
	}

private:
	char m_unmodelled04[ 0x2C ];
	_STL::vector<LivingWorldArmy> m_armies;
	char m_unmodelled3C[ 0x78 ];
};

#pragma comment(linker, "/alternatename:?getName@LivingWorldArmy@@QBE?AVAsciiString@@XZ=?j_000041d3@@YAXXZ")

class Rva00362550ArmyVisitor
{
public:
	virtual void slot0();
	virtual void visit( const AsciiString &name, int count );
};

class Rva00362550ArmyVisitorPtr
{
public:
	__forceinline Rva00362550ArmyVisitor *operator->() const
	{
		if( m_ptr == 0 )
			throw FunctorNotSet();
		return m_ptr;
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
	_STL::vector<LivingWorldArmy>::size_type i;
	i = 0;
	for( ; i < m_armies.size(); ++i )
	{
		LivingWorldArmy &army = *( m_armies.begin() + i );
		( *(Rva00362550ArmyVisitorPtr *)visitor )->visit(
			army.getName(), army.getCount() );
	}
}

// Probe result for this indexed vector shape: 220/219 bytes and 22
// non-relocation differences.  The remaining source-shape residue is the
// exact VC7.1 allocation of EBP as index versus EBX as byte offset together
// with retail's EH-state/count-load order.
