// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The constructor of the load screen GameLogic::getLoadScreen builds for the
// skirmish and multiplayer modes (GameLogicGetLoadScreen.cpp news 0xA4 bytes
// and calls ??0LoadScreen0051BF30@@QAE@I@Z with m_gameMode). Retail 0x0051BF30,
// 739 bytes. Its parked destructor (0x0051B7E0) installs the same vtable
// 0x01106070 and clears the singleton this constructor sets.
//
// Each piece is witnessed by a matched body:
//   base         Gen_00490420 (S3LinkedSingletonCtor.cpp), dtor 0x00490470
//   +0x18        AptMapPreview (ctor 0x00520670, initGadgets 0x00521AE0)
//   callbacks    WindowManager::bindShownWithArg (0x0046DBC0) with its
//                refcounted Rva0050F920FunctorHolder; the holder allocates
//                the wrapper (vtable 0x011060C0) from a by-value binding of
//                this object and one of its methods (0x0051B560, 0x0051B5F0),
//                the shape AptMapPreview::initGadgets (0x00521AE0) lands
//   layout       GameWindowManager::winCreateLayout (+0x6C) and
//                WindowLayout::runInit (slot 0), as in Shell_doPush.cpp
//   text         WindowManager::bfme_setAptText (0x0046CBF0) and
//                GameTextInterface::fetch(const char *, bool *) (+0x28)
// The class's own name is not recovered, so it keeps the address token of the
// ledger pin; so do its members and the two callback methods.

template<class T> struct StringData { int ref_count; unsigned short length, capacity; T text[1]; };
template<class T> class StringBase {
	friend class AsciiString;
	friend class UnicodeString;
private:
	StringData<T> *data;
	StringBase() : data(0) {}
	StringBase(const T *);
	StringBase(const StringBase &);
	~StringBase();
};
class AsciiString : private StringBase<char> {
public:
	AsciiString() {}
	AsciiString(const char *p) : StringBase<char>(p) {}
	AsciiString(const AsciiString &p) : StringBase<char>(p) {}
	~AsciiString() {}
	void __cdecl format(AsciiString, ...);
};
class UnicodeString : private StringBase<unsigned short> {
public:
	UnicodeString() {}
	UnicodeString(const unsigned short *p) : StringBase<unsigned short>(p) {}
	UnicodeString(const UnicodeString &p) : StringBase<unsigned short>(p) {}
	~UnicodeString() {}
};

class __single_inheritance FunctorTargetSingle
{
};
typedef void (FunctorTargetSingle::*FunctorMethodSingle)(void);

struct FunctorBindingSingle
{
	FunctorBindingSingle(FunctorMethodSingle method, FunctorTargetSingle *target)
		: m_target(target), m_method(method) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual ~FunctorWrapperHead();

	int m_refCount;
};

// Vtable 0x011060C0: the wrapper both registrations below allocate.
class FunctorWrapper011060C0 : public FunctorWrapperHead
{
public:
	FunctorWrapper011060C0(const FunctorBindingSingle &binding) : m_binding(binding) {}

	FunctorBindingSingle m_binding;
};

class Rva0050F920FunctorHolder
{
public:
	Rva0050F920FunctorHolder(FunctorBindingSingle binding)
	{
		m_ptr = new FunctorWrapper011060C0(binding);
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	Rva0050F920FunctorHolder(const Rva0050F920FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	~Rva0050F920FunctorHolder()
	{
		FunctorWrapperHead *p = m_ptr;
		if (p && (p->m_refCount = p->m_refCount - 1) <= 0)
			delete p;
	}

	FunctorWrapperHead *m_ptr;
};

class WindowManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(int);

	void bindShownWithArg(const AsciiString &name, void *argument, Rva0050F920FunctorHolder callback);
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

class WindowLayout
{
public:
	virtual void runInit(void *) = 0;

	AsciiString m_04;
	void *m_windowList;
};

class GameWindowManager
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString filename) = 0;
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface();
	virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual UnicodeString fetch(const char *label, bool *exists);
	virtual UnicodeString fetch(AsciiString label, bool *exists);
};

class GameSpyInfo;
class GameSpyStagingRoom
{
public:
	char m_pad[0x43C];
	bool m_43C;
};
struct Rva00579160Current;
class BfmeH1065;

extern WindowManager *g_rva012F19E8WindowManager;
extern GameWindowManager *TheWindowManager;
extern GameTextInterface *TheGameText;
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyStagingRoom *TheGameSpyGame;
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

int bfmeAptLevel00465CE0(BfmeH1065 *window);

class BfmeLinkedSingleton;
extern BfmeLinkedSingleton *TheBfmeSingletonHead;

class BfmeLinkedSingleton
{
public:
	virtual void bfmeSlot00(void);

	BfmeLinkedSingleton *m_bfmeNext;
};

class Gen_00490420 : public BfmeLinkedSingleton
{
public:
	Gen_00490420(void);
	virtual ~Gen_00490420();

protected:
	BfmeH1065 *m_bfme0008;
	bool m_bfme000C;
};

class AptMapPreview
{
public:
	AptMapPreview();
	~AptMapPreview();
	void initGadgets();

private:
	char m_data[0x40];
};

class LoadScreen0051BF30 : public Gen_00490420
{
public:
	LoadScreen0051BF30(unsigned int mode);
	virtual ~LoadScreen0051BF30();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();

	void Rva0051B560(void *argument, void *params, bool flag);
	void Rva0051B5F0(void *argument, void *params, bool flag);

private:
	WindowLayout *m_layout10;
	unsigned int m_mode14;
	AptMapPreview m_preview18;
	int m_58;
	int m_5C;
	int m_60[8];
	int m_80[8];
	bool m_A0;
};

extern LoadScreen0051BF30 *g_loadScreen012F49B0;

// ??0LoadScreen0051BF30@@QAE@I@Z
LoadScreen0051BF30::LoadScreen0051BF30(unsigned int mode)
	: m_layout10(0),
	  m_mode14(mode),
	  m_58(0),
	  m_5C(-1),
	  m_A0(false)
{
	g_loadScreen012F49B0 = this;
	for (int i = 0; i < 8; ++i)
	{
		m_60[i] = -1;
		m_80[i] = -1;
	}

	AsciiString name;
	AsciiString unused;
	for (int player = 0; player < 8; ++player)
	{
		name.format("GameLoading:PlayerColor:%d", player);
		g_rva012F19E8WindowManager->bindShownWithArg(name, (void *)player,
			Rva0050F920FunctorHolder(FunctorBindingSingle(
				reinterpret_cast<FunctorMethodSingle>(&LoadScreen0051BF30::Rva0051B560),
				(FunctorTargetSingle *)this)));
	}
	{
		AsciiString typeName("GameLoadingType");
		g_rva012F19E8WindowManager->bindShownWithArg(typeName, 0,
			Rva0050F920FunctorHolder(FunctorBindingSingle(
				reinterpret_cast<FunctorMethodSingle>(&LoadScreen0051BF30::Rva0051B5F0),
				(FunctorTargetSingle *)this)));
	}

	m_preview18.initGadgets();

	m_layout10 = TheWindowManager->winCreateLayout("LoadScreen.apt");
	m_layout10->runInit(0);
	if (m_layout10->m_windowList != 0)
	{
		m_bfme0008 = (BfmeH1065 *)m_layout10->m_windowList;
		m_5C = bfmeAptLevel00465CE0(m_bfme0008);
		g_rva012F19E8WindowManager->slot38(0);
		if (TheSkirmishGameInfo == 0 && TheGameSpyInfo == 0)
		{
			UnicodeString blank((const unsigned short *)L" ");
			g_rva012F19E8WindowManager->bfme_setAptText(AsciiString("GUI:Level"), blank);
		}
		if (TheGameSpyGame != 0 && TheGameSpyGame->m_43C)
		{
			AsciiString level("GUI:Level");
			g_rva012F19E8WindowManager->bfme_setAptText(level, TheGameText->fetch("GUI:Rank", 0));
		}
	}
}
