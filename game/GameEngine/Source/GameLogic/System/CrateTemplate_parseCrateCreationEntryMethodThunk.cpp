// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z: game/GameEngine/Source/GameLogic/System/CrateSystem.cpp

// Open-BFME: retail-layout C++ conversion of the CrateTemplate parser.
// The BFME KindOf mask is six dwords wide, and STLport's no-exception list
// path is what exposes the inlined allocator and element construction here.
#define __PLACEMENT_VEC_NEW_INLINE
#define Matrix4x4 Matrix4
#define __KINDOF_H_
#include "Common/BitFlags.h"
enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_COUNT = 192
};
typedef BitFlags<KINDOF_COUNT> KindOfMaskType;

#include "PreRTS.h"
#include "GameLogic/CrateSystem.h"
#include "Common/INIException.h"

// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z
void CrateTemplate::parseCrateCreationEntry( INI* ini, void *instance, void *, const void* )
{
	CrateTemplate *self = (CrateTemplate *)instance;

	const char *token = ini->getNextToken();
	AsciiString crateName = token;

	token = ini->getNextToken();
	Real crateValue;
	if (sscanf( token, "%f", &crateValue ) != 1)
		throw INIException( 3, "Floating point value expected instead of '%s'", token );

	crateCreationEntry newEntry;
	newEntry.crateName = crateName;
	newEntry.crateChance = crateValue;

	self->m_possibleCrates.push_back( newEntry );
}
