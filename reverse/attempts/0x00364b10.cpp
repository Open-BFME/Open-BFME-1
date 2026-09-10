// ?d_00364b10@@YAXXZ
// partial score=0.56 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// This is an address-qualified Living World army-summary operation.  The
// original class spelling is not recoverable from the available callers, so
// the source name deliberately records the retail boundary instead of
// inventing a method name.  The nested record layouts are measured from the
// retail accesses: groups are 0x58 bytes, their army records are 0xB4 bytes,
// and the group vector begins at this+0x18.
//
// Copyright (C) 2024 Open-BFME contributors.  This file is free software;
// it may be redistributed and/or modified under the terms of the GNU GPL.
#include "Common/AsciiString.h"
class UnicodeString
{
public:
	void set( const UnicodeString &source );

	bool isNotEmpty() const
	{
		return m_data != 0 && *reinterpret_cast<const unsigned short *>( reinterpret_cast<const char *>( m_data ) + 4 ) != 0;
	}

private:
	void *m_data;
};

class LivingWorldArmy;

class Rva00364B10ArmyVector
{
public:
	LivingWorldArmy *erase( LivingWorldArmy *first, LivingWorldArmy *last );

	LivingWorldArmy *m_begin;
	LivingWorldArmy *m_end;
	LivingWorldArmy *m_capacity;
};

// This declaration-only member has the ABI of the existing retail erase
// implementation.  Its address is independently pinned as the ILT at
// 0x00030B48; it is not a local callback or a guessed helper body.
#pragma comment( linker, "/alternatename:?erase@Rva00364B10ArmyVector@@QAEPAVLivingWorldArmy@@PAV2@0@Z=?erase@?$vector@VLivingWorldArmy@@V?$allocator@VLivingWorldArmy@@@_STL@@@_STL@@QAEPAVLivingWorldArmy@@PAV3@0@Z" )

class LivingWorldArmy
{
public:
	virtual ~LivingWorldArmy();
	AsciiString getName() const;

	char m_unmodelled04[ 0x2C ];
	Rva00364B10ArmyVector m_armies;
	char m_unmodelled3C[ 0x78 ];
};

class Rva00364B10ArmyGroup
{
public:
	char m_unmodelled00[ 0x30 ];
	Rva00364B10ArmyVector m_armies;
	char m_unmodelled3C[ 0x20 ];
};

class Rva00364B10GroupVector
{
public:
	Rva00364B10ArmyGroup *m_begin;
	Rva00364B10ArmyGroup *m_end;
	Rva00364B10ArmyGroup *m_capacity;
};

class Rva00364B10LivingWorldArmySummary
{
public:
	int scanArmyGroups( void *summary, bool copySummary );

private:
	char m_unmodelled00[ 0x18 ];
	Rva00364B10GroupVector m_groups;
};

int Rva00364B10LivingWorldArmySummary::scanArmyGroups( void *summary, bool copySummary )
{
	AsciiString expected( reinterpret_cast<const char *>( 0x010E8F88 ) );
	int groupIndex = 0;

	for( Rva00364B10ArmyGroup *group = m_groups.m_begin; group != m_groups.m_end; group = reinterpret_cast<Rva00364B10ArmyGroup *>( reinterpret_cast<char *>( group ) + 0x58 ), ++groupIndex )
	{
		for( LivingWorldArmy *army = group->m_armies.m_begin; army != group->m_armies.m_end; army = reinterpret_cast<LivingWorldArmy *>( reinterpret_cast<char *>( army ) + 0xB4 ) )
		{
			AsciiString name = army->getName();
			if( name.compare( expected ) != 0 )
				continue;

			if( copySummary )
			{
				char *destination = reinterpret_cast<char *>( summary );
				const char *source = reinterpret_cast<const char *>( army );
				*reinterpret_cast<int *>( destination + 0x374 ) = *reinterpret_cast<const int *>( source + 0x3C );
				reinterpret_cast<UnicodeString *>( destination + 0x388 )->set( *reinterpret_cast<const UnicodeString *>( source + 0x78 ) );
				*reinterpret_cast<int *>( destination + 0x37C ) = *reinterpret_cast<const int *>( source + 0x44 );
				*reinterpret_cast<int *>( destination + 0x380 ) = *reinterpret_cast<const int *>( source + 0x48 );
				*reinterpret_cast<int *>( destination + 0x378 ) = 0;
				*reinterpret_cast<unsigned char *>( destination + 0x384 ) = 0;

				const UnicodeString *displayName = reinterpret_cast<const UnicodeString *>( source + 0x4C );
				if( displayName->isNotEmpty() )
					reinterpret_cast<UnicodeString *>( destination + 0x38C )->set( *displayName );
			}

			*reinterpret_cast<int *>( reinterpret_cast<char *>( army ) + 0x20 ) = 4;
			army->m_armies.erase( army->m_armies.m_begin, army->m_armies.m_end );
			*reinterpret_cast<unsigned char *>( reinterpret_cast<char *>( army ) + 8 ) = 0;
			return groupIndex;
		}
	}

	return -1;
}
