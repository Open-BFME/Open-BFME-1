// Open-BFME5 conversions.

// The member copy is StringBase<char>'s copy constructor (call target
// 0x00887B60, matched as ??0?$StringBase@D@@AAE@ABV0@@Z).
class BfmeThingVKE;
template <class T> class StringBase
{
	friend class BfmeThingVKE;
	StringBase(const StringBase &o);
	void *m_data;
};

class BfmeUniVKE
{
public:
	void *m_bfme00;
};

struct BfmeBlockVKE
{
	int m_bfmeArr[16];
};

class BfmeThingVKE
{
public:
	BfmeThingVKE *bfmeInitVKE(const BfmeThingVKE &o);
	BfmeUniVKE m_bfme00;
	char m_bfme04;
	char m_bfmePad05[3];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBlockVKE m_bfme18;
};

BfmeThingVKE *BfmeThingVKE::bfmeInitVKE(const BfmeThingVKE &o)
{
	((StringBase<char> *)&m_bfme00)->StringBase<char>::StringBase(*(const StringBase<char> *)&o.m_bfme00);
	m_bfme04 = o.m_bfme04;
	m_bfme08 = o.m_bfme08;
	m_bfme0c = o.m_bfme0c;
	m_bfme10 = o.m_bfme10;
	m_bfme14 = o.m_bfme14;
	m_bfme18 = o.m_bfme18;
	return this;
}
