// One __thiscall member that walks a contiguous array of pointers held as a
// begin/end pair at +0x50/+0x54 and answers the first element whose virtual
// slot 0x18 returns a given value:
//
//     mov esi,[edi+0x50] / cmp esi,[edi+0x54] / je .none
//   .loop:
//     mov ecx,[esi] / mov eax,[ecx] / call [eax+0x18]
//     cmp eax,ebx / je .found
//     mov eax,[edi+0x54] / add esi,4 / cmp esi,eax / jne .loop
//   .none:  xor eax,eax / ret 4
//   .found: mov eax,[esi] / ret 4
//
// WHAT THE BYTES SHOW.  The cursor is compared against the END POINTER, before
// the loop and again at the bottom, and no pointer difference and no `sar` ever
// appears: this walk has no element count in it at all, so the source condition
// is `cursor != end`, not `index < size`.  The end is re-read from the object on
// every iteration, so the compiler could not prove the virtual call leaves it
// alone.  `mov ecx,[esi]` before the vtable load makes the element a POINTER to
// a polymorphic class, and the found arm returns that same element.
//
// A SECOND ROW walks the SAME begin/end pair at +0x50/+0x54 and calls the SAME
// virtual slot 0x18 on what it finds, so the two share an element type -- but
// 0x003BDEC0 walks it by INDEX with the count recomputed in the condition
// (`mov eax,[esi+0x54] / sub eax,[esi+0x50] / sar eax,2` at the bottom of every
// iteration) and tests the answer with `test ebx,eax`, a bitwise AND against its
// argument rather than an equality.  Both of its results are constants with the
// epilogue duplicated.
//
// The two sibling loops at 0x003BDE80 and 0x003BD830 walk a begin/end pair at
// +0xC/+0x10 and DO recompute a `sar 2` element count in their condition; both
// reproduce to within one byte -- retail keeps `this` in esi and defers its
// second register push until after the count is computed, and every spelling
// tried here loads the base pointer into a register before the loop instead.
// Neither is claimed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Gen003BDF20Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual int  slot18();
};

class Rva003BDF20
{
public:
	Gen003BDF20Element *  find( int id );
	char                  m_pad00[ 0x50 ];
	Gen003BDF20Element ** m_at50;
	Gen003BDF20Element ** m_at54;
};
Gen003BDF20Element * Rva003BDF20::find( int id )
{
	for( Gen003BDF20Element **cursor = m_at50; cursor != m_at54; ++cursor )
	{
		if( (*cursor)->slot18() == id )
			return *cursor;
	}
	return 0;
}

// Same class as in V4BooleanGateChain.cpp, spelled identically there.
class Rva003BDEC0
{
public:
	bool                  anyMatching( int mask );
	bool                  allowed();
	char                  m_pad00[ 0x50 ];
	Gen003BDF20Element ** m_at50;
	Gen003BDF20Element ** m_at54;
	char                  m_pad58[ 0x20 ];
	bool                  m_at78;
};
bool Rva003BDEC0::anyMatching( int mask )
{
	for( unsigned index = 0; index < (unsigned)( m_at54 - m_at50 ); ++index )
	{
		if( mask & m_at50[ index ]->slot18() )
			return true;
	}
	return false;
}
