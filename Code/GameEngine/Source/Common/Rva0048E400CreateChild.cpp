// retail 0x0048E400, 98 bytes.
//
// Fuzzy twin of 0x0035B680 (Bfme5MakeAndReturn.cpp, ratio 0.942): both are a
// guarded `new` of a fixed-size class inside a scope-table EH frame.  Two
// things differ from the twin's `return new X(this);` shape:
//   - the constructed pointer is written through `this` (esi) to a member at
//     +0x08, not returned in eax -- the function is void, not a pointer type;
//   - the constructor call passes NO owner argument (only ecx=the raw block),
//     matching the credited default constructor already landed at 0x00471EC0
//     (`??0Gen_00471EC0@@QAE@XZ`, BfmeCreditedCtorWA.cpp) and reached here
//     through the pinned ILT thunk ?j_00001582@@YAXXZ -> FUN_00871ec0.
//
// Gen_00471EC0's own fields sum to 0x4C; retail pushes 0x54 as the allocation
// size, so the true layout carries 8 more trailing bytes than the landed
// declaration models (left unresolved there too, see its "left alone" note).
// Only sizeof() matters here -- the constructor BODY lives in the other TU,
// so this file only DECLARES the class (opaque base, no method bodies) with
// a trailing pad field to reach 0x54; the call resolves to the one real ctor.
//
// IDENTITY IS NOT RECOVERED for the outer object or the member; both names
// are address-derived.

class BfmeStrWA
{
public:
	BfmeStrWA(const char *text);
	~BfmeStrWA(void);

private:
	char *m_bfmeData;
};

struct BfmeTripleWA
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class BfmeGuardWA
{
public:
	~BfmeGuardWA(void);
};

class Gen_00471EC0 : public BfmeGuardWA
{
public:
	Gen_00471EC0(void);

	int *m_bfmeVtable;					// +0x00
	char m_bfmePad04[0x18];					// +0x04
	int m_bfmeX;						// +0x1C
	int m_bfmeY;						// +0x20
	BfmeStrWA m_bfmeName;					// +0x24
	int m_bfmeCode;						// +0x28
	int m_bfmeCount;					// +0x2C
	int m_bfmeLimit;					// +0x30
	BfmeTripleWA m_bfmeFirst;				// +0x34
	BfmeTripleWA m_bfmeSecond;				// +0x40
	int m_bfmePad2[2];					// +0x4C, unresolved tail to 0x54
};

class Gen_0048E400
{
public:
	void bfmeCreateChild(void);

private:
	char m_bfmePad[8];					// +0x00
	Gen_00471EC0 *m_bfmeChild;				// +0x08
};

// ?bfmeCreateChild@Gen_0048E400@@QAEXXZ
void Gen_0048E400::bfmeCreateChild(void)
{
	m_bfmeChild = new Gen_00471EC0();
}
