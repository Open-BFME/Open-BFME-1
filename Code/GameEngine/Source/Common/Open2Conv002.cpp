// Nine small bodies recovered from byte-true dumps.  Identity is NOT recovered
// for any of them: every class, member and function name is derived from the
// address it lives at, and the padding virtuals exist only to place the slot
// each body actually calls.

// ---------------------------------------------------------------------------
// 0x0056AD60 -- store 3 when a pointer is set, 1 when it is not.
//
//     mov edx,[ecx+0x25c] / xor eax,eax / test edx,edx / setne al
//     lea eax,[eax+eax+1] / mov [ecx+0x258],eax / ret
//
// `setne` + `lea eax,[eax+eax+1]` is MSVC's branchless form of a two-valued
// select whose arms differ by two: it never appears for arbitrary constants,
// so the pair really is {1, 3} and not a lookup.

class Rva0056AD60
{
public:
	void refresh( void );
	char m_pad[0x258];
	int m_state;
	void *m_source;
};

// @?refresh@Rva0056AD60@@QAEXXZ 0x0056AD60
void Rva0056AD60::refresh( void )
{
	m_state = m_source ? 3 : 1;
}

// ---------------------------------------------------------------------------
// 0x00581870 -- null-checked tail dispatch through slot 0x20, -1 when unset.
//
//     mov eax,[ecx+0x34] / test eax,eax / je none / mov ecx,eax
//     mov eax,[ecx] / jmp [eax+0x20] / none: or eax,-1 / ret
//
// Control leaves through `jmp`, so the callee's `ret` is ours: with a bare
// `ret` on this side both are __thiscall taking no stack arguments.  The
// no-object arm is `or eax,-1`, the dword form, so the result is int-wide.

class Gen00581870Slot20
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
	virtual int slot0C();
	virtual int slot10();
	virtual int slot14();
	virtual int slot18();
	virtual int slot1C();
	virtual int slot20();
};

class Rva00581870
{
public:
	int query( void ) const;
	char m_pad[0x34];
	Gen00581870Slot20 *m_held;
};

// @?query@Rva00581870@@QBEHXZ 0x00581870
int Rva00581870::query( void ) const
{
	if( m_held )
		return m_held->slot20();
	return -1;
}

// ---------------------------------------------------------------------------
// 0x005C3140 -- the same shape through slot 0x28, answering 1 when unset.

class Gen005C3140Slot28
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
	virtual int slot0C();
	virtual int slot10();
	virtual int slot14();
	virtual int slot18();
	virtual int slot1C();
	virtual int slot20();
	virtual int slot24();
	virtual int slot28();
};

class Rva005C3140
{
public:
	int query( void ) const;
	char m_pad[0x94];
	Gen005C3140Slot28 *m_held;
};

// @?query@Rva005C3140@@QBEHXZ 0x005C3140
int Rva005C3140::query( void ) const
{
	Gen005C3140Slot28 *held = m_held;
	if( held )
		return held->slot28();
	return 1;
}

// ---------------------------------------------------------------------------
// 0x0059FCF0 -- run a one-shot through a virtual, then latch a second flag.
//
//     mov al,[esi+0x1c] / test al,al / jne done / mov eax,[esi]
//     mov [esi+0x20],0x3f800000 / call [eax+0x10] / done: mov [esi+0x24],1
//
// 0x3f800000 is 1.0f.  The store lands between the vtable load and the call,
// which is scheduling, not order: it is the only statement that can precede a
// call whose vptr has already been fetched.

class Rva0059FCF0
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	void begin( void );
	char m_pad[0x18];
	char m_started;
	char m_pad2[3];
	float m_scale;
	char m_running;
};

// @?begin@Rva0059FCF0@@QAEXXZ 0x0059FCF0
void Rva0059FCF0::begin( void )
{
	if( !m_started )
	{
		m_scale = 1.0f;
		slot10();
	}
	m_running = 1;
}

// ---------------------------------------------------------------------------
// 0x005A41F0 -- bump a counter, then run two members, the second as a tail jump.
//
//     push esi / mov esi,ecx / inc [esi+0xe18] / call <REL32> / mov ecx,esi
//     pop esi / jmp <REL32>
//
// Neither call passes a stack argument and both are entered with `this`, so
// both are __thiscall and nullary; the second leaves through `jmp`, which is
// what a void call in tail position compiles to.

class Rva005A41F0
{
public:
	void advance( void );
	void tick( void );
	void publish( void );
	char m_pad[0xe18];
	int m_counter;
};

// @?advance@Rva005A41F0@@QAEXXZ 0x005A41F0
void Rva005A41F0::advance( void )
{
	++m_counter;
	tick();
	publish();
}

// ---------------------------------------------------------------------------
// 0x005D0490 -- create the held object the first time it is asked for.
//
//     mov eax,[ecx] / test eax,eax / jne have / jmp <REL32> / have: ret
//
// The pointer is LOADED into eax rather than compared in place, and the
// non-null arm falls straight into `ret` with it still there: the accessor
// hands the object back, and the create path is a tail jump because its
// return value becomes this one's.

class Rva005D0490
{
public:
	void *ensure( void );
	void *create( void );
	void *m_held;
};

// @?ensure@Rva005D0490@@QAEPAXXZ 0x005D0490
void *Rva005D0490::ensure( void )
{
	if( !m_held )
		return create();
	return m_held;
}

// ---------------------------------------------------------------------------
// 0x005F0D10 and 0x005F5500 -- delete two global singletons of one class.
//
//     mov ecx,[GLOBAL] / test ecx,ecx / push esi / mov esi,ecx / je done
//     call <DTOR> / push esi / call operator delete / add esp,4 / done: pop esi
//
// The destructor is reached by a direct call rather than through vtable slot 0,
// so the class is NOT polymorphic, and the slot is left holding its old value
// -- neither body writes the global back.  Both reach the same destructor at
// 0x0090F680, so the two globals hold the same type.

class Gen0090F680
{
public:
	~Gen0090F680();
};

extern Gen0090F680 *TheGen012F6D88;
extern Gen0090F680 *TheGen012F6DFC;

// @?Rva005F0D10@@YAXXZ 0x005F0D10
void Rva005F0D10( void )
{
	delete TheGen012F6D88;
}

// @?Rva005F5500@@YAXXZ 0x005F5500
void Rva005F5500( void )
{
	delete TheGen012F6DFC;
}

// ---------------------------------------------------------------------------
// 0x0060C120 -- refresh, then react when one member has overtaken another.
//
//     push esi / mov esi,ecx / call <REL32> / mov eax,[esi+0x30]
//     cmp eax,[esi+0x40] / jbe done / mov ecx,esi / pop esi / jmp <REL32>
//
// `jbe` makes the comparison unsigned, so both members are unsigned.

class Rva0060C120
{
public:
	void poll( void );
	void refresh( void );
	void overflow( void );
	char m_pad[0x30];
	unsigned int m_used;
	char m_pad2[0xc];
	unsigned int m_limit;
};

// @?poll@Rva0060C120@@QAEXXZ 0x0060C120
void Rva0060C120::poll( void )
{
	refresh();
	if( m_used > m_limit )
		overflow();
}
