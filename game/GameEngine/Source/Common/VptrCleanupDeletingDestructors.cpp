// 12 thirty-six-byte __thiscall members with one shape:
//
//     push esi / mov esi,ecx / mov [esi],<offset vftable> / call <rel32> /
//     test byte ptr [esp+4],1 / je +9 / push esi / call operator delete /
//     add esp,4 / mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  MSVC 7.1's scalar deleting destructor `??_G`, as in
// ScalarDeletingDestructors.cpp, with a destructor inlined into it that is not
// empty: it re-seats the vptr and then makes one __thiscall call with `this`
// unchanged in ecx.  The flag test, the conditional `operator delete` at
// 0x00881EB0 and the `this` returned in eax are the helper's own frame and are
// identical in both files.
//
// WHY THE CALL IS NOT A BASE DESTRUCTOR.  Probed: a class with a polymorphic
// base emits `call ??1NAME@@UAE@XZ` from the helper and keeps the vptr store in
// that separate body -- MSVC 7.1 will not fold a destructor with a base call
// into `??_G`, whether the destructor is written inline, out of line, or left
// implicit.  What DOES fold, on the first spelling, is a destructor whose body
// is one member call on `this`; that is the shape here.  The same reasoning
// leaves the eleven-byte `mov [ecx],<vftable> / jmp <rel32>` bodies in
// VptrTailJumpDestructors.cpp ambiguous between a base destructor and a member
// call -- the bytes are identical either way -- but here the helper's shape
// picks one.
//
// The callee is spelled as a member of a small class the object is cast to,
// because 12 bodies with different vftables share 4 callees between them: what
// the bytes show is a __thiscall function reached with `this` in ecx, not a
// member of any one of these classes.  Each callee is an address decoded from
// the retail REL32 and pinned in `targets/game/reverse/symbols.csv` under an address-derived
// name.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// Each callee is called by its existing ledger name at the address retail's
// call reaches (callees.py): 0x7EB6C0 ??1BfmeDirtyBase, 0x7FA650
// ??1Rva00803890Base, 0x9EDD30 SList<TagBlockIndex>::Remove_All, and ILT
// 0xB9CE, whose emitted object symbol is the VectorClass Clear thunk.  All
// are no-argument __thiscall; the member-pointer view keeps `this` in ecx.
class BfmeVptrCleanupTarget
{
public:
	void run();
};

#define BFME_CLEANUP_0000B9CE "?Clear@?$VectorClass@U_ArcInfoStruct@VehicleCurveClass@@@@UAEXXZ"
#define BFME_CLEANUP_007EB6C0 "??1BfmeDirtyBase@@UAE@XZ"
#define BFME_CLEANUP_007FA650 "??1Rva00803890Base@@UAE@XZ"
#define BFME_CLEANUP_009EDD30 "?Remove_All@?$SList@VTagBlockIndex@@@@UAEXXZ"

extern "C" void __cdecl __identifier( BFME_CLEANUP_0000B9CE )();
extern "C" void __cdecl __identifier( BFME_CLEANUP_007EB6C0 )();
extern "C" void __cdecl __identifier( BFME_CLEANUP_007FA650 )();
extern "C" void __cdecl __identifier( BFME_CLEANUP_009EDD30 )();

#define BFME_VPTR_CLEANUP_DELETING_DTOR( NAME, CLEANUP )                      \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
		union                                                                 \
		{                                                                     \
			void ( __cdecl *symbol )();                                       \
			void ( BfmeVptrCleanupTarget::*member )();                        \
		} cleanup;                                                            \
		cleanup.symbol = &__identifier( CLEANUP );                            \
		( ( (BfmeVptrCleanupTarget *)this )->*cleanup.member )();             \
	}

BFME_VPTR_CLEANUP_DELETING_DTOR( Rva00673550CleanupDeleting, BFME_CLEANUP_0000B9CE )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007E92C0CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F0C80CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F1DB0CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F2650CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F2F50CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F37F0CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F41E0CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F4900CleanupDeleting, BFME_CLEANUP_007FA650 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FADF0CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FC120CleanupDeleting, BFME_CLEANUP_007EB6C0 )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva009EEA70CleanupDeleting, BFME_CLEANUP_009EDD30 )
