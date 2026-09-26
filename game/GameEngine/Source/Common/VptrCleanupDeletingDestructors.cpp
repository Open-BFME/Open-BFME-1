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

class Rva0000B9CECleanup
{
public:
	void run();
};

class Rva007EB6C0Cleanup
{
public:
	void run();
};

class Rva007FA650Cleanup
{
public:
	void run();
};

class Rva009EDD30Cleanup
{
public:
	void run();
};

#define BFME_VPTR_CLEANUP_DELETING_DTOR( NAME, CLEANUP )                      \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
		( (CLEANUP *)this )->run();                                           \
	}

BFME_VPTR_CLEANUP_DELETING_DTOR( Rva00673550CleanupDeleting, Rva0000B9CECleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007E92C0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F0C80CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F1DB0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F2650CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F2F50CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F37F0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F41E0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F4900CleanupDeleting, Rva007FA650Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FADF0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FC120CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva009EEA70CleanupDeleting, Rva009EDD30Cleanup )
