// ?handle@Gen00362760Elem@@QAEXPAX@Z
// partial score=0.93 date=2026-09-12
// The element callback at retail RVA 0x00362550.
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
	AsciiString getName() const
	{
		return *reinterpret_cast<const AsciiString *>( reinterpret_cast<const char *>( this ) + 4 );
	}

	int getCount() const
	{
		return *reinterpret_cast<const int *>( reinterpret_cast<const char *>( this ) + 0x34 );
	}

private:
	char m_unmodelled[ 0xB0 ];
};

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
	unsigned int i = 0;
	if( m_armies.size() == 0 )
		return;

	unsigned int offset = 0;
	do
	{
		LivingWorldArmy &army = *(LivingWorldArmy *)( (char *)m_armies.begin() + offset );
		( *(Rva00362550ArmyVisitorPtr *)visitor )->visit(
			army.getName(), army.getCount() );
		++i;
		offset += sizeof( LivingWorldArmy );
	}
	while( i < m_armies.size() );
}
