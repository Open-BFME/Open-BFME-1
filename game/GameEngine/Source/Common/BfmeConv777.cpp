class BfmeGlobDSV
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeRunDSV();
};

class PlayerList;
extern PlayerList *ThePlayerList;
static inline BfmeGlobDSV *thePlayersView() { return (BfmeGlobDSV *)ThePlayerList; }

extern void j_000313a9();

class BfmeSubDSV
{
};

struct BfmeThingDSV
{
	void bfmeGoDSV();
	unsigned char m_bfmeHead[0xc];
	BfmeSubDSV *m_bfmeSub;
};

void BfmeThingDSV::bfmeGoDSV()
{
	((void (__fastcall *)(BfmeSubDSV *))j_000313a9)(m_bfmeSub);
	thePlayersView()->bfmeRunDSV();
}
