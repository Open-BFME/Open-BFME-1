// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Precompiled /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Fuzzy twin (tools/fuzzy_twin_scan.py) of Rva0007F560Ctor.cpp: build a temporary
// AsciiString from the literal, look it up through a singleton, and hand the
// pointer back. Retail 0x003392B0 keeps the result in esi and returns it (ret 4,
// no this), so it is a __stdcall free function over TheParticleSystemManager
// (0x012F64BC); the lookup calls the matched ParticleSystemManager::findTemplate
// body through its retail thunk at 0x00015267.

// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include "ascii_string.h"
// ParticleSys.h's upstream AsciiString differs from BFME's local definition.
#define ASCIISTRING_H
#include "GameClient/ParticleSys.h"

void *__stdcall Rva003392B0FindParticleTemplate( const char *name )
{
	AsciiString tmp( name );
	return TheParticleSystemManager->findTemplate( tmp );
}
