struct BfmeSubBRB
{
	unsigned char m_bfmeHead[4];
};

class AsciiString;
class BfmeUniqueIntegerStoreC8C0;

// ILT 0x0003D712 -> matched 0x0039CB60. The provider accepts the
// unique-index store and a level-name string reference.
class LightPointSystem
{
public:
	void rva0039CB60(BfmeUniqueIntegerStoreC8C0 *, const AsciiString &);
};

extern LightPointSystem *TheLightPointSystem;

class BfmeThingBRB
{
public:
	void bfmeGoBRB(void *what);
	unsigned char m_bfmeHead[0x274];
	BfmeSubBRB m_bfmeSub;
};

void BfmeThingBRB::bfmeGoBRB(void *what)
{
	if (TheLightPointSystem != 0)
		TheLightPointSystem->rva0039CB60((BfmeUniqueIntegerStoreC8C0 *)&m_bfmeSub,
			*(const AsciiString *)what);
}
