// 46 thirty-one-byte __thiscall members with one shape:
//
//     test byte ptr [esp+4],1 / push esi / mov esi,ecx /
//     mov [esi],<offset vftable> / je +9 / push esi / call operator delete /
//     add esp,4 / mov eax,esi / pop esi / ret 4
//
// WHAT THE BODY IS.  This is MSVC 7.1's SCALAR DELETING DESTRUCTOR, the
// compiler-generated `??_G` helper that a class with a virtual destructor gets
// a vftable slot for: one flag argument, bit 0 meaning "and free the storage",
// the destructor's own work done first and `this` returned.  Nothing about it
// is hand-written -- declaring a class with a virtual destructor and defining
// that destructor empty emits these exact thirty-one bytes, with the
// destructor body (the vftable re-seat) inlined into the helper and the call
// going to `operator delete` at 0x00881EB0.
//
// The 46 bodies carry 46 distinct vftables, so they are 46 distinct classes;
// nine further members of the same family are NOT here, because their vftable
// is one already claimed by a class in TrivialVirtualDestructors.cpp and their
// row belongs to that class rather than to a new one.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_SCALAR_DELETING_DTOR( NAME )                                     \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_SCALAR_DELETING_DTOR( Rva00087370Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0008A3E0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva000AFC40Deleting )
BFME_SCALAR_DELETING_DTOR( Rva000C3BB0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00101B70Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00102470Deleting )
BFME_SCALAR_DELETING_DTOR( Rva001026F0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva001B24D0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00338FF0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0035FF30Deleting )
BFME_SCALAR_DELETING_DTOR( Rva003851B0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0042E2D0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva004708B0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0047CFA0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva004896E0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva004952C0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva004B2CE0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00516610Deleting )
BFME_SCALAR_DELETING_DTOR( Rva006282B0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00651690Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0065E4A0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00739C40Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0073A7C0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00782C80Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00782DA0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007AE380Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007AE5A0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007E39C0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007E87C0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007EA6D0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F0350Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F48D0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F4930Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F89B0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F8F40Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007F96A0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007FA8E0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007FAD50Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007FBBE0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva007FD040Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00889250Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00938BF0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva00942EB0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva0095C6F0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva009CDDF0Deleting )
BFME_SCALAR_DELETING_DTOR( Rva009DB610Deleting )
