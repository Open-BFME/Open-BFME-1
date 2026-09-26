// Three void __thiscall members that clear one field and dispatch through their
// own vftable:
//
//     mov eax,[ecx] / push <K> / mov <field>,0 / call dword ptr [eax+<SLOT>] /
//     ret
//
// WHAT THE BYTES SHOW.  All three are FULLY CONCRETE -- fifteen, fifteen and
// eighteen bytes with not one relocation site -- so every number here is proven:
// the slot index, the field offset, the store width and the pushed constant.
//
//   * `mov eax,[ecx]` reads a pointer from offset 0 and the call indexes off it,
//     so offset 0 holds a dispatch table and the object's own data starts at 4.
//     That is exactly a class with virtual functions and no base, which is how
//     it is spelled below: the slot index is reproduced by declaring that many
//     virtual functions ahead of the one being called.  None of them is defined
//     and no object is constructed here, so MSVC 7.1 emits no vftable for these
//     translation-unit-local shells -- no COMDAT appears that no ledger row
//     accounts for.
//   * Slots: 0x20/4 = index 8, 0x6C/4 = index 27, 0x10/4 = index 4.
//   * The store width is read off the opcode: C7 (dword) for 001EE810 and
//     006FCDF0, C6 (byte) for 00220700.
//   * The argument is pushed BEFORE the store is emitted, but that is scheduling,
//     not source order -- the bytes do not fix which statement came first.  It is
//     written store-then-call below; either order compiles to these bytes.
//   * `push 2` in 00220700 rules bool out for that argument, so all three are
//     spelled int -- the widest reading a byte-sized push allows.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, the virtual functions
// ahead of the called slot are placeholders that exist only to put it at the
// proven index, and the leading char arrays reproduce a proven field offset.

class Rva001EE810
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8( int value );

	void reset();

	char m_lead[ 8 ];
	int m_value;
};

void Rva001EE810::reset()
{
	m_value = 0;
	slot8( 0 );
}

class Rva00220700
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27( int value );

	void reset();

	char m_lead[ 0x95 ];
	bool m_value;
};

void Rva00220700::reset()
{
	m_value = false;
	slot27( 2 );
}

class Rva006FCDF0
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4( int value );

	void reset();

	char m_lead[ 0xC8 ];
	int m_value;
};

void Rva006FCDF0::reset()
{
	m_value = 0;
	slot4( 0 );
}
