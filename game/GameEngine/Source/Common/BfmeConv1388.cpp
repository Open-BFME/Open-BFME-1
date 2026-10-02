// Open-BFME5 conversions.

// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies call
// (store the base vtable 0x01129358 into *this, then ret).  It is defined under
// this name in game/gen_small/fun_005.cpp, so the call site spells it through
// this neutral declaration rather than a member of the local message view.
class Gen_007e86c0
{
public:
	void m();
};

// Retail 0x007E8850 is the (char*, int) constructor of the real BfmeC994
// message class (see game/GameEngine/Source/Common/BfmeConv994.cpp), so the
// local view spells it that way instead of an invented init method.
class BfmeC994
{
public:
	BfmeC994(char *buf, int n);
	char m_bfmePad[0x34];
};

class BfmeAVJK
{
public:
	virtual void bfmeA00VJK() throw();
	virtual void bfmeA04VJK() throw();
	virtual void bfmeA08VJK() throw();
	virtual void bfmeA0CVJK() throw();
	virtual void bfmeA10VJK() throw();
	virtual void bfmeA14VJK() throw();
	virtual void bfmeA18VJK() throw();
	virtual void bfmeA1CVJK() throw();
	virtual void bfmeA20VJK() throw();
	virtual void bfmeA24VJK() throw();
	virtual void bfmeA28VJK() throw();
	virtual void bfmeA2CVJK() throw();
	virtual void bfmeA30VJK() throw();
	virtual void bfmeA34VJK() throw();
	virtual void bfmeA38VJK() throw();
	virtual void bfmeA3CVJK() throw();
	virtual void bfmeA40VJK() throw();
	virtual void bfmeA44VJK() throw();
	virtual void bfmeA48VJK() throw();
	virtual void bfmeA4CVJK() throw();
	virtual void bfmeA50VJK(class BfmeC994 *m) throw();
};

class BfmeBVJK
{
public:
	virtual void bfmeB00VJK() throw();
	virtual void bfmeB04VJK() throw();
	virtual void bfmeB08VJK(class BfmeC994 *m, int x, int y, int z) throw();
};

class BfmeThingVJK
{
public:
	void bfmeGoVJK(int unused);
	char m_bfmePad00[0x10];
	BfmeAVJK *m_bfme10;
	BfmeBVJK *m_bfme14;
	char m_bfmePad18[0x2c4];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJK::bfmeGoVJK(int unused)
{
	BfmeC994 msg(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA50VJK(&msg);
	m_bfme14->bfmeB08VJK(&msg, 0, 0, m_bfme6dc);
	reinterpret_cast< Gen_007e86c0 * >( &msg )->m();
}
