// ?hasAnyBuildings@Team@@QBE_N_N@Z
// partial score=0.72 date=2026-09-01
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// BFME Team::hasAnyBuildings, retail 0x000F4980. The Zero Hour source walks
// the intrusive TeamMemberList and asks whether a live member is a structure.
// BFME adds one flag. Its retail body always excludes the template flag in
// kind-of word 1 bit 22; when the flag is set it also excludes structures whose
// Object condition word has either of bits 2 and 3 set.

#include "PreRTS.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;

class BfmeThingTemplate
{
public:
	BfmeThingTemplate *getFinalOverride();		// ILT 0x000022BB
};

class BfmeTeamMemberLink
{
public:
	static Object *__fastcall next( const void *link );	// ILT 0x00001140
};

static BfmeThingTemplate *bfmeFinalTemplate( const Object *object )
{
	BfmeThingTemplate *value =
		*(BfmeThingTemplate *const *)((const char *)object + 0x04);
	if( value )
	{
		BfmeThingTemplate *next =
			*(BfmeThingTemplate **)((char *)value + 0x04);
		if( next )
			value = next->getFinalOverride();
	}
	return value;
}

class Team
{
public:
	Bool hasAnyBuildings( Bool bfmeFlag ) const;

private:
	unsigned char m_unmodelled_000[ 0x0c ];
	Object *m_teamMemberList;
};

// ?hasAnyBuildings@Team@@QBE_N_N@Z
Bool Team::hasAnyBuildings( Bool bfmeFlag ) const
{
	typedef Object *(__fastcall *GetNextFunction)( const void * );
	GetNextFunction getNext = BfmeTeamMemberLink::next;
	const int thisDelta = -0x64;
	const unsigned int vbIndex = 0;
	Object *object = m_teamMemberList;

	while( object )
	{
		BfmeThingTemplate *thing = bfmeFinalTemplate( object );
		const UnsignedInt *kindOf =
			(const UnsignedInt *)((const char *)thing + 0xc8);
		const signed char *kindOfBytes = (const signed char *)kindOf;

		if( (kindOf[1] & 0x00400000u) != 0 )
			goto next_object;

		if( bfmeFlag &&
			kindOfBytes[0] < 0 &&
			(*(const UnsignedInt *)((const char *)object + 0x118) & 0x0cu) != 0 )
			goto next_object;

		thing = bfmeFinalTemplate( object );
		kindOfBytes = (const signed char *)thing + 0xc8;
		if( kindOfBytes[0] < 0 )
			return true;

	next_object:
		if( object )
		{
			const char *vbptrAddress = (const char *)object + 0x68;
			const int *vbtable = *(const int *const *)vbptrAddress;
			const void *link = vbptrAddress + vbtable[vbIndex] + thisDelta;
			object = getNext( link );
		}
	}

	return false;
}
