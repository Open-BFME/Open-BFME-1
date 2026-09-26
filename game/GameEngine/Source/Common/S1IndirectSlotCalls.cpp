// Six bodies whose call goes through a DWORD SLOT rather than a REL32
// displacement:
//
//     call dword ptr [<SLOT>]        (FF 15 + DIR32)
//
// WHAT THE BYTES SHOW.  FF 15 reads its destination out of memory at link time,
// so nothing about the callee is recoverable from the displacement the way it
// is for an E8.  Every one of these slots lands in .idata (RVA 0x00F58000 ..
// 0x00F5E000), which is the import address table -- so in retail these almost
// certainly call into a DLL.  THAT IS A READING OF WHERE THE SLOT LIVES, NOT OF
// THESE BYTES: a global function pointer produces the identical encoding, and
// build.py fills the DIR32 from retail either way.  The slots are therefore
// spelled as function-pointer globals named after their RVA, which claims no
// import library, no module and no name.
//
// WHAT THE BYTES DO DECIDE, per row:
//
//   * 0007B620, 00336740, 00339040 and 00694BC0 end `mov eax,esi / pop esi /
//     ret`, so they are CONSTRUCTORS returning `this`; 006629A0 and 00133070 do
//     not, so they are void.
//   * The first three call the SAME slot and then store three DIFFERENT .rdata
//     addresses into the object's first dword.  Those addresses (RVA 0x00C766DC,
//     0x00CE7524, 0x00CE75B4) read like vftables, but a vftable store and
//     `m_p = &SomeConstObject;` encode identically and the DIR32 is copied from
//     retail, so the less assertive spelling is used.
//   * 006629A0 stores the call's RESULT (`mov [esi+0x34C],eax`), so its slot
//     returns a dword; the other slots' results are never read.
//   * 00133070 pushes one byte-wide constant and then does NOT adjust esp, so
//     its callee cleans the stack: __stdcall, not __cdecl.  Its guard reads a
//     one-byte global with `mov al,[..] / test al,al`, an int-width flag would
//     have loaded a dword.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

typedef void ( *BfmeVoidSlot )();
typedef int ( *BfmeIntSlot )();
typedef void( __stdcall *BfmeStdcallFlagSlot )( bool );

extern BfmeVoidSlot Data00F59214;
extern BfmeVoidSlot Data00F595C4;
extern BfmeIntSlot Data00F59544;
extern BfmeStdcallFlagSlot Data00F58F30;

extern const int Rdata00C766DC;
extern const int Rdata00CE7524;
extern const int Rdata00CE75B4;

extern bool Data00EEF1DC;

// Constructor: call the slot, then park a fixed .rdata address in the object's
// first dword, then return this.
#define BFME_SLOT_CTOR_STORE_ADDRESS( NAME, DATUM )                       \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		const int *m_target;                                              \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		Data00F59214();                                                   \
		m_target = &DATUM;                                                \
	}

BFME_SLOT_CTOR_STORE_ADDRESS( Rva0007B620, Rdata00C766DC )
BFME_SLOT_CTOR_STORE_ADDRESS( Rva00336740, Rdata00CE7524 )
BFME_SLOT_CTOR_STORE_ADDRESS( Rva00339040, Rdata00CE75B4 )

// Constructor: call a different slot, then set one byte at offset 0.
class Rva00694BC0
{
public:
	Rva00694BC0();
	bool m_flag;
};

Rva00694BC0::Rva00694BC0()
{
	Data00F595C4();
	m_flag = true;
}

// Void: store the slot's dword result into a member far out in the object.
class Rva006629A0
{
public:
	void refresh();
	char m_lead[ 0x34C ];
	int m_value;
};

void Rva006629A0::refresh()
{
	m_value = Data00F59544();
}

// Void: read a one-byte global and, only when it is set, forward one flag
// through a __stdcall slot.
void Rva00133070();
void Rva00133070()
{
	if ( Data00EEF1DC )
	{
		Data00F58F30( false );
	}
}
