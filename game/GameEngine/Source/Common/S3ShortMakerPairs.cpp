// Eight bodies in four pairs. Each pair sign-extends a 16-bit argument, pushes
// it twice, and calls the same cdecl maker; one of the pair throws the result
// away and the other stores it at +0x04 of this.
//
//     movsx eax, word ptr [esp + 4]
//     push eax / push eax
//     call <maker>
//     add esp, 8
//
// movsx rather than movzx makes the argument signed, and the two identical
// pushes are one value used for both parameters -- the maker takes it twice.
// The pairing is the evidence that the two shapes belong together: each pair
// reaches the same thunk, and only those four thunks.
//
// The throw-away halves clean their own argument while never touching ecx, so
// they are __stdcall; the storing halves keep ecx and are members.

int __cdecl Rva005277B0(int, int);			// ILT 0x000364C6 -> 0x005277B0
int __cdecl Rva0054E760(int, int);			// ILT 0x0000B500 -> 0x0054E760
int __cdecl Rva0054E960(int, int);			// ILT 0x00029771 -> 0x0054E960
int __cdecl Rva0056DEC0(int, int);			// ILT 0x0003C65A -> 0x0056DEC0

#define bfmeMake_00528ef0(a, b) ((void *)Rva005277B0((int)(a), (int)(b)))
#define bfmeMake_0054ed70(a, b) ((void *)Rva0054E760((int)(a), (int)(b)))
#define bfmeMake_0054ee00(a, b) ((void *)Rva0054E960((int)(a), (int)(b)))
#define bfmeMake_0056e1c0(a, b) ((void *)Rva0056DEC0((int)(a), (int)(b)))

class Gen_005292a0
{
public:
	void bfmeSet(short value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};


class Gen_0054f300
{
public:
	void bfmeSet(short value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};


class Gen_0054f390
{
public:
	void bfmeSet(short value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};


class Gen_0056e7c0
{
public:
	void bfmeSet(short value);

	char m_bfmeHead[0x04];
	void *m_bfmeMade;						// +0x04
};

// ?Gen_00528ef0@@YGXF@Z
void __stdcall Gen_00528ef0(short value)
{
	bfmeMake_00528ef0(value, value);
}

// ?bfmeSet@Gen_005292a0@@QAEXF@Z
void Gen_005292a0::bfmeSet(short value)
{
	m_bfmeMade = bfmeMake_00528ef0(value, value);
}

// ?Gen_0054ed70@@YGXF@Z
void __stdcall Gen_0054ed70(short value)
{
	bfmeMake_0054ed70(value, value);
}

// ?bfmeSet@Gen_0054f300@@QAEXF@Z
void Gen_0054f300::bfmeSet(short value)
{
	m_bfmeMade = bfmeMake_0054ed70(value, value);
}

// ?Gen_0054ee00@@YGXF@Z
void __stdcall Gen_0054ee00(short value)
{
	bfmeMake_0054ee00(value, value);
}

// ?bfmeSet@Gen_0054f390@@QAEXF@Z
void Gen_0054f390::bfmeSet(short value)
{
	m_bfmeMade = bfmeMake_0054ee00(value, value);
}

// ?Gen_0056e1c0@@YGXF@Z
void __stdcall Gen_0056e1c0(short value)
{
	bfmeMake_0056e1c0(value, value);
}

// ?bfmeSet@Gen_0056e7c0@@QAEXF@Z
void Gen_0056e7c0::bfmeSet(short value)
{
	m_bfmeMade = bfmeMake_0056e1c0(value, value);
}
