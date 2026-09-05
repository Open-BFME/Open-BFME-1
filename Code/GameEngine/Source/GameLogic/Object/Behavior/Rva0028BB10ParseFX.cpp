// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Byte-twin of ?parseFX@@YAXPAVINI@@PAX1PBX@Z at 0x002016E0
// (InstantDeathBehaviorParseFXThunk.cpp): identical 106 bytes once
// relocations are masked; only the vector-field offset differs (+0x14 here
// vs +0x40 there), matching the prompt's this-relative field note. All
// callees (getNextToken/getNextTokenOrNull, the global bfmeAdd1061 lookup,
// the vector overflow helper) are fixed real symbols independent of the
// enclosing module-data class, so no per-instance renaming is needed there;
// only the outer function needs a fresh mangled name.

#include <vector>

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXListStore
{
public:
	const FXList *findFXList( const char *name ) const;
};

extern FXListStore *TheFXListStore;

class Rva0028BB10ModuleData
{
public:
	unsigned char m_unreconstructed_00[0x14];
	_STL::vector<const FXList *> m_fx;						///< +0x14
};

//-------------------------------------------------------------------------------------------------
void Rva0028BB10ParseFX( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	Rva0028BB10ModuleData* self = (Rva0028BB10ModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList((token));	// could be null! this is OK!
		self->m_fx.push_back(fxl);
	}
}
