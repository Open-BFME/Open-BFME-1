// cl: /O1
// 56 twenty-eight-byte __thiscall members with one shape:
//
//     push esi / mov esi,ecx / call <destructor> / test byte ptr [esp+8],1 /
//     je +7 / push esi / call operator delete / pop ecx /
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  MSVC 7.1's scalar deleting destructor `??_G`, as in
// ScalarDeletingDestructors.cpp, with the destructor NOT folded in: the helper
// calls it and the vptr store lives in that separate body.
//
// WHY THIS FILE CARRIES A `/O1`.  The single-argument cleanup after the delete
// is `pop ecx`, not `add esp,4`.  At the project's default `/O2` MSVC 7.1 emits
// `add esp,4` here and the body is thirty-one bytes; `/O1` emits `pop ecx` and
// twenty-eight, which is retail exactly.  That is a property of the translation
// unit these bodies came from, so it is declared on this file rather than
// worked around in the source.
//
// THE DESTRUCTORS ARE FOLDED.  56 bodies call only 22 distinct destructors --
// 26 of them share one address.  Identical-code folding is why: a derived class
// whose destructor does nothing of its own compiles to the same bytes as its
// siblings', and the linker keeps one copy.  Each class's destructor is
// therefore pinned at the address its own helper calls, which is what folding
// means.  The base also keeps those destructors out of line: MSVC folds an
// empty destructor with no base straight into the helper, and that is the
// thirty-one-byte shape, not this one.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class DeletingOutOfLineBase
{
public:
	virtual ~DeletingOutOfLineBase();
};

#define BFME_SIZE_OPT_DELETING_DTOR( NAME )                                   \
	class NAME : public DeletingOutOfLineBase                                 \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_SIZE_OPT_DELETING_DTOR( Rva00A1175CSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A27BFBSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A314E9SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A35FB5SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A35FEDSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36025SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3605DSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36311SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36349SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36381SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A363B9SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A363F1SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36429SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36461SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A367B7SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A367EFSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36827SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3685FSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36897SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A368CFSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36907SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3693FSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36CA5SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36CDDSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36D15SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36D4DSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36D85SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A36DBDSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3AA39SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B1A1SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B1D5SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B209SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B23DSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B271SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3B28DSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3BA94SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3BAB0SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3BACCSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3CA3CSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3CAE0SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3CD76SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3CDB1SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A3E088SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A43687SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A43B0FSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A5523DSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A56F70SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A570EESizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A571EBSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A57BFDSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A589BDSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A6B7C9SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A6BD2FSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A6FAABSizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00A920C6SizeOptDeleting )
BFME_SIZE_OPT_DELETING_DTOR( Rva00ABC788SizeOptDeleting )
