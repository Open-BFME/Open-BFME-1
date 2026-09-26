// cl: /DNDEBUG /MD /EHsc

// The adjusted-owner factory at 0x005E6290 calls this 187-byte constructor
// with the receiver minus 0x14.  Retail lays out a two-vptr category base at
// +0/+4, a flag at +8, and a polymorphic owner-fields base at +0xc.  The
// address-qualified BaseY name is the call-derived identity used by the
// adjacent adjusted-owner constructor family.

class FXList;

namespace FXParticleSystem
{
class TerrainCollisionEventFXLookupShim
{
public:
	const FXList *lookup(const char *name) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

template <int Category>
struct DefaultModuleName
{
	static const char VALUE[1];
};
}

class BfmeVal1027
{
public:
	float bfmeVal1027();
};

class OwnerY005E6290
{
public:
	unsigned char m_pad00[0x1d];
	unsigned char m_flag1d;
	unsigned char m_pad1e[0x6];
	const char *m_name;
	BfmeVal1027 m_random;
	unsigned char m_pad2c[0x8];
	const FXList *m_cached;
};

class __declspec(novtable) CategoryPrimaryY005E6290
{
public:
	virtual ~CategoryPrimaryY005E6290();
};

class __declspec(novtable) CategoryInfoY005E6290
{
public:
	__declspec(nothrow) CategoryInfoY005E6290()
	{
		// The volatile store preserves the interim CategoryModuleInfo<8>
		// vtable before MSVC emits the delayed EH callee-save pair.
		*(volatile unsigned int *)this = 0x0107375c;
		*(volatile unsigned char *)((unsigned char *)this + 4) = true;
	}
	virtual void unused();

protected:
	volatile unsigned char m_flag;
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

class __declspec(novtable) CategoryTemplateY005E6290
	: public CategoryBaseY005E6290
{
public:
	CategoryTemplateY005E6290()
		: CategoryBaseY005E6290() {}
	__declspec(nothrow) virtual ~CategoryTemplateY005E6290();
};

class OwnerFieldsY005E6290
{
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

// ??0BaseY005E6290@@QAE@PAVOwnerY005E6290@@@Z
BaseY005E6290::BaseY005E6290(OwnerY005E6290 *owner)
	: CategoryTemplateY005E6290(), OwnerFieldsY005E6290(owner)
{
	m_value = (int)owner->m_random.bfmeVal1027();

	if (!owner->m_cached)
	{
		const char *name = owner->m_name;
		owner->m_cached = FXParticleSystem::g_terrainCollisionEventFXListStore->lookup(
			name ? name + 8 : FXParticleSystem::DefaultModuleName<8>::VALUE);
	}

	m_eventFX = owner->m_cached;
	m_flag = owner->m_flag1d;
}
