class BfmeThingCFF;

class BfmeOwnerCFF
{
public:
	void bfmeDetachCFF(BfmeThingCFF *what);
	void bfmeAttachCFF(BfmeThingCFF *what);
};

class BfmeThingCFF
{
public:
	void bfmeGoCFF(BfmeOwnerCFF *owner);
	unsigned char m_bfmeHead[8];
	BfmeOwnerCFF *m_bfmeOwner;
};

void BfmeThingCFF::bfmeGoCFF(BfmeOwnerCFF *owner)
{
	if (owner != 0)
	{
		if (m_bfmeOwner != 0)
			m_bfmeOwner->bfmeDetachCFF(this);
		m_bfmeOwner = owner;
		owner->bfmeAttachCFF(this);
	}
}
