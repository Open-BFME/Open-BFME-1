// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

typedef int Int;
typedef int NameKeyType;

template <typename T> struct StringInlineData
{
    int m_refCount;
    int m_length;
    T m_text[1];
};

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void format(AsciiString format, ...);
	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name)
	{
		return nameToKey(name.str());
	}
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;
class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
};

extern GameWindowManager *TheWindowManager;

static NameKeyType staticTextPlayerID[8];
static NameKeyType staticTextSideID[8];
static NameKeyType staticTextTeamID[8];
static NameKeyType staticTextStatusID[8];
static NameKeyType buttonMuteID[8];
static NameKeyType buttonUnMuteID[8];
static GameWindow *staticTextPlayer[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static GameWindow *staticTextSide[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static GameWindow *staticTextTeam[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static GameWindow *staticTextStatus[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static GameWindow *buttonMute[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static GameWindow *buttonUnMute[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static Int slotNumInRow[8];
static GameWindow *theWindow = 0;

// ?grabWindowPointers@@YAXXZ
void grabWindowPointers(void)
{
	for (Int i = 0; i < 8; ++i)
	{
		AsciiString temp;
		temp.format(AsciiString("Diplomacy.wnd:StaticTextPlayer%d"), i);
		staticTextPlayerID[i] = TheNameKeyGenerator->nameToKey(temp);
		temp.format(AsciiString("Diplomacy.wnd:StaticTextSide%d"), i);
		staticTextSideID[i] = TheNameKeyGenerator->nameToKey(temp);
		temp.format(AsciiString("Diplomacy.wnd:StaticTextTeam%d"), i);
		staticTextTeamID[i] = TheNameKeyGenerator->nameToKey(temp);
		temp.format(AsciiString("Diplomacy.wnd:StaticTextStatus%d"), i);
		staticTextStatusID[i] = TheNameKeyGenerator->nameToKey(temp);
		temp.format(AsciiString("Diplomacy.wnd:ButtonMute%d"), i);
		buttonMuteID[i] = TheNameKeyGenerator->nameToKey(temp);
		temp.format(AsciiString("Diplomacy.wnd:ButtonUnMute%d"), i);
		buttonUnMuteID[i] = TheNameKeyGenerator->nameToKey(temp);

		staticTextPlayer[i] = TheWindowManager->winGetWindowFromId(theWindow, staticTextPlayerID[i]);
		staticTextSide[i] = TheWindowManager->winGetWindowFromId(theWindow, staticTextSideID[i]);
		staticTextTeam[i] = TheWindowManager->winGetWindowFromId(theWindow, staticTextTeamID[i]);
		staticTextStatus[i] = TheWindowManager->winGetWindowFromId(theWindow, staticTextStatusID[i]);
		buttonMute[i] = TheWindowManager->winGetWindowFromId(theWindow, buttonMuteID[i]);
		buttonUnMute[i] = TheWindowManager->winGetWindowFromId(theWindow, buttonUnMuteID[i]);

		slotNumInRow[i] = -1;
	}
}
