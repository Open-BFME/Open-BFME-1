class BfmeThingEUH
{
public:
	BfmeThingEUH();

	virtual void bfmeSlot00EUH();
	virtual void bfmeSlot01EUH();
	virtual void bfmeSlot02EUH();
	virtual void bfmeSlot03EUH();
	virtual void bfmeSlot04EUH();
	virtual void bfmeSlot05EUH();
	virtual void bfmeSlot06EUH();
	virtual void bfmeSlot07EUH();
	virtual void bfmeSlot08EUH();
	virtual void bfmeSlot09EUH();
	virtual void bfmeSlot10EUH();
	virtual void bfmeSlot11EUH();
	virtual void bfmeSlot12EUH();
	virtual void bfmeSlot13EUH();
	virtual void bfmeSlot14EUH();
	virtual void bfmeSlot15EUH();
	virtual void bfmeSlot16EUH();
	virtual void bfmeSlot17EUH();
	virtual void bfmeApplyEUH(unsigned char level);

	unsigned char m_bfmeBodyEUH[0x5c];
};

extern unsigned char g_bfmeLevelEUH;

BfmeThingEUH *bfmeMakeEUH()
{
	BfmeThingEUH *obj = new BfmeThingEUH;

	obj->bfmeApplyEUH(g_bfmeLevelEUH);

	return obj;
}
