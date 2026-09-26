// ?method@Rva001F7CC0Owner@@QAEXXZ
// partial score=0.43 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x001F7CC0 (208 bytes). thiscall, no explicit stack args (ret 4
// is the hidden-this ABI's own cleanup? see below), builds a 320-bit "clear"
// model-condition mask (bits 154..159 set via a single OR of 0xfc000000 into
// its fifth dword) and an empty "set" mask, calls
// Object::clearAndSetModelConditionFlags through a secondary-vtable object at
// this-0x18 (negative offset -> secondary base, docs/shape_levers.md), zeroes
// this->+8, and on success dispatches Drawable::applyPendingModelConditionFlags
// on the object a vtable+0x28 call on that same this-0x18 object returns.
// callers_of finds no named caller and no vtable slot names this method, so
// it lands under an opaque address-derived name.

typedef int Int;
typedef bool Bool;

struct BfmeC1166
{
	unsigned int m_bfme00[10];
};

class Rva001F7CC0Overridable
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void unused1c();
	virtual void unused20();
	virtual void unused24();
	virtual class Rva001F7CC0Drawable *getFinal();   // slot 0x28
};

class Rva001F7CC0Object
{
public:
	// pinned callee: ?clearAndSetModelConditionFlags@Object@@QAEXABV?$BitFlags@$0BEA@@@0@Z
	void clearAndSetModelConditionFlags( const BfmeC1166 &clear, const BfmeC1166 &set );
};

class Rva001F7CC0Drawable
{
public:
	// pinned callee: ?applyPendingModelConditionFlags@Drawable@@AAEX_N@Z
	void applyPendingModelConditionFlags( Bool immediate );
};

class Rva001F7CC0Owner
{
public:
	void method( void );

	char m_unreconstructed_00[8];
	Int m_field8;                       // +0x8
	char m_unreconstructed_0c[0x18 - 0xc];
	Rva001F7CC0Overridable *m_secondaryNeg18;   // reached via this-0x18
};

// ?rva001f7cc0@Rva001F7CC0Owner@@QAEXXZ
void Rva001F7CC0Owner::method( void )
{
	Rva001F7CC0Drawable *drawable =
		( *(Rva001F7CC0Overridable **)( (char *)this - 0x18 ) )->getFinal();
	if ( !drawable )
		return;

	BfmeC1166 clear;
	BfmeC1166 set;
	clear.m_bfme00[0] = 0;
	set.m_bfme00[0] = 0;
	clear.m_bfme00[1] = 0;
	set.m_bfme00[1] = 0;
	clear.m_bfme00[2] = 0;
	set.m_bfme00[2] = 0;
	clear.m_bfme00[3] = 0;
	set.m_bfme00[3] = 0;
	clear.m_bfme00[4] = 0xfc000000;
	set.m_bfme00[4] = 0;
	clear.m_bfme00[5] = 0;
	set.m_bfme00[5] = 0;
	clear.m_bfme00[6] = 0;
	set.m_bfme00[6] = 0;
	clear.m_bfme00[7] = 0;
	set.m_bfme00[7] = 0;
	clear.m_bfme00[8] = 0;
	set.m_bfme00[8] = 0;
	clear.m_bfme00[9] = 0;
	set.m_bfme00[9] = 0;

	m_field8 = 0;
	( *(Rva001F7CC0Object **)( (char *)this - 0x18 ) )->clearAndSetModelConditionFlags( clear, set );

	drawable->applyPendingModelConditionFlags( false );
}
