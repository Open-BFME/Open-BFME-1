// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

typedef int Int;
typedef int Bool;

class GameWindow;

template <typename T>
class StringBase
{
public:
	StringBase(const StringBase &other);

private:
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString()
	{
		reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
	}
};

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &other);
	~UnicodeString();

private:
	void *m_data;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
extern void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

struct BFMERetailMapTransferProgress
{
	unsigned char m_base[0x10];
	GameWindow *m_progressBars[8];
	GameWindow *m_playerNames[8];
	GameWindow *m_progressText[8];
	Int m_playerLookup[8];
	Int m_oldProgress[8];
};

extern void j_00021b7a();
extern void j_0002c16f();

class MapTransferLoadScreen
{
public:
	void processProgress(Int playerId, Int percentage, AsciiString stateStr);
};

void MapTransferLoadScreen::processProgress(Int playerId, Int percentage, AsciiString stateStr)
{
	BFMERetailMapTransferProgress *retail =
		reinterpret_cast<BFMERetailMapTransferProgress *>(this);

	if (retail->m_oldProgress[playerId] != percentage)
	{
		retail->m_oldProgress[playerId] = percentage;
		Int translatedSlot = retail->m_playerLookup[playerId];
		if (retail->m_progressBars[translatedSlot])
		{
			typedef void (*ProgressFn)(GameWindow *, Int);
			(reinterpret_cast<ProgressFn>(j_00021b7a))(
				retail->m_progressBars[translatedSlot], percentage);
		}
		if (retail->m_progressText[translatedSlot])
		{
			typedef void (*TextFn)(GameWindow *, UnicodeString);
			(reinterpret_cast<TextFn>(j_0002c16f))(
				retail->m_progressText[translatedSlot], TheGameText->fetch(stateStr));
		}
	}
}
