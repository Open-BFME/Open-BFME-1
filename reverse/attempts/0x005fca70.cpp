// ?d_005fca70@@YAXXZ
// partial score=0.94 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
//
// Focused reconstruction of the 187-byte constructor at RVA 0x005FCA70.
// The only identity evidence is the adjusted-owner factory at 0x005E6290,
// whose named constructor call reaches this body through its retail thunk.
// The BaseY name remains address-derived; the class names below describe the
// ABI layout being tested, not a recovered game type.
//
// Retail first constructs a two-vptr category base (+0/+4, with a byte at
// +8) and a second polymorphic base at +0xc.  That second base owns the two
// dwords at +0x10/+0x14.  The complete constructor then stamps all three
// final vptrs and fills those fields from the adjusted owner at +0x1d,
// +0x24, +0x28 and +0x34.
//
// REMAINING WALL (8/187 non-reloc bytes, first at +27; one relocation site
// out of 14 lands at a different offset than retail): the interim vtable
// store at [esi+4]=CategoryInfoY005E6290's vtable and a `push edi; mov
// [esp+8],esi` pair (a delayed callee-save of edi plus an EH-frame this-stash
// slot) are two independent, commutable chunks. Retail emits the vtable
// store first, then the push/mov pair, then completes CategoryInfoY005E6290's
// own m_flag=true store; ours emits the push/mov pair first, then the vtable
// store, then the same m_flag store. Every other byte in the body, including
// both OwnerFieldsY005E6290 stores and both final-vtable stamps, already
// matches.
// Ruled out (14 shape_search trials, masked score pinned at 0.95722 for every
// variant): writing CategoryInfoY005E6290's m_flag through a constructor-body
// assignment instead of the member-initializer list; reversing the
// CategoryPrimaryY005E6290/CategoryInfoY005E6290 base-initializer order;
// dropping __declspec(nothrow) from CategoryBaseY005E6290's and
// CategoryTemplateY005E6290's destructors; adding __declspec(nothrow) to
// OwnerFieldsY005E6290's constructor. None shifted the push/mov pair relative
// to the vtable store. This is the same base-ctor-EH-shape class of wall
// documented for 0x005FD6A0, now narrowed to a single instruction-scheduling
// decision rather than a whole-body register-allocation difference.

class FXList;

namespace FXParticleSystem {

class TerrainCollisionEventFXLookupShim {
public:
	const FXList *lookup(const char *name) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

template <int Category>
struct DefaultModuleName {
	static const char VALUE[1];
};

}

class BfmeVal1027 {
public:
	float bfmeVal1027() const;
};

class OwnerY005E6290 {
	public:
	unsigned char m_pad00[0x1d];
	unsigned char m_flag1d;
	unsigned char m_pad1e[0x6];
	const char *m_name;
	BfmeVal1027 m_random;
	unsigned char m_pad2c[0x8];
	const FXList *m_cached;
};

class CategoryPrimaryY005E6290 {
public:
	virtual void primary();
};

class CategoryInfoY005E6290 {
public:
	__declspec(nothrow) CategoryInfoY005E6290() : m_flag(true) {}
	virtual void unused();

protected:
	unsigned char m_flag;
};

class __declspec(novtable) CategoryBaseY005E6290
	: public CategoryPrimaryY005E6290,
	  public CategoryInfoY005E6290
{
public:
	CategoryBaseY005E6290()
		: CategoryPrimaryY005E6290(), CategoryInfoY005E6290() {}
	__declspec(nothrow) virtual ~CategoryBaseY005E6290();
};

class __declspec(novtable) CategoryTemplateY005E6290 : public CategoryBaseY005E6290
{
public:
	CategoryTemplateY005E6290()
		: CategoryBaseY005E6290() {}
	__declspec(nothrow) virtual ~CategoryTemplateY005E6290();
};

class OwnerFieldsY005E6290 {
public:
	OwnerFieldsY005E6290(OwnerY005E6290 *)
		: m_value(0), m_eventFX(0) {}
	virtual ~OwnerFieldsY005E6290();

protected:
	int m_value;
	const FXList *m_eventFX;
};

class BaseY005E6290
	: public CategoryTemplateY005E6290,
	  public OwnerFieldsY005E6290
{
public:
	BaseY005E6290(OwnerY005E6290 *owner);
	virtual ~BaseY005E6290();
};

BaseY005E6290::BaseY005E6290(OwnerY005E6290 *owner)
	: CategoryTemplateY005E6290(), OwnerFieldsY005E6290(owner)
{
	m_value = (int)owner->m_random.bfmeVal1027();

	if (!owner->m_cached) {
		const char *name = owner->m_name;
		owner->m_cached = FXParticleSystem::g_terrainCollisionEventFXListStore->lookup(
			name ? name + 8 : FXParticleSystem::DefaultModuleName<8>::VALUE);
	}

	m_eventFX = owner->m_cached;
	m_flag = owner->m_flag1d;
}
