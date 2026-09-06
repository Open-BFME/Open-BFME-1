// Nine small __thiscall members that walk a half-open pointer pair held in the
// object and call one member function on every element.  They fall into six
// shapes, and the shapes differ from each other in ways the bytes fix exactly:
//
//   A  0x003D0F60  0x003D0FA0  0x003D0FE0   45 bytes, ret 4
//        mov al,[ecx+0x34] / test al,al / jne out      <- Bool guard, returns
//        esi = [ecx+0x0C], edi = [ecx+0x10]            <- END READ ONCE
//        ebx = the argument, then per element: mov ecx,[esi] / push ebx / call
//        Three bodies, three different callees, otherwise identical.

//
//   B  0x003CFC60  0x003D2410                          36 bytes, ret 0
//        esi = [ecx+0x18], end RE-READ from [edi+0x1C] every iteration
//        per element: mov ecx,[esi] / call, no argument
//
//   C  0x003CD260                                      48 bytes, ret 8
//        esi = [ecx+0x08], end re-read from [edi+0x0C]; stride 0x3C, so the
//        elements are OBJECTS, not pointers, and ecx is the element address
//        itself.  Two pointer arguments are pushed in reverse order.

//
//   D  0x003CDE60                                      43 bytes, ret 0
//        same 0x3C-stride object walk, no arguments, and each iteration stores
//        zero to the element's dword at +0x30 AFTER the call.

//
//   E  0x003D2EE0                                      38 bytes, ret 0
//        end read once from [ebx+0x10]; after the loop, `mov byte [ebx+0x34],0`

//
//   F  0x003D0EE0                                      95 bytes, ret 0
//        a shape-B walk nested inside an outer walk, described where it sits

//
// WHAT THE BYTES DECIDE, AND WHAT THEY DO NOT.
//
// CACHED-vs-RELOADED END IS A SOURCE FACT.  MSVC 7.1 cannot keep a member in a
// register across a call to a function it cannot see, so shapes B, C and D --
// which reload the end pointer from the object after every call -- were written
// against the member, and shapes A and E, which compare against a register
// loaded once, hoisted the end into a local first.  That is why this file
// spells the two forms differently rather than picking one and hoping.

//
// The trailing stores are source order for the same reason: `mov [esi+0x30],0`
// in D sits after the call, and `mov byte [ebx+0x34],0` in E sits after the
// loop, and no MSVC 7.1 pass moves a store across a call.
//

// STRIDE IS THE ELEMENT SIZE.  `add esi,4` walks an array of pointers and the
// call takes `[esi]` in ecx; `add esi,0x3C` walks an array of 0x3C-byte objects
// and the call takes esi itself.  Only the offsets that appear are declared: the
// padding ahead of each member places it and asserts nothing else about the
// layout.

//
// THE CALLEES STAY DECLARATIONS.  Retail encodes a `call` at every one of these
// sites, so in retail the callee was NOT visible to the compiler here; defining
// any of them in this translation unit would inline it and destroy the loop.
// Each is named for the incremental-link thunk the call site encodes, and each
// such name is pinned in reverse/symbols.csv at that thunk -- the same
// convention the 981 Gen<RVA> pins already in that file use.
//

// IDENTITY REMAINS OPEN FOR THE OTHER GEN TYPES.  The Gen000135B1 body below is
// named by Rva003CD260 and uses the BFME seed slots at vtable offsets 0x78,
// 0x88 and 0x8C.

class Y1ForEachArg
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(void);
	virtual void bfmeTakeAt78(void *item);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeTakeAt88(void *item);
	virtual void bfmeTakeAt8C(void *item);
};

class BfmeSeedTarget;

class AsciiString;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, int extra);
	virtual ~AudioEventRTS();
	char m_bfmeStorage[ 0x6C ];
};

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);
};

extern AsciiString TheBfmeCrateNameDefault;
extern "C" unsigned char bfmeVftBTB[];

class BfmeThingBaseBTB
{
public:
	BfmeThingBaseBTB()
	{
		m_bfmeVft = bfmeVftBTB;
	}

	void *m_bfmeVft;
};

class BfmeThingBTB : public BfmeThingBaseBTB
{
public:
	BfmeThingBTB(const AsciiString &name, int extra) :
		m_bfmeAudio(name, extra)
	{
	}

	AudioEventRTS m_bfmeAudio;
};

// ---------------------------------------------------------------- shape A ---
#define Y1_FOREACH_PTR_GUARDED_ARG( NAME, ELEM )                              \
	class ELEM                                                                \
	{                                                                         \
	public:                                                                   \
		void call( Y1ForEachArg *arg );                                       \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char m_lead[ 0x0C ];                                                  \
		ELEM **m_begin;                                                       \
		ELEM **m_end;                                                         \
		char m_mid[ 0x20 ];                                                   \
		bool m_done;                                                          \
		void run( Y1ForEachArg *arg );                                        \
	};                                                                        \
	void NAME::run( Y1ForEachArg *arg )                                       \
	{                                                                         \
		if ( m_done )                                                         \
			return;                                                           \
		ELEM **end = m_end;                                                   \
		for ( ELEM **it = m_begin; it != end; ++it )                          \
			( *it )->call( arg );                                             \
	}

Y1_FOREACH_PTR_GUARDED_ARG( Rva003D0F60, Gen0001C184 )
Y1_FOREACH_PTR_GUARDED_ARG( Rva003D0FA0, Gen00041FE7 )
Y1_FOREACH_PTR_GUARDED_ARG( Rva003D0FE0, Gen0000C4F0 )

// ---------------------------------------------------------------- shape B ---
#define Y1_FOREACH_PTR_RELOAD( NAME, ELEM )                                   \
	class ELEM                                                                \
	{                                                                         \
	public:                                                                   \
		void call();                                                          \
	};                                                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		char m_lead[ 0x18 ];                                                  \
		ELEM **m_begin;                                                       \
		ELEM **m_end;                                                         \
		void run();                                                           \
	};                                                                        \
	void NAME::run()                                                          \
	{                                                                         \
		for ( ELEM **it = m_begin; it != m_end; ++it )                        \
			( *it )->call();                                                  \
	}

Y1_FOREACH_PTR_RELOAD( Rva003CFC60, Gen0000D84B )
Y1_FOREACH_PTR_RELOAD( Rva003D2410, Gen00025603 )

// ---------------------------------------------------------------- shape C ---
class Gen000135B1
{
public:
	char m_pad0[ 0x0C ];
	void *m_bfmeItem;
	char m_pad1[ 0x20 ];
	char m_bfmeField0[ 4 ];
	char m_bfmeField1[ 4 ];
	char m_bfmeField2;
	char m_bfmeField3[ 1 ];
	char m_bfmeTail[ 2 ];

	void call( Y1ForEachArg *first, Y1ForEachArg *second );
};

void Gen000135B1::call( Y1ForEachArg *first, Y1ForEachArg *second )
{
	volatile unsigned char accepted = m_bfmeItem != 0;
	first->bfmeTakeAt8C( (void *)&accepted );

	if ( accepted )
	{
		if ( !m_bfmeItem )
		{
			BfmeThingBTB *item = new BfmeThingBTB( TheBfmeCrateNameDefault, 0 );
			m_bfmeItem = item;
		}
	}

	if ( accepted )
		reinterpret_cast<BfmeSubAccept_0002C41C *>( (char *)m_bfmeItem + 4 )->bfmeAccept(
			reinterpret_cast<BfmeSeedTarget *>( first ) );

	first->bfmeTakeAt78( &m_bfmeField0 );
	first->bfmeTakeAt78( &m_bfmeField1 );
	first->bfmeTakeAt88( &m_bfmeField2 );
	first->bfmeTakeAt88( &m_bfmeField3 );
}

class Rva003CD260
{
public:
	char m_lead[ 8 ];
	Gen000135B1 *m_begin;
	Gen000135B1 *m_end;

	void run( Y1ForEachArg *first, Y1ForEachArg *second );
};

void Rva003CD260::run( Y1ForEachArg *first, Y1ForEachArg *second )
{
	for ( Gen000135B1 *it = m_begin; it != m_end; ++it )
		it->call( first, second );
}

// ---------------------------------------------------------------- shape D ---
class Gen00036A9D
{
public:
	char m_lead[ 0x30 ];
	int m_reset;
	char m_tail[ 8 ];

	void call();
};

class Rva003CDE60
{
public:
	char m_lead[ 8 ];
	Gen00036A9D *m_begin;
	Gen00036A9D *m_end;

	void run();
};

void Rva003CDE60::run()
{
	for ( Gen00036A9D *it = m_begin; it != m_end; ++it )
	{
		it->call();
		it->m_reset = 0;
	}
}

// ---------------------------------------------------------------- shape E ---
class Gen00018BF1
{
public:
	void call();
};

class Rva003D2EE0
{
public:
	char m_lead[ 0x0C ];
	Gen00018BF1 **m_begin;
	Gen00018BF1 **m_end;
	char m_mid[ 0x20 ];
	bool m_done;

	void run();
};

void Rva003D2EE0::run()
{
	Gen00018BF1 **end = m_end;
	for ( Gen00018BF1 **it = m_begin; it != end; ++it )
		( *it )->call();

	m_done = false;
}

// ---------------------------------------------------------------- shape F ---
// 0x003D0EE0, 95 bytes, ret 0.  The same walk one level deeper: a leading
// member call on `this`, then an outer walk whose end is read ONCE, and inside
// it an inner walk over the element's own pointer pair at +0x18/+0x1C whose end
// is RE-READ -- the inner loop is shape B, inlined.  Its callee is the same
// 0x0000D84B the shape-B body at 0x003CFC60 calls, which is why the element
// type is reused here rather than minted again.

//
// The two outer loads are in source order: retail reads +0x0C before +0x10, and
// writing the end into a local ahead of the iterator reverses them.  Hence the
// iterator is declared first and the loop header left empty.
//
// The trailing `mov byte [?+0x34],1` is duplicated into both arms, once through
// esi and once through the spilled `this` -- the compiler's tail duplication,
// not two stores in the source.

class Gen0004A5A7
{
public:
	void pre();
};

class Rva003D0EE0
{
public:
	char m_lead[ 0x0C ];
	Rva003CFC60 **m_begin;
	Rva003CFC60 **m_end;
	char m_mid[ 0x20 ];
	bool m_done;

	void run();
};

void Rva003D0EE0::run()
{
	( (Gen0004A5A7 *)this )->pre();

	Rva003CFC60 **it = m_begin;
	Rva003CFC60 **end = m_end;
	for ( ; it != end; ++it )
	{
		Rva003CFC60 *group = *it;
		for ( Gen0000D84B **e = group->m_begin; e != group->m_end; ++e )
			( *e )->call();
	}

	m_done = true;
}

// ---------------------------------------------------- LargeGroupAudio ---
// 0x003D2440, 61 bytes.  GameLogic phase 5 calls this through the
// LargeGroupAudio subsystem vtable.  Its inner loop is the already matched
// 0x003D2410 shape above, inlined here; the shared 0x00025603 callee thunk
// fixes the element call identity.

class LargeGroupAudio
{
public:
	virtual void update();

	char m_lead[ 8 ];
	Rva003D2410 **m_begin;
	Rva003D2410 **m_end;
	char m_mid[ 0x20 ];
	bool m_done;
};

void LargeGroupAudio::update()
{
	if ( m_done )
		return;

	Rva003D2410 **it = m_begin;
	Rva003D2410 **end = m_end;
	for ( ; it != end; ++it )
	{
		Rva003D2410 *group = *it;
		for ( Gen00025603 **e = group->m_begin; e != group->m_end; ++e )
			( *e )->call();
	}
}
