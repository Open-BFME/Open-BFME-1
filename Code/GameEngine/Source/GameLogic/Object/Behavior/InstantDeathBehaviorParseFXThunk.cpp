// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: parseFX, retail 0x002016E0, converted out of a machine byte dump.
// The reference body ports unchanged.
//
// The sweep could not tell parseFX from parseOCL -- both are the same four
// lines over a different store and a different vector, and masking the
// relocation sites hides exactly the bytes that would separate them. The call
// displacement is what decides it: the body reaches
// ?findFXList@FXListStore@@QBEPBVFXList@@PBD@Z, so this is parseFX, and the
// vector it appends to is m_fx at module-data +0x40.
//
// Almost all 106 bytes are one inlined push_back:
//
//   mov ecx,[esi+4] / cmp ecx,[esi+8] / je overflow
//   test ecx,ecx / je / mov [ecx],eax
//   add dword [esi+4],4
//
// The `test ecx,ecx` is not a source-level test -- _Copy_Construct is a
// placement new and MSVC guards every placement new with a null check on the
// pointer it is handed. A hand-written _STL shim gets that far and then loses
// on the __true_type tag: retail passes the tag by reference at the SAME stack
// address as the value, so the frame allocates no locals at all, while a shim's
// tag takes a slot of its own worth one `push ecx`. The vendored header does it
// retail's way, so this file includes <vector> rather than reconstructing it.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_00[0x40];
	_STL::vector<const FXList *> m_fx;						///< +0x40
};

//-------------------------------------------------------------------------------------------------
// ?parseFX@@YAXPAVINI@@PAX1PBX@Z
void parseFX( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	InstantDeathBehaviorModuleData* self = (InstantDeathBehaviorModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList((token));	// could be null! this is OK!
		self->m_fx.push_back(fxl);
	}
}
