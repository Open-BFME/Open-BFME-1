// ?d_005eff60@@YAXXZ
// partial score=0.3 date=2026-09-25
// Retail RVA 0x005EFF60, 349 B.
// The address-derived owner and base names preserve unresolved identity.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

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
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeA1189
{
public:
	BfmeA1189();
	virtual ~BfmeA1189()
	{
		*(volatile unsigned int *)this = 0x01073744;
	}
	BfmeQuad1189 m_bfme04[8];
	int m_bfme84;
};

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

class BaseY005E5D90Category
{
public:
	virtual void categorySlot();
};

class BaseY005E5D90
	: public BaseY005E5D90Primary,
	  public BaseY005E5D90Category,
	  public BfmeA1189
{
public:
	BaseY005E5D90(OwnerY005E5D90 *owner);
};

BaseY005E5D90::BaseY005E5D90(OwnerY005E5D90 *owner)
{
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
