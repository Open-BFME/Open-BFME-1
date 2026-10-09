class BfmeThingCJ
{
public:
	int m_bfmeDataCJ;
};

class BfmeGuardCJ
{
public:
	BfmeGuardCJ(BfmeThingCJ *thing, void *value);
	~BfmeGuardCJ();

	unsigned char m_bfmeHeadCJ[0xc];
};

class BfmeOwnCM
{
public:
	virtual void bfmeSlot00CM(void);
	virtual void bfmeSlot01CM(void);
	virtual void bfmeSlot02CM(void);
	virtual void bfmeSlot03CM(void);
	virtual void bfmeSlot04CM(void);
	virtual void bfmeSlot05CM(void);
	virtual void bfmeSlot06CM(void);
	virtual void bfmeSlot07CM(void);
	virtual void bfmeSlot08CM(void);
	virtual void bfmeSlot09CM(void);
	virtual void bfmeSlot10CM(void);
	virtual void bfmeSlot11CM(void);
	virtual void bfmeSlot12CM(void);
	virtual void bfmeSlot13CM(void);
	virtual void bfmeSlot14CM(void);
	virtual void bfmeSlot15CM(void);
	virtual void bfmeSlot16CM(void);
	virtual void bfmeSlot17CM(void);
	virtual void bfmeSlot18CM(void);
	virtual void bfmeSlot19CM(void);
	virtual void bfmeSlot20CM(void);
	virtual void bfmeSlot21CM(void);
	virtual void bfmeSlot22CM(void);
	virtual char bfmeRunCM(void *first, void *second, void *third);

	char bfmeGuardedCM(void *first, void *second, void *third, void *fourth);

	unsigned char m_bfmeHeadCM[0x17084];
	BfmeThingCJ m_bfmeThingCM;
};

// The 12-byte guard storage is built and torn down through two already-matched
// ledger rows: retail 0x00339DA0 (BfmeConv1627.cpp) and 0x00339E20
// (BfmeConv1764.cpp).  The guard's destructor forwards inline to the matched
// BfmeOwnCD destructor so the automatic object (and its SEH frame) is kept
// while both calls resolve to the matched symbols.
//   ??0BfmeOwnVTY@@QAE@PAVBfmeStrVTY@@ABV1@@Z
//   ??1BfmeOwnCD@@UAE@XZ
class BfmeStrVTY
{
public:
	unsigned short *m_bfme00;
};

class BfmeOwnCD
{
public:
	virtual ~BfmeOwnCD(void);
};

class BfmeOwnVTY
{
public:
	BfmeOwnVTY(BfmeStrVTY *first, const BfmeStrVTY &second);
	__forceinline ~BfmeOwnVTY() { ((BfmeOwnCD *)this)->BfmeOwnCD::~BfmeOwnCD(); }

	int m_00;
	BfmeStrVTY m_bfme04;
	BfmeStrVTY *m_bfme08;
};

char BfmeOwnCM::bfmeGuardedCM(void *first, void *second, void *third, void *fourth)
{
	BfmeOwnVTY guard((BfmeStrVTY *)&m_bfmeThingCM, *(const BfmeStrVTY *)first);

	return bfmeRunCM(second, third, fourth);
}
