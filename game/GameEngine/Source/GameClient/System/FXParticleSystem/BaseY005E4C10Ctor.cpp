// cl: /DNDEBUG /MD /EHsc

class FXList;

namespace FXParticleSystem
{
class TerrainCollisionEventFXLookupShim
{
public:
	const FXList *lookup( const char *name ) const;
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

class OwnerY005E4C10
{
public:
	unsigned char m_pad00[ 0x1d ];
	unsigned char m_flag1d;
	unsigned char m_pad1e[ 0x6 ];
	const char *m_name;
	BfmeVal1027 m_random;
	unsigned char m_pad2c[ 0x8 ];
	unsigned char m_pad31[ 0x3 ];
	unsigned char m_flag34;
	unsigned char m_pad35[ 0x3 ];
	const FXList *m_cached;
};

class __declspec(novtable) CategoryPrimaryY005E4C10
{
public:
	virtual ~CategoryPrimaryY005E4C10();
};

class __declspec(novtable) CategoryInfoY005E4C10
{
public:
	__declspec(nothrow) CategoryInfoY005E4C10()
	{
		*(volatile unsigned int *)this = 0x0107375c;
		*(volatile unsigned char *)((unsigned char *)this + 4) = true;
	}
	virtual void unused();

protected:
	volatile unsigned char m_flag;
};

class __declspec(novtable) CategoryBaseY005E4C10
	: public CategoryPrimaryY005E4C10,
	  public CategoryInfoY005E4C10
{
public:
	CategoryBaseY005E4C10()
		: CategoryPrimaryY005E4C10(), CategoryInfoY005E4C10() {}
	__declspec(nothrow) virtual ~CategoryBaseY005E4C10();
};

class __declspec(novtable) CategoryTemplateY005E4C10
	: public CategoryBaseY005E4C10
{
public:
	CategoryTemplateY005E4C10()
		: CategoryBaseY005E4C10() {}
	__declspec(nothrow) virtual ~CategoryTemplateY005E4C10();
};

class OwnerFieldsY005E4C10
{
public:
	OwnerFieldsY005E4C10( OwnerY005E4C10 * )
		: m_value( 0.0f ), m_eventFX( 0 ), m_flag( false ) {}
	virtual ~OwnerFieldsY005E4C10();

protected:
	float m_value;
	const FXList *m_eventFX;
	unsigned char m_flag;
};

class BaseY005E4C10
	: public CategoryTemplateY005E4C10,
	  public OwnerFieldsY005E4C10
{
public:
	BaseY005E4C10( OwnerY005E4C10 *owner );
	virtual ~BaseY005E4C10();
};

// ??0BaseY005E4C10@@QAE@PAVOwnerY005E4C10@@@Z
BaseY005E4C10::BaseY005E4C10( OwnerY005E4C10 *owner )
	: CategoryTemplateY005E4C10(), OwnerFieldsY005E4C10( owner )
{
	m_value = owner->m_random.bfmeVal1027();

	if ( !owner->m_cached )
	{
		const char *name = owner->m_name;
		owner->m_cached = FXParticleSystem::g_terrainCollisionEventFXListStore->lookup(
			name ? name + 8 : FXParticleSystem::DefaultModuleName<8>::VALUE );
	}

	m_eventFX = owner->m_cached;
	OwnerFieldsY005E4C10::m_flag = owner->m_flag34;
	CategoryInfoY005E4C10::m_flag = owner->m_flag1d;
}
