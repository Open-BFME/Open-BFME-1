// Ten bodies that a mnemonic-only grouping filed together as "a few moves and a
// ret".  They are not one family and never were: what follows is TEN shapes
// that happen to be built out of the same instruction names.  Each is landed on
// its own evidence.
//
// WHAT THE BYTES DECIDE HERE, shape by shape:
//
//  * 0x0007BE10 and 0x00490280 open with `mov eax,ecx`, define eax and never
//    read it again.  That is a RETURN VALUE, and a __thiscall body that hands
//    `this` back for no other reason is a constructor tail -- so both are
//    spelled as constructors.
//  * 0x00490280 stores 0x010F9AD8 into the object at +0 BEFORE anything else.
//    MSVC 7.1 always writes the vptr before any member initialiser, so a
//    leading dword store is a vptr and the class has virtuals.  What follows is
//    the two-instruction intrusive-list push: m_next = head; head = this.
//  * 0x000C81E0 and 0x0016A2E0 load one integer constant into eax and store it
//    to several slots.  0x3F800000 and 0xC2C80000 are the bit patterns of 1.0f
//    and -100.0f; MSVC copies float constants through an integer register.
//    The STORE ORDER tells the two apart: ascending offsets are separate
//    statements, descending offsets are a chained assignment (`a = b = c = k`
//    evaluates rightmost first).
//  * 0x0085CE00 and 0x0085D360 end with `mov eax,1` -- five bytes, not the
//    two-byte `mov al,1`.  That is an INT return, not a bool.  The source dword
//    is loaded before the destination pointer, which is argument order.
//  * 0x000BEED0 and 0x000DFB80 take three dwords off the stack and return the
//    first one.  No `this` is involved: they are free functions.
//  * 0x0071CF10 writes four bytes at displacements above 0x1E0000.  Nothing
//    else in the bytes explains an object that large; the padding below only
//    reproduces the displacements and claims nothing about what fills it.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// vftable and global addresses are relocation sites, so their four bytes come
// from retail and are NOT evidence of anything beyond "a vptr" and "a global".

// ---------------------------------------------------------------- 0x0007BE10

class Rva0007BE10
{
public:
	Rva0007BE10();
	int m_count;
	bool m_first;
	bool m_second;
};
Rva0007BE10::Rva0007BE10()
{
	m_count = 2;
	m_first = true;
	m_second = true;
}

// ------------------------------------------------- 0x000BEED0 and 0x000DFB80

class R1DwordPair
{
public:
	int m_first;
	int m_second;
};

R1DwordPair *Rva000BEED0( R1DwordPair *pair, int first, int second )
{
	pair->m_first = first;
	pair->m_second = second;
	return pair;
}

R1DwordPair *Rva000DFB80( R1DwordPair *pair, int first, int second )
{
	pair->m_first = first;
	pair->m_second = second;
	return pair;
}

// ---------------------------------------------------------------- 0x000C81E0

class Rva000C81E0
{
public:
	void reset();
	float m_a;
	float m_b;
	float m_c;
	float m_d;
};
void Rva000C81E0::reset()
{
	m_a = 1.0f;
	m_b = 1.0f;
	m_c = 1.0f;
	m_d = 1.0f;
}

// ---------------------------------------------------------------- 0x0016A2E0

class Rva0016A2E0
{
public:
	void reset();
	char m_lead[ 0x34 ];
	float m_a;
	float m_b;
	float m_c;
	char m_pad[ 4 ];
	int m_count;
};
void Rva0016A2E0::reset()
{
	m_a = m_b = m_c = -100.0f;
	m_count = -5;
}

// ---------------------------------------------------------------- 0x003BDAB0

class Rva003BDAB0
{
public:
	void reset();
	char m_lead[ 0x78 ];
	bool m_firstFlag;
	char m_pad0[ 3 ];
	int m_firstValue;
	char m_mid[ 0x48 ];
	bool m_secondFlag;
	char m_pad1[ 3 ];
	int m_secondValue;
};
void Rva003BDAB0::reset()
{
	m_secondFlag = true;
	m_secondValue = 0x78;
	m_firstFlag = true;
	m_firstValue = 0x1e;
}

// ---------------------------------------------------------------- 0x00490280

class Rva00490280;
extern Rva00490280 *g_Glo00EF3350;

class Rva00490280
{
public:
	Rva00490280();
	virtual void v0();
	Rva00490280 *m_next;
};
Rva00490280::Rva00490280()
{
	m_next = g_Glo00EF3350;
	g_Glo00EF3350 = this;
}

// ---------------------------------------------------------------- 0x0071CF10

class Rva0071CF10
{
public:
	void reset();
	char m_lead[ 0x1e1ccc ];
	bool m_a;
	bool m_b;
	char m_pad[ 3 ];
	bool m_c;
	char m_mid[ 0x1e391c - 0x1e1cd2 ];
	bool m_d;
};
void Rva0071CF10::reset()
{
	m_c = true;
	m_d = true;
	m_a = true;
	m_b = true;
}

// ------------------------------------------------- 0x0085CE00 and 0x0085D360

class R1DwordCell
{
public:
	int m_value;
};

int Rva0085CE00( R1DwordCell *destination, const R1DwordCell *source )
{
	destination->m_value = source->m_value;
	return 1;
}

int Rva0085D360( R1DwordCell *destination, const R1DwordCell *source )
{
	destination->m_value = source->m_value;
	return 1;
}

// ---------------------------------------------------------------- 0x005FC7D0
//
// Another constructor tail, and the one place in this file where the LAYOUT is
// forced rather than chosen.  The body writes [this+4] twice:
//
//     mov [eax+4],<A> / mov byte [eax+8],1 / mov [eax],<B> / mov [eax+4],<C>
//
// Three different dwords at two vptr-shaped slots is the multiple-inheritance
// signature: a base subobject at +4 brings its own vptr, its constructor is
// inlined (that is the store of <A> and the byte member at +8), and then the
// most-derived constructor stamps BOTH vptrs with its own tables.  The base at
// +0 contributes no store of its own, which is what happens when that base has
// no user-written constructor: MSVC folds its vptr into the derived
// initialisation instead of inlining a base constructor for it.
//
// All three dwords are relocation sites and their bytes come from retail, so
// they are not evidence about which tables these are.

class Rva005FC7D0BaseA
{
public:
	virtual void av();
};

class Rva005FC7D0BaseB
{
public:
	// Defined IN-CLASS, hence implicitly inline. Written out of line this is a
	// non-inline function that MSVC emits as its own COMDAT in addition to
	// inlining it here -- an emitted body no ledger row accounts for, which is
	// what find_declared_unmatched rejects. In-class it is inlined into the
	// derived constructor and nothing standalone is emitted; the derived body
	// verifies byte-identical either way.
	Rva005FC7D0BaseB() { m_flag = true; }
	virtual void bv();
	bool m_flag;
};

class Rva005FC7D0 : public Rva005FC7D0BaseA, public Rva005FC7D0BaseB
{
public:
	Rva005FC7D0();
	virtual void dv();
};
Rva005FC7D0::Rva005FC7D0() {}
