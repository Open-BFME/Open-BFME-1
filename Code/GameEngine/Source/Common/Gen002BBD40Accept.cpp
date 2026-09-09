// cl: /DNDEBUG /MD /EHsc

struct BfmeSeedPair
{
	BfmeSeedPair(void)
	{
	}

	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeUnused0(void);
	virtual bool bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual bool bfmeSkip(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);
	virtual void bfmeSeed(BfmeSeedPair *pair);
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeTakeAt4C(void *item);
	virtual void bfmeTakeAt50(void *item);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);
	virtual void bfmeSlot25(void);
	virtual void bfmeTakeAt68(void *item);
	virtual void bfmeTakeAt6C(void *item);
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);
	virtual void bfmeTakeAt78(void *item);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeTakeAt84(void *item);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);
};

void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);

class Gen_002BBD40;

class Gen_0014F150
{
    friend class Gen_002BBD40;

private:
	void bfmeAccept(BfmeSeedTarget *target);
};

template <typename T> class StringBase
{
friend class AsciiString;

protected:
	T *m_data;

private:
	StringBase(void) : m_data(0)
	{
	}

	StringBase(const StringBase<T> &other);
	~StringBase(void);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void)
		: StringBase<char>()
	{
	}

	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}

	~AsciiString(void)
	{
	}

	void *data(void) const
	{
		return m_data;
	}
};

typedef AsciiString GameSpyGroupRoom;

class UnicodeString
{
public:
	void set(const UnicodeString &other);
};

class TerrainLogic
{
public:
	virtual void bfmeSlot00(void);
	virtual void bfmeSlot01(void);
	virtual void bfmeSlot02(void);
	virtual void bfmeSlot03(void);
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot05(void);
	virtual void bfmeSlot06(void);
	virtual void bfmeSlot07(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot09(void);
	virtual void bfmeSlot0A(void);
	virtual void bfmeSlot0B(void);
	virtual void bfmeSlot0C(void);
	virtual void bfmeSlot0D(void);
	virtual void bfmeSlot0E(void);
	virtual void bfmeSlot0F(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot1A(void);
	virtual void bfmeSlot1B(void);
	virtual void bfmeSlot1C(void);
	virtual void bfmeSlot1D(void);
	virtual void bfmeSlot1E(void);
	virtual void bfmeSlot1F(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void *bfmeGetTerrainRoom(GameSpyGroupRoom room);
};

extern TerrainLogic *TheTerrainLogic;

class Gen_002BBD40
{
private:
	void bfmeAccept(BfmeSeedTarget *target);

	char m_bfmePad0[0x44];
	char m_bfmeItem0;
	char m_bfmePad1[0x3];
	char m_bfmeItem1;
	char m_bfmePad2[0x3];
	void *m_bfmeRoom;
};

void Gen_002BBD40::bfmeAccept(BfmeSeedTarget *target)
{
	if (target->bfmeSkip())
		return;

	((Gen_0014F150 *)this)->bfmeAccept(target);

	BfmeSeedPair pair;
	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 2;
	target->bfmeSeed(&pair);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
	bfmeHandOver_0000C9B4(target, (char *)this + 0x6C);
	target->bfmeTakeAt60((char *)this + 0x50);
	target->bfmeTakeAt60((char *)this + 0x5C);
	target->bfmeTakeAt8C((char *)this + 0x68);

	if (pair.m_bfmeSecond >= 2)
	{
		target->bfmeTakeAt24((char *)this + 0x70, 4);
		target->bfmeTakeAt74((char *)this + 0x74);
	}

	GameSpyGroupRoom room;
	if (m_bfmeRoom != 0)
	{
		((UnicodeString *)&room)->set(
			*(UnicodeString *)((char *)m_bfmeRoom + 8));
	}
	target->bfmeTakeAt68(&room);
	if (target->bfmeSlot0() && room.data() != 0
		&& *(unsigned short *)((char *)room.data() + 4) != 0)
	{
		m_bfmeRoom = TheTerrainLogic->bfmeGetTerrainRoom(room);
	}
}
