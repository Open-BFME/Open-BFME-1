// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source

// Complete 117-byte GenerateGameOptionsString at RVA 0x0068DFF0.
// Local ABI declarations expose only the fields and virtual slot this body uses.
// The typed handleInActive caller confirms the hidden AsciiString return slot.

typedef int Int;
typedef bool Bool;

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}

	static AsciiString TheEmptyString;
};

class GameInfo
{
protected:
	char m_bfmeBase[0x0c];
};

class LANGameSlot
{
public:
	Bool isLocalPlayer(void) const;
};

class LANGameInfo : public GameInfo
{
public:
	LANGameSlot *getFirstLANSlot(void)
	{
		return &m_firstLANSlot;
	}

	Bool amIHost(void)
	{
		if (!m_inGame)
			return false;
		return getFirstLANSlot()->isLocalPlayer();
	}

private:
	Bool m_inGame;
	char m_bfmeBeforeSlots[0x58 - 0x0d];
	LANGameSlot m_firstLANSlot; // Only the address at +0x58 is used here.
};

// Slot names 0..47 are deliberately unspecified; GetMyGame is the verified
// slot at vtable +0xc0. These local declarations never instantiate LANAPI.
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
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual LANGameInfo *GetMyGame(void);
};

extern LANAPI *TheLAN;
// The typed formatter call encodes ILT 0xe70a -> body 0x621600 and passes
// includeSlots. Existing SkirmishPreferences and GameSpy callers confirm this ABI.
extern AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);

AsciiString GenerateGameOptionsString(void)
{
	if (!TheLAN->GetMyGame() || !TheLAN->GetMyGame()->amIHost())
		return AsciiString::TheEmptyString;

	return GameInfoToAsciiString(TheLAN->GetMyGame(), 1);
}
