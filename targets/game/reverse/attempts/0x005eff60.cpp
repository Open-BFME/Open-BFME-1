// ??0BaseY005E5D90@@QAE@PAVOwnerY005E5D90@@@Z
// partial score=0.7593 date=2026-09-29
// Retail RVA 0x005EFF60, 349 B.
// The address-derived names preserve unresolved identity.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// The matched BfmeA1189 constructor is defined here so VC7.1 preserves ECX.
// Retail writes EH state 1 at +0x104; this draft still omits that store.

class GameClientRandomVariable {
public:
  enum DistributionType { CONSTANT = 0, UNIFORM, GAUSSIAN };
  float getValue() const;
  DistributionType distribution;
  float minimum;
  float maximum;
};

struct BfmeQuad1189
{
	BfmeQuad1189(void)
	{
		m_bfme08 = 0;
		m_bfme04 = 0;
		m_bfme00 = 0;
		m_bfme0c = 0;
	}
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

extern "C" char g_bfmeV1189[];

class BfmeBase1189
{
public:
	BfmeBase1189() { m_bfme00 = g_bfmeV1189; }
	char *volatile m_bfme00;
};

class BfmeA1189 : public BfmeBase1189
{
public:
	BfmeA1189();
	BfmeQuad1189 m_bfme04[8];
	float m_bfme84;
};

BfmeA1189::BfmeA1189(void)
{
	m_bfme84 = 0.0f;
}

class OwnerY005E5D90
{
public:
	char m_pad00[0x20];
	BfmeQuad1189 m_bfme04[8];
	GameClientRandomVariable m_value;
};

class __declspec(novtable) BaseY005E5D90Primary
{
public:
	virtual void primarySlot();
};

class PolymorphicVptrBase01073760
{
public:
	virtual void unusedVirtual();
	virtual ~PolymorphicVptrBase01073760() {}
};

class BaseY005E5D90
	: public BaseY005E5D90Primary,
	  public PolymorphicVptrBase01073760,
	  public BfmeA1189
{
public:
	BaseY005E5D90(OwnerY005E5D90 *owner);
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

BaseY005E5D90::BaseY005E5D90(OwnerY005E5D90 *owner)
	: BaseY005E5D90Primary(),
	  PolymorphicVptrBase01073760(),
	  BfmeA1189()
{
	*(volatile unsigned int *)((unsigned char *)this + 0x08) = 0x0111279c;
	*(volatile unsigned int *)this = 0x0111290c;
	*(volatile unsigned int *)((unsigned char *)this + 0x04) = 0x011127b0;
	_ReadWriteBarrier();
	m_bfme04[0] = owner->m_bfme04[0];
	m_bfme04[1] = owner->m_bfme04[1];
	m_bfme04[2] = owner->m_bfme04[2];
	m_bfme04[3] = owner->m_bfme04[3];
	m_bfme04[4] = owner->m_bfme04[4];
	m_bfme04[5] = owner->m_bfme04[5];
	m_bfme04[6] = owner->m_bfme04[6];
	m_bfme04[7] = owner->m_bfme04[7];
	m_bfme84 = owner->m_value.getValue();
}
