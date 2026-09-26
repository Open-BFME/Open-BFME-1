// cl: /DNDEBUG /MD /EHsc
// Sixty 89-byte __thiscall destructors that differ ONLY in the two DIR32
// addresses they store into the object's vptr slot and in their own EH
// registration record.  Retail:
//
//     push -1 / push <ehdata> / fs:[0] frame
//     mov [esi], <DERIVED VFTABLE>          ; derived vptr, dtor entry
//     eax = [esi+4]; ecx = [eax]
//     if (ecx) { edx=[ecx]; push 1; call [edx] }   ; virtual `delete`
//     eax = [esi+4]; [eax] = 0
//     mov [esi], <BASE VFTABLE>             ; inlined empty virtual ~Base
//
// WHAT THE BYTES SHOW.  Two vptr stores bracketing the body make this a
// DESTRUCTOR, not an ordinary member: the entry store publishes the derived
// vftable and the exit store publishes the base's, which is the whole of an
// inlined `virtual ~Base() {}` on a base whose only member is its vptr.  The
// derived vftables run at a FOUR-BYTE STRIDE across the sixty members, so each
// derived vftable holds exactly one slot -- the scalar deleting destructor --
// confirming the destructor is the only virtual function.  The base vftable is
// the SAME address in all sixty, so all sixty derive from one base.
//
// The call is `mov edx,[ecx] / push 1 / call [edx]`: slot 0 with flag 1 is the
// scalar deleting destructor, i.e. `delete` of a pointer to a class with a
// virtual destructor.  [esi+4] is reloaded after the call before the store of
// 0, so the source names it again rather than caching it -- two loads, one per
// mention.  The frame stores `this` at [esp+4] and sets the EH state to 0
// before the call, so an unwind funclet exists to run the base destructor if
// `delete` throws; that is what forces the SEH prolog and /EHsc.
//
// WHERE THE BYTES CANNOT DECIDE: `m_pp` is spelled as a pointer-to-pointer
// member.  A reference member (`Victim *&`) and a pointer to a struct whose
// first field is the victim pointer compile to the identical two loads; the
// pointer-to-pointer spelling asserts the least.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The two
// vftable addresses and the EH data address are DIR32 relocation sites, so the
// byte gate takes them from the target -- the shape, not the addresses, is what
// this file proves.

class BigOwnedVictim
{
public:
	virtual ~BigOwnedVictim();
};

class BigOwnedPtrBase
{
public:
	virtual ~BigOwnedPtrBase() {}
};

#define BFME_OWNED_POINTER_DTOR( NAME )                                   	class NAME : public BigOwnedPtrBase                                   	{                                                                     	public:                                                               		virtual ~NAME();                                                  		BigOwnedVictim **m_pp;                                            	};                                                                    	NAME::~NAME()                                                         	{                                                                     		if ( *m_pp )                                                      			delete *m_pp;                                                 		*m_pp = 0;                                                        	}

BFME_OWNED_POINTER_DTOR( Rva0006F660 )
BFME_OWNED_POINTER_DTOR( Rva0006F720 )
BFME_OWNED_POINTER_DTOR( Rva0006F7E0 )
BFME_OWNED_POINTER_DTOR( Rva0006F8A0 )
BFME_OWNED_POINTER_DTOR( Rva0006F960 )
BFME_OWNED_POINTER_DTOR( Rva0006FA20 )
BFME_OWNED_POINTER_DTOR( Rva0006FAE0 )
BFME_OWNED_POINTER_DTOR( Rva0006FBA0 )
BFME_OWNED_POINTER_DTOR( Rva0006FC60 )
BFME_OWNED_POINTER_DTOR( Rva0006FD20 )
BFME_OWNED_POINTER_DTOR( Rva0006FDE0 )
BFME_OWNED_POINTER_DTOR( Rva0006FEA0 )
BFME_OWNED_POINTER_DTOR( Rva0006FF60 )
BFME_OWNED_POINTER_DTOR( Rva00070020 )
BFME_OWNED_POINTER_DTOR( Rva000700E0 )
BFME_OWNED_POINTER_DTOR( Rva000701A0 )
BFME_OWNED_POINTER_DTOR( Rva00070260 )
BFME_OWNED_POINTER_DTOR( Rva00070320 )
BFME_OWNED_POINTER_DTOR( Rva000703E0 )
BFME_OWNED_POINTER_DTOR( Rva000704A0 )
BFME_OWNED_POINTER_DTOR( Rva00070560 )
BFME_OWNED_POINTER_DTOR( Rva00070620 )
BFME_OWNED_POINTER_DTOR( Rva000706E0 )
BFME_OWNED_POINTER_DTOR( Rva000707A0 )
BFME_OWNED_POINTER_DTOR( Rva00070860 )
BFME_OWNED_POINTER_DTOR( Rva00070920 )
BFME_OWNED_POINTER_DTOR( Rva000709E0 )
BFME_OWNED_POINTER_DTOR( Rva00070AA0 )
BFME_OWNED_POINTER_DTOR( Rva00070B60 )
BFME_OWNED_POINTER_DTOR( Rva00070C20 )
BFME_OWNED_POINTER_DTOR( Rva00070CE0 )
BFME_OWNED_POINTER_DTOR( Rva00070DA0 )
BFME_OWNED_POINTER_DTOR( Rva00070E60 )
BFME_OWNED_POINTER_DTOR( Rva00070F20 )
BFME_OWNED_POINTER_DTOR( Rva00070FE0 )
BFME_OWNED_POINTER_DTOR( Rva000710A0 )
BFME_OWNED_POINTER_DTOR( Rva00071160 )
BFME_OWNED_POINTER_DTOR( Rva00071220 )
BFME_OWNED_POINTER_DTOR( Rva000712E0 )
BFME_OWNED_POINTER_DTOR( Rva000713A0 )
BFME_OWNED_POINTER_DTOR( Rva00071460 )
BFME_OWNED_POINTER_DTOR( Rva00071520 )
BFME_OWNED_POINTER_DTOR( Rva000715E0 )
BFME_OWNED_POINTER_DTOR( Rva000716A0 )
BFME_OWNED_POINTER_DTOR( Rva00071760 )
BFME_OWNED_POINTER_DTOR( Rva00071820 )
BFME_OWNED_POINTER_DTOR( Rva000718E0 )
BFME_OWNED_POINTER_DTOR( Rva000719A0 )
BFME_OWNED_POINTER_DTOR( Rva00071A60 )
BFME_OWNED_POINTER_DTOR( Rva00071B20 )
BFME_OWNED_POINTER_DTOR( Rva00071BE0 )
BFME_OWNED_POINTER_DTOR( Rva00071CA0 )
BFME_OWNED_POINTER_DTOR( Rva00071D60 )
BFME_OWNED_POINTER_DTOR( Rva00071E20 )
BFME_OWNED_POINTER_DTOR( Rva00071EE0 )
BFME_OWNED_POINTER_DTOR( Rva00071FA0 )
BFME_OWNED_POINTER_DTOR( Rva00072060 )
BFME_OWNED_POINTER_DTOR( Rva00072120 )
BFME_OWNED_POINTER_DTOR( Rva000721E0 )
BFME_OWNED_POINTER_DTOR( Rva000722A0 )
