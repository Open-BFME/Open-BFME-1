// The shared body in BfmeConv1267.cpp declares this class locally, so repeat
// its identical declaration here to name the byte-verified callee without
// inventing a second class layout.
struct BfmeVec1267
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeA1267
{
public:
	BfmeVec1267 *bfmeGet1267();
	char m_bfmePad00[0x28];
	BfmeVec1267 m_bfme28;
	char m_bfmePad34[0x3c - 0x34];
	float m_bfme3c;
	float m_bfme40;
	BfmeVec1267 m_bfme44;
};

class BfmeSubDDA
{
public:
	unsigned char m_bfmeHead[0x39];
	bool m_bfmeFlag;
};

class BfmeThingDDA
{
public:
	int bfmeGoDDA();
	unsigned char m_bfmeHead[0x68];
	BfmeSubDDA *m_bfmeSub;
};

int BfmeThingDDA::bfmeGoDDA()
{
	BfmeSubDDA *s = m_bfmeSub;
	if (s != 0 && s->m_bfmeFlag)
		return (int)(unsigned long)((BfmeA1267 *)s)->bfmeGet1267();
	return 0;
}
