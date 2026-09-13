// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// Retail 0x00364B10 (574 B). Collection of 0x58-byte player-army groups at
// this+0x18 with nested 0xB4 LivingWorldArmy records. RohanSam special-case
// scan. Address-derived names: no matched caller names the method.
#include "Common/AsciiString.h"

class UnicodeString
{
public:
	void set( const UnicodeString &source )
	{
		reinterpret_cast<StringBase<unsigned short> *>( this )->set(
			*reinterpret_cast<const StringBase<unsigned short> *>( &source ) );
	}

	void *m_data;
};

class Rva00364B10AsciiSet
{
public:
	void set( const Rva00364B10AsciiSet &source )
	{
		reinterpret_cast<StringBase<char> *>( this )->set(
			*reinterpret_cast<const StringBase<char> *>( &source ) );
	}

	void *m_data;
};

struct Rva00364B10AsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[ 1 ];
};

class Rva00364B10AsciiString
{
public:
	int compare( const char *text, int length ) const
	{
		int valueLength = m_data != 0 ? m_data->m_length : 0;
		const char *valueText = m_data != 0 ? reinterpret_cast<const char *>( m_data ) + 8 : reinterpret_cast<const char *>( 0x0107388B );
		int result = memcmp( valueText, text, valueLength < length ? valueLength : length );
		if( result == 0 )
			result = valueLength - length;
		return result;
	}

	Rva00364B10AsciiHeader *m_data;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
	char m_unmodelled08[ 0x18 ];
	Rva00364B10AsciiString m_name;
};

// The retail call is the ILT at 0x000022BB; its body is the resolved
// ?getFinalOverride@Overridable@@QBEPBV1@XZ at 0x00087A80.
#pragma comment( linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ" )

class Rva00364B10Summary
{
public:
	char m_unmodelled00[ 4 ];
	Overridable *m_override;
	char m_unmodelled08[ 0x36C ];
	int m_field374;
	int m_field378;
	int m_field37C;
	int m_field380;
	unsigned char m_field384;
	char m_unmodelled385[ 3 ];
	UnicodeString m_field388;
	Rva00364B10AsciiSet m_field38C;
};

class LivingWorldArmy;

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	T *erase( T *first, T *last );

	T *m_begin;
	T *m_end;
	T *m_capacity;
};
}

typedef _STL::vector<LivingWorldArmy, _STL::allocator<LivingWorldArmy> > Rva00364B10ArmyVector;

class LivingWorldArmy
{
public:
	virtual ~LivingWorldArmy();
	AsciiString getName() const;

	char m_unmodelled04[ 0x2C ];
	Rva00364B10ArmyVector m_armies;
	int m_field3C;
	char m_unmodelled40[ 4 ];
	int m_field44;
	int m_field48;
	Rva00364B10AsciiSet m_displayName;
	char m_unmodelled50[ 0x28 ];
	UnicodeString m_sourceString;
	char m_unmodelled7C[ 0x38 ];
};

// ?getName@LivingWorldArmy@@QBE?AVAsciiString@@XZ
#pragma comment( linker, "/alternatename:?getName@LivingWorldArmy@@QBE?AVAsciiString@@XZ=?j_000041d3@@YAXXZ" )

class Rva00364B10ArmyGroup
{
public:
	char m_unmodelled00[ 8 ];
	unsigned char m_isActive;
	char m_unmodelled09[ 0x17 ];
	int m_startingCommandPoints;
	char m_unmodelled24[ 0x0C ];
	Rva00364B10ArmyVector m_armies;
	char m_unmodelled3C[ 0x20 ];

	void clearArmies()
	{
		m_armies.erase( m_armies.m_begin, m_armies.m_end );
		m_isActive = 0;
	}
};

class Rva00364B10GroupVector
{
public:
	Rva00364B10ArmyGroup *m_begin;
	Rva00364B10ArmyGroup *m_end;
	Rva00364B10ArmyGroup *m_capacity;
	Rva00364B10ArmyGroup *first() const { return m_begin; }
	Rva00364B10ArmyGroup *last() const { return m_end; }
};

class Rva00364B10LivingWorldPlayerArmyCollection
{
public:
	int scanArmyGroups( Rva00364B10Summary *summary, bool copySummary );

private:
	char m_unmodelled00[ 0x18 ];
	Rva00364B10GroupVector m_groups;
};

// ?scanArmyGroups@Rva00364B10LivingWorldPlayerArmyCollection@@QAEHPAVRva00364B10Summary@@_N@Z
int Rva00364B10LivingWorldPlayerArmyCollection::scanArmyGroups(
	Rva00364B10Summary *summary, bool copySummary )
{
	char *armyEnd;
	Rva00364B10ArmyGroup *groupValue;
	unsigned int groupIndex;
	AsciiString expected( "RohanSam" );
	groupValue = m_groups.first();
	groupIndex = 0;

	if( groupValue != m_groups.last() )
	{
		armyEnd = reinterpret_cast<char *>( &groupValue->m_armies.m_end );
		do
		{
			LivingWorldArmy *army = *reinterpret_cast<LivingWorldArmy **>( armyEnd - 4 );
			if( army != *reinterpret_cast<LivingWorldArmy **>( armyEnd ) )
			{
				do
				{
					if( army->getName().compare( expected ) == 0 )
					{
						Overridable *override = *reinterpret_cast<Overridable **>( reinterpret_cast<char *>( summary ) + 4 );
						if( override != 0 && override->m_nextOverride != 0 )
							override = (Overridable *)override->m_nextOverride->getFinalOverride();

						if( override->m_name.compare( "RohanSamWithFrodoPowers", 0x17 ) == 0 )
						{
							if( copySummary )
						{
								summary->m_field374 = army->m_field3C;
								UnicodeString *summarySourceString = &summary->m_field388;
								const UnicodeString *armySourceString = &army->m_sourceString;
								summarySourceString->set( *armySourceString );
								summary->m_field37C = army->m_field44;
								int field48 = army->m_field48;
								summary->m_field380 = field48;
							summary->m_field378 = 0;
							summary->m_field384 = 0;

							const Rva00364B10AsciiSet *displayName = &army->m_displayName;
							if( displayName->m_data != 0 && *reinterpret_cast<const unsigned short *>( reinterpret_cast<const char *>( displayName->m_data ) + 4 ) != 0 )
							{
								Rva00364B10AsciiSet *summaryDisplayName = &summary->m_field38C;
								summaryDisplayName->set( *displayName );
							}
						}
						else
						{
							Rva00364B10ArmyVector *armyVector = &groupValue->m_armies;
							groupValue->m_startingCommandPoints = 4;
							LivingWorldArmy *lastArmy = armyVector->m_end;
							LivingWorldArmy *firstArmy = armyVector->m_begin;
							armyVector->erase( firstArmy, lastArmy );
							groupValue->m_isActive = 0;
						}
							return groupIndex;
						}
					}

					army = reinterpret_cast<LivingWorldArmy *>( reinterpret_cast<char *>( army ) + 0xB4 );
				}
					while( army != *reinterpret_cast<LivingWorldArmy **>( armyEnd ) );
			}

			groupValue = reinterpret_cast<Rva00364B10ArmyGroup *>( reinterpret_cast<char *>( groupValue ) + 0x58 );
			armyEnd += 0x58;
			++groupIndex;
		}
		while( groupValue != m_groups.last() );
	}

	return -1;
}
