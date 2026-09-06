// ?bfmeSendZD@BfmeOwnZD@@QAEXXZ (identity unknown)
// partial score=0.75 date=2026-09-06
// Exact size (56) and exact structure. The whole diff is one register-role
// swap: retail keeps `this` in ecx for the whole body (the else branch pushes
// ecx as the copy-ctor source) and loads the id straight into eax; MSVC hoists
// `this` into eax (`mov eax,ecx`) because ecx is clobbered on the if path, then
// uses ecx for the temporary address. Every downstream difference follows from
// that. Tried if/else, early return with the guard both ways, a named local for
// the id, and /G7 /Ob0 /GF.
// Slots read off the bytes: GameSpyInfo slot 75 (+0x12c) takes the id, slot 81
// (+0x144) takes a 4-byte room BY VALUE; the room is at offset 0 of the caller
// so its address is `this`. Copy ctor is the string_base alias at 0x00887B60.
class BfmeRoomZD
{
public:
	BfmeRoomZD(const BfmeRoomZD &other);
	~BfmeRoomZD();

	int m_bfmeHandleZD;
};

class GameSpyInfo
{
public:
	virtual void bfmeSlot00ZD(void);
	virtual void bfmeSlot01ZD(void);
	virtual void bfmeSlot02ZD(void);
	virtual void bfmeSlot03ZD(void);
	virtual void bfmeSlot04ZD(void);
	virtual void bfmeSlot05ZD(void);
	virtual void bfmeSlot06ZD(void);
	virtual void bfmeSlot07ZD(void);
	virtual void bfmeSlot08ZD(void);
	virtual void bfmeSlot09ZD(void);
	virtual void bfmeSlot10ZD(void);
	virtual void bfmeSlot11ZD(void);
	virtual void bfmeSlot12ZD(void);
	virtual void bfmeSlot13ZD(void);
	virtual void bfmeSlot14ZD(void);
	virtual void bfmeSlot15ZD(void);
	virtual void bfmeSlot16ZD(void);
	virtual void bfmeSlot17ZD(void);
	virtual void bfmeSlot18ZD(void);
	virtual void bfmeSlot19ZD(void);
	virtual void bfmeSlot20ZD(void);
	virtual void bfmeSlot21ZD(void);
	virtual void bfmeSlot22ZD(void);
	virtual void bfmeSlot23ZD(void);
	virtual void bfmeSlot24ZD(void);
	virtual void bfmeSlot25ZD(void);
	virtual void bfmeSlot26ZD(void);
	virtual void bfmeSlot27ZD(void);
	virtual void bfmeSlot28ZD(void);
	virtual void bfmeSlot29ZD(void);
	virtual void bfmeSlot30ZD(void);
	virtual void bfmeSlot31ZD(void);
	virtual void bfmeSlot32ZD(void);
	virtual void bfmeSlot33ZD(void);
	virtual void bfmeSlot34ZD(void);
	virtual void bfmeSlot35ZD(void);
	virtual void bfmeSlot36ZD(void);
	virtual void bfmeSlot37ZD(void);
	virtual void bfmeSlot38ZD(void);
	virtual void bfmeSlot39ZD(void);
	virtual void bfmeSlot40ZD(void);
	virtual void bfmeSlot41ZD(void);
	virtual void bfmeSlot42ZD(void);
	virtual void bfmeSlot43ZD(void);
	virtual void bfmeSlot44ZD(void);
	virtual void bfmeSlot45ZD(void);
	virtual void bfmeSlot46ZD(void);
	virtual void bfmeSlot47ZD(void);
	virtual void bfmeSlot48ZD(void);
	virtual void bfmeSlot49ZD(void);
	virtual void bfmeSlot50ZD(void);
	virtual void bfmeSlot51ZD(void);
	virtual void bfmeSlot52ZD(void);
	virtual void bfmeSlot53ZD(void);
	virtual void bfmeSlot54ZD(void);
	virtual void bfmeSlot55ZD(void);
	virtual void bfmeSlot56ZD(void);
	virtual void bfmeSlot57ZD(void);
	virtual void bfmeSlot58ZD(void);
	virtual void bfmeSlot59ZD(void);
	virtual void bfmeSlot60ZD(void);
	virtual void bfmeSlot61ZD(void);
	virtual void bfmeSlot62ZD(void);
	virtual void bfmeSlot63ZD(void);
	virtual void bfmeSlot64ZD(void);
	virtual void bfmeSlot65ZD(void);
	virtual void bfmeSlot66ZD(void);
	virtual void bfmeSlot67ZD(void);
	virtual void bfmeSlot68ZD(void);
	virtual void bfmeSlot69ZD(void);
	virtual void bfmeSlot70ZD(void);
	virtual void bfmeSlot71ZD(void);
	virtual void bfmeSlot72ZD(void);
	virtual void bfmeSlot73ZD(void);
	virtual void bfmeSlot74ZD(void);
	virtual void bfmeSlotAZD(void *id);
	virtual void bfmeSlot76ZD(void);
	virtual void bfmeSlot77ZD(void);
	virtual void bfmeSlot78ZD(void);
	virtual void bfmeSlot79ZD(void);
	virtual void bfmeSlot80ZD(void);
	virtual void bfmeSlotBZD(class BfmeRoomZD room);
};

extern GameSpyInfo *TheGameSpyInfo;

class BfmeOwnZD
{
public:
	void bfmeSendZD(void);

	BfmeRoomZD m_bfmeRoomZD;
	unsigned char m_bfmeMidZD[0x10];
	void *m_bfmeIdZD;
};

void BfmeOwnZD::bfmeSendZD(void)
{
	if (m_bfmeIdZD == 0)
	{
		TheGameSpyInfo->bfmeSlotBZD(m_bfmeRoomZD);
		return;
	}

	TheGameSpyInfo->bfmeSlotAZD(m_bfmeIdZD);
}
