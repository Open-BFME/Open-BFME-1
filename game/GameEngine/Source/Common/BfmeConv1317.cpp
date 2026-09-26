// Open-BFME5 conversions.

class BfmeSubTLB
{
public:
	virtual void bfmeV0TLB();
	virtual void bfmeV1TLB();
	virtual void bfmeV2TLB();
	virtual void bfmeV3TLB();
	virtual void bfmeV4TLB();
	virtual void bfmeV5TLB();
	virtual void bfmeV6TLB();
	virtual void bfmeV7TLB();
	virtual void bfmeV8TLB();
	virtual void bfmeV9TLB();
	virtual void bfmeV10TLB();
	virtual void bfmeV11TLB();
	virtual void bfmeV12TLB();
	virtual void bfmeV13TLB();
	virtual void bfmeV14TLB();
	virtual void bfmeV15TLB();
	virtual void bfmeV16TLB();
	virtual void bfmeV17TLB();
	virtual void bfmeV18TLB();
	virtual void bfmeV19TLB();
	virtual void bfmeV20TLB();
	virtual void bfmeV21TLB();
	virtual void bfmeV22TLB();
	virtual void bfmeV23TLB();
	virtual void bfmeV24TLB();
	virtual void bfmeV25TLB();
	virtual void bfmeV26TLB();
	virtual void bfmeV27TLB();
	virtual void bfmeV28TLB();
	virtual void bfmeV29TLB();
	virtual void bfmeV30TLB();
	virtual void bfmeV31TLB();
	virtual void bfmeV32TLB();
	virtual void bfmeV33TLB();
	virtual void bfmeV34TLB();
	virtual void bfmeV35TLB();
	virtual void bfmeV36TLB();
	virtual void bfmeV37TLB();
	virtual void bfmeV38TLB();
	virtual void bfmeV39TLB();
	virtual void bfmeV40TLB();
	virtual void bfmeV41TLB();
	virtual void bfmeV42TLB();
	virtual void bfmeV43TLB();
	virtual void bfmeV44TLB();
	virtual void bfmeV45TLB();
	virtual void bfmeV46TLB();
	virtual void bfmeV47TLB();
	virtual void bfmeV48TLB();
	virtual void bfmeV49TLB();
	virtual void bfmeV50TLB();
	virtual void bfmeV51TLB();
	virtual void bfmeV52TLB();
	virtual void bfmeV53TLB();
	virtual void bfmeV54TLB();
	virtual void bfmeV55TLB();
	virtual void bfmeV56TLB();
	virtual void bfmeV57TLB();
	virtual void bfmeV58TLB();
	virtual void bfmeV59TLB();
	virtual void bfmeV60TLB();
	virtual void bfmeV61TLB();
	virtual void bfmeV62TLB();
	virtual void bfmeV63TLB();
	virtual unsigned bfmeCountTLB(int a);
};

class BfmeOtherTLB
{
public:
	char m_bfmePad[0x17c];
	unsigned m_bfmeLimit;
};

class BfmeThingTLB
{
public:
	int bfmeGoTLB(int a);
	char m_bfmePad[4];
	BfmeOtherTLB *m_bfmeOther;
	char m_bfmePad2[0x18];
	BfmeSubTLB m_bfmeSub;
};

int BfmeThingTLB::bfmeGoTLB(int a)
{
	BfmeOtherTLB *o = m_bfmeOther;
	return m_bfmeSub.bfmeCountTLB(0) < o->m_bfmeLimit;
}
