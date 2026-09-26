// Five short __thiscall members that make ONE guarded indirect call and then
// write a constant into a member.  They share a mnemonic run and NOTHING else:
// this file is THREE shapes, and saying which is which is the whole content.
//
// SHAPE 1 -- Rva00411BB0 and Rva0048E590.  Test the MEMBER, call a virtual on a
// global sink passing that member, clear the member:
//
//     mov eax,[this+OFF] / test eax,eax / je .1 /
//     mov ecx,[SINK] / mov edx,[ecx] / push eax / call [edx+0x28] /
//     mov [this+OFF],0
//
// ecx holds the loaded global and the argument is pushed, so the callee is an
// ordinary __thiscall virtual at slot 10.  The two rows differ in the member
// offset (0x2D0 and 4) AND IN WHERE THE `je` LANDS: 0x00411BB0 jumps ONTO the
// clear, 0x0048E590 jumps PAST it to the epilogue.  So the clear is outside the
// guard in one and inside it in the other -- same length, different source.
//
// SHAPE 2 -- Rva0057F100.  Tests the GLOBAL, not the member; passes the member
// BY VALUE to slot 19 of a DIFFERENT global; and stores 1, not 0, with the
// store inside the guard.  Four separate differences: a different predicate, a
// different global, a different slot, a different constant.
//
// SHAPE 3 -- Rva0078AE40 and Rva0078AE70, whose 34 bytes are IDENTICAL to each
// other and contain no relocation at all.  Here the vtable is used with `this`
// PUSHED rather than in ecx:
//
//     mov eax,[eax+0x1C] / mov ecx,[eax] / push eax / call [ecx+0x30]
//
// ecx holds the VTABLE, not the receiver, and the receiver is a stack argument
// that nobody pops -- that is a __stdcall virtual, the convention COM-style
// interfaces use, not __thiscall.  Note also that the tested member (+0xD0) and
// the written member (+0xDC) are DIFFERENT SLOTS: the guard does not clear what
// it tested.  Two rows with the same bytes are still two functions; the ledger
// names both.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the filler
// virtuals exist only to place slots 10, 19 and 12; and the globals are typed
// only as far as the guard and the call convention require.

class GenSink
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void take( void *item );
};

extern GenSink *TheGenSink;

class Rva00411BB0
{
public:
	void handOff();
	char m_pad[ 0x2d0 ];
	void *m_item;
};
void Rva00411BB0::handOff()
{
	if( m_item )
		TheGenSink->take( m_item );
	m_item = 0;
}

class Rva0048E590
{
public:
	void handOff();
	int m_00;
	void *m_item;
};
void Rva0048E590::handOff()
{
	if( m_item )
	{
		TheGenSink->take( m_item );
		m_item = 0;
	}
}

class GenReturner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void giveBack( int slot );
};

extern GenReturner *TheGenReturner;

class Rva0057F100
{
public:
	void giveBack();
	char m_pad[ 0x64 ];
	int m_slot;
};
void Rva0057F100::giveBack()
{
	if( TheGenReturner )
	{
		TheGenReturner->giveBack( m_slot );
		m_slot = 1;
	}
}

class GenCom
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void __stdcall shutdown();
};

class GenHolder
{
public:
	char m_pad[ 0x1c ];
	GenCom *m_com;
};

class Rva0078AE40
{
public:
	void closeA();
	void closeB();
	char m_pad[ 0xd0 ];
	GenHolder *m_holder;
	char m_pad2[ 8 ];
	int m_state;
};
void Rva0078AE40::closeA()
{
	if( m_holder )
	{
		m_holder->m_com->shutdown();
		m_state = 0;
	}
}
void Rva0078AE40::closeB()
{
	if( m_holder )
	{
		m_holder->m_com->shutdown();
		m_state = 0;
	}
}
