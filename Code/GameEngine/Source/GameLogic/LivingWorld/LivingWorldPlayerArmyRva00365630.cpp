// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// LivingWorldPlayerArmy method at retail 0x00365630 (405B, ret 8). Its only
// caller, 0x003B4510, passes the record 0x003B43D0 returns (an element of the
// campaign manager's 0x58-stride player-army vector) as `this`, and the body
// reads a vector of 0xB4-byte LivingWorldArmy records at +0x30. For each army
// here it looks the name up in the first argument's list with findArmy
// (0x00362BE0), appends the found record to the second argument's +0x30
// vector, then erases it from the first by the index findArmy reported.
// The method name is not proven, so it keeps the address.
#include "PreRTS.h"
#include <vector>

class LivingWorldArmy
{
public:
	LivingWorldArmy( const LivingWorldArmy &other );	// ILT 0x0001FE6F -> 0x00362F30
	virtual ~LivingWorldArmy();
	AsciiString getName() const;	// ILT 0x000041D3

private:
	char m_unmodelled04[ 0xB0 ];
};

class LivingWorldPlayerArmy
{
public:
	LivingWorldArmy *findArmy( const AsciiString &name, int *outIndex );
	void rva00365630( void *a, void *b );

private:
	char m_unmodelled00[ 0x30 ];
	std::vector<LivingWorldArmy> m_armies;
};

// ?rva00365630@LivingWorldPlayerArmy@@QAEXPAX0@Z
void LivingWorldPlayerArmy::rva00365630( void *a, void *b )
{
	LivingWorldPlayerArmy *source = (LivingWorldPlayerArmy *)a;
	for( UnsignedInt i = 0; i < m_armies.size(); ++i )
	{
		int sourceIndex;
		LivingWorldArmy *found = source->findArmy( m_armies[ i ].getName(), &sourceIndex );
		if( found )
		{
			LivingWorldPlayerArmy *destination = (LivingWorldPlayerArmy *)b;
			destination->m_armies.push_back( *found );
			if( sourceIndex >= 0 && (UnsignedInt)sourceIndex < source->m_armies.size() )
				source->m_armies.erase( source->m_armies.begin() + sourceIndex );
		}
	}
}
