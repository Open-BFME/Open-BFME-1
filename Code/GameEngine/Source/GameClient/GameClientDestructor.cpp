// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME GameClient destructor, retail 0x00596500 (860 bytes).

#include "../../../../Code/Libraries/Source/WWVegas/WWMath/coord2d.h"

extern void __cdecl operator delete(void *value) throw();

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() {}

private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc() {}
	virtual void xfer() {}
	virtual void loadPostProcess() {}
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class WindowManager
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
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30(void *value) = 0;
};

class CommandTranslator
{
public:
	virtual ~CommandTranslator();
};

extern WindowManager *g_theWindowManager;
extern WindowManager *TheWindowManager;
extern const void *GameClientVftable[];
extern const void *GameClientSecondaryVftable[];

extern void j_00025464();
extern void j_0001e277();
extern void j_00023a60();
extern void j_0002bed1();
extern void j_00032ba0();
extern void j_00016261();
extern void j_0003760a();
extern void j_00042e51();
extern void j_00011d42();
extern void j_000060d7();
extern void j_00049e72();
extern void j_0001bd1f();

typedef void (WindowManager::*RemoveNameMember)(const AsciiString *);

union RemoveNameCast
{
	void (*raw)();
	RemoveNameMember member;
};

static __forceinline void gameClientRemoveName(WindowManager *manager,
	void (*function)(), AsciiString *name)
{
	RemoveNameCast cast;
	cast.raw = function;
	(manager->*cast.member)(name);
}

class GameClientMember20
{
public:
	~GameClientMember20()
	{
		((void (__fastcall *)(GameClientMember20 *))j_00016261)(this);
	}

private:
	unsigned char m_pad[0x48];
};

class GameClientMember68
{
public:
	~GameClientMember68()
	{
		((void (__fastcall *)(GameClientMember68 *))j_0003760a)(this);
	}

private:
	unsigned char m_pad[0xec];
};

class GameClientMember154
{
public:
	~GameClientMember154()
	{
		((void (__fastcall *)(GameClientMember154 *))j_00042e51)(this);
	}

private:
	unsigned char m_pad[0x28];
};

class GameClientMember17c
{
public:
	~GameClientMember17c()
	{
		((void (__fastcall *)(GameClientMember17c *))j_00011d42)(this);
	}

private:
	unsigned char m_pad[0x13c];
};

class GameClientMember2b8
{
public:
	~GameClientMember2b8()
	{
		((void (__fastcall *)(GameClientMember2b8 *))j_000060d7)(this);
	}

private:
	unsigned char m_pad[0x1a8];
};

class GameClientMember460
{
public:
	~GameClientMember460()
	{
		((void (__fastcall *)(GameClientMember460 *))j_00049e72)(this);
	}

private:
	unsigned char m_pad[0x28];
};

class GameClientMember488
{
public:
	~GameClientMember488()
	{
		((void (__fastcall *)(GameClientMember488 *))j_0001bd1f)(this);
	}

private:
	unsigned char m_pad[0x3c];
};

class GameClientTailFields
{
public:
	__forceinline ~GameClientTailFields() throw()
	{
		void *value = m_4cc;
		::operator delete(value);
	}

private:
	unsigned char m_4c4;
	unsigned char m_4c5;
	unsigned char m_pad[2];
	unsigned int m_4c8;
	void *m_4cc;
	unsigned int m_4d0;
	unsigned char m_4d4;
	unsigned char m_tailPad[3];
};

class GameClientCoordArray
{
private:
	Coord2D m_data[4];
};

class GameClientList
{
public:
	~GameClientList()
	{
		((void (__fastcall *)(GameClientList *))j_00032ba0)(this);
	}

private:
	unsigned char m_pad[0x14];
};

class GameClient
	: public SubsystemInterface,
	  public Snapshot
{
public:
	virtual ~GameClient();

private:
	void *m_0c;
	CommandTranslator *m_10;
	unsigned char m_14[0x0c];
	GameClientMember20 m_member20;
	GameClientMember68 m_member68;
	GameClientMember154 m_member154;
	GameClientMember17c m_member17c;
	GameClientMember2b8 m_member2b8;
	GameClientMember460 m_member460;
	GameClientMember488 m_member488;
	GameClientTailFields m_tail;
	AsciiString m_name;
	Coord2D m_coords[4];
	GameClientList m_list;
};

GameClient::~GameClient()
{
	*(const void ***)this = GameClientVftable;
	*(const void ***)((char *)this + 8) = GameClientSecondaryVftable;

	if (g_theWindowManager)
	{
		{
			AsciiString name("AptPalantir::OnBttnObservePriorPlayer");
			gameClientRemoveName(g_theWindowManager, j_00025464, &name);
		}
		{
			AsciiString name("AptPalantir::OnBttnObserveNextPlayer");
			gameClientRemoveName(g_theWindowManager, j_00025464, &name);
		}
		{
			AsciiString name("AptPalantir::OnBttnMovie");
			gameClientRemoveName(g_theWindowManager, j_00025464, &name);
		}
		{
			AsciiString name("AptPalantir::OnBttnObjectives");
			gameClientRemoveName(g_theWindowManager, j_00025464, &name);
		}
		{
			AsciiString name("Palantir/ObserverStuff/NextPlayerBttn");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("Palantir/ObserverStuff/PriorPlayerBttn");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("Palantir/PalantirButtons/Buttons/Options");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("Palantir/PalantirButtons/Buttons/PlayerMagic/ButtonClip/");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("Palantir/PalantirButtons/Buttons/Objectives/ButtonClip/");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("Palantir/PalantirButtons/Buttons/PlayerPowerCap/");
			gameClientRemoveName(g_theWindowManager, j_0001e277, &name);
		}
		{
			AsciiString name("PalantirMinLOD");
			gameClientRemoveName(g_theWindowManager, j_00023a60, &name);
		}
	}

	((void (__fastcall *)())j_0002bed1)();

	if (m_10)
		delete m_10;

	m_10 = 0;
	TheWindowManager->slot30(m_0c);
	m_0c = 0;
}
