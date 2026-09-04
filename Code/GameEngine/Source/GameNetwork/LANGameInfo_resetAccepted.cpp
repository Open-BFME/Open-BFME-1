// cl: /DNDEBUG /MD /EHsc

// LANGameInfo::resetAccepted, retail 0x0068D4D0 (98 bytes).
// The BFME LAN interface adds six virtual entries before the Zero Hour
// interface's utility calls; the slots below keep the three calls at +0x68,
// +0xB8, and +0xC0 on their retail entries.

typedef int Int;
typedef bool Bool;

class LANGameInfo;

class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot0a(void) = 0;
	virtual void slot0b(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot0d(void) = 0;
	virtual void slot0e(void) = 0;
	virtual void slot0f(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void ResetGameStartTimer(void);
	virtual void slot1b(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot1d(void) = 0;
	virtual void slot1e(void) = 0;
	virtual void slot1f(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot2a(void) = 0;
	virtual void slot2b(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot2d(void) = 0;
	virtual Bool AmIHost(void);
	virtual void slot2f(void) = 0;
	virtual LANGameInfo *GetMyGame(void);
};

extern LANAPI *TheLAN;
extern void LANEnableStartButton(Bool enabled);
extern int g_Va012F49D4;

class GameSlot
{
public:
	virtual void reset(void);
	void unAccept(void);

private:
	char m_body[0x64];
};

class LANGameSlot : public GameSlot
{
};

class GameInfo
{
public:
	virtual void base(void);

private:
	char m_body[0x54];
};

class LANGameInfo : public GameInfo
{
public:
	virtual void resetAccepted(void);

private:
	LANGameSlot m_LANSlot[8];
};

void LANGameInfo::resetAccepted(void)
{
	if (TheLAN)
	{
		TheLAN->ResetGameStartTimer();
		if (TheLAN->GetMyGame() == this && TheLAN->AmIHost() &&
			g_Va012F49D4 == 0)
			LANEnableStartButton(true);
	}

	for (Int i = 0; i < 8; ++i)
		m_LANSlot[i].unAccept();
}
