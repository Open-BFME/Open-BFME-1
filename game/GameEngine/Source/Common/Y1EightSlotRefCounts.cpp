// Three __thiscall members of one class that keeps EIGHT pointer slots at
// +0x10..+0x2C, each pointing at an object whose byte at +0x38 is a reference
// count, plus a count byte of its own at +0x39 and a reference count of its own
// at +0x38.
//
//   0x003CBA90   146 bytes, ret 4   -- fill the eight slots from an array
//   0x003CCD70    94 bytes, ret 0   -- release: drop every slot's reference
//   0x003CCDF0   109 bytes, ret 8   -- re-point: release, restore, take references
//
// THE LAYOUT IS READ STRAIGHT OFF THE BYTES.  Eight dword slots at 0x10, 0x14,
// ... 0x2C, unrolled with no loop; `fe 4a 38` / `fe 40 38` is a byte increment
// and decrement of the POINTEE at +0x38; `fe 49 38` at the end of each body
// does the same to `this`, so the owning object carries the same byte in the
// same place.  0x003CBA90 writes a second byte at +0x39, which counts how many
// of the eight incoming slots were null.
//
// WHAT EACH ONE SAYS.
//
// 0x003CBA90 zeroes +0x39 and then, per slot: tests the INCOMING pointer, bumps
// the count when it is null, and stores it.  The first bump is `mov byte
// [ecx+0x39],1` and the other seven are `inc` -- the fold of `0 + 1` on the
// first one, which is what a uniform `if ( p == NULL ) ++m_nullCount;` produces
// after the zero store.  Retail RE-READS the incoming pointer for the store
// after testing it, so the source named that expression twice rather than
// binding it to a local.
//
// 0x003CCD70 RETURNS THE OLD OWNED POINTER, and that is not a guess: retail
// loads [ecx+0x0C] into eax, stores zero over it, and then does all eight slot
// loads through EDX -- eax is kept alive across the whole body for no other
// reason.  Written as a void function the same source compiles the slot loads
// through eax and reorders the first one ahead of the store.
//
// 0x003CCDF0 calls the release body at 0x003CC890 (reached through the
// incremental-link thunk at 0x00036A9D), then stores its two arguments to +0x0C
// and +0x34, then takes a reference on each surviving slot.  The call proves
// the release stayed an opaque declaration here, so it is declared and not
// defined -- defining it in this translation unit would inline it away.
//
// THE LOCAL SLOT BASE IS A SOURCE FACT.  In both 0x003CCD70 and 0x003CCDF0
// retail keeps the eight slot accesses adjacent and the surrounding member
// stores adjacent.  Reaching the slots through `this` directly makes MSVC 7.1
// hoist the first slot load above the neighbouring member store in BOTH bodies;
// binding the base to a local first reproduces retail in both.  One body could
// be coincidence, two agreeing is the source telling us how it was written.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the class, the slots or the count,
// and the one callee is an unnamed body.  Every name here is address-derived or
// describes only what the byte does.

class Y1SlotRef
{
public:
	char m_lead[ 0x38 ];
	unsigned char m_refCount;
};

class Y1SlotArray
{
public:
	Y1SlotRef *m_slot[ 8 ];
};

// The release body at 0x003CC890, reached through its incremental-link thunk.
// Declared only: retail encodes a `call`, so it was not visible here.
class Gen00036A9D
{
public:
	void call();
};

class Rva003CBA90
{
public:
	char m_lead[ 0x0C ];
	void *m_owned;
	Y1SlotRef *m_slot[ 8 ];
	int m_pad30;
	int m_extra;
	unsigned char m_refCount;
	unsigned char m_nullCount;

	void setSlots( Y1SlotArray *incoming );
	void *releaseSlots();
	void repoint( void *owned, int extra );
};

void Rva003CBA90::setSlots( Y1SlotArray *incoming )
{
	m_nullCount = 0;

	if ( incoming->m_slot[ 0 ] == 0 ) ++m_nullCount;
	m_slot[ 0 ] = incoming->m_slot[ 0 ];
	if ( incoming->m_slot[ 1 ] == 0 ) ++m_nullCount;
	m_slot[ 1 ] = incoming->m_slot[ 1 ];
	if ( incoming->m_slot[ 2 ] == 0 ) ++m_nullCount;
	m_slot[ 2 ] = incoming->m_slot[ 2 ];
	if ( incoming->m_slot[ 3 ] == 0 ) ++m_nullCount;
	m_slot[ 3 ] = incoming->m_slot[ 3 ];
	if ( incoming->m_slot[ 4 ] == 0 ) ++m_nullCount;
	m_slot[ 4 ] = incoming->m_slot[ 4 ];
	if ( incoming->m_slot[ 5 ] == 0 ) ++m_nullCount;
	m_slot[ 5 ] = incoming->m_slot[ 5 ];
	if ( incoming->m_slot[ 6 ] == 0 ) ++m_nullCount;
	m_slot[ 6 ] = incoming->m_slot[ 6 ];
	if ( incoming->m_slot[ 7 ] == 0 ) ++m_nullCount;
	m_slot[ 7 ] = incoming->m_slot[ 7 ];
}

void *Rva003CBA90::releaseSlots()
{
	void *owned = m_owned;
	m_owned = 0;

	Y1SlotRef **slots = m_slot;
	if ( slots[ 0 ] ) --slots[ 0 ]->m_refCount;
	if ( slots[ 1 ] ) --slots[ 1 ]->m_refCount;
	if ( slots[ 2 ] ) --slots[ 2 ]->m_refCount;
	if ( slots[ 3 ] ) --slots[ 3 ]->m_refCount;
	if ( slots[ 4 ] ) --slots[ 4 ]->m_refCount;
	if ( slots[ 5 ] ) --slots[ 5 ]->m_refCount;
	if ( slots[ 6 ] ) --slots[ 6 ]->m_refCount;
	if ( slots[ 7 ] ) --slots[ 7 ]->m_refCount;
	--m_refCount;

	return owned;
}

void Rva003CBA90::repoint( void *owned, int extra )
{
	( (Gen00036A9D *)this )->call();

	m_owned = owned;
	m_extra = extra;

	Y1SlotRef **slots = m_slot;
	if ( slots[ 0 ] ) ++slots[ 0 ]->m_refCount;
	if ( slots[ 1 ] ) ++slots[ 1 ]->m_refCount;
	if ( slots[ 2 ] ) ++slots[ 2 ]->m_refCount;
	if ( slots[ 3 ] ) ++slots[ 3 ]->m_refCount;
	if ( slots[ 4 ] ) ++slots[ 4 ]->m_refCount;
	if ( slots[ 5 ] ) ++slots[ 5 ]->m_refCount;
	if ( slots[ 6 ] ) ++slots[ 6 ]->m_refCount;
	if ( slots[ 7 ] ) ++slots[ 7 ]->m_refCount;
	++m_refCount;
}
