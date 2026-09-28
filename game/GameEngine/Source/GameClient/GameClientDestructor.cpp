// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME Rva00597FC0Client destructor, retail 0x00596500 (860 bytes).
// Rva00597FC0Client (constructor 0x00597FC0, vtable 0x0110C2D8) is the base
// AptPalantir derives from; it is not GameClient, whose destructor is
// 0x00431380 (identity_evidence/00431380-gameclient-vs-00597fc0-client.md).

#include "../../../../game/Libraries/Source/WWVegas/WWMath/coord2d.h"

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
extern const void *Rva00597FC0ClientVftable[];
extern const void *Rva00597FC0ClientSecondaryVftable[];

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

class Rva00597FC0ClientMember20
{
public:
	~Rva00597FC0ClientMember20()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember20 *))j_00016261)(this);
	}

private:
	unsigned char m_pad[0x48];
};

class Rva00597FC0ClientMember68
{
public:
	~Rva00597FC0ClientMember68()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember68 *))j_0003760a)(this);
	}

private:
	unsigned char m_pad[0xec];
};

class Rva00597FC0ClientMember154
{
public:
	~Rva00597FC0ClientMember154()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember154 *))j_00042e51)(this);
	}

private:
	unsigned char m_pad[0x28];
};

class Rva00597FC0ClientMember17c
{
public:
	~Rva00597FC0ClientMember17c()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember17c *))j_00011d42)(this);
	}

private:
	unsigned char m_pad[0x13c];
};

class Rva00597FC0ClientMember2b8
{
public:
	~Rva00597FC0ClientMember2b8()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember2b8 *))j_000060d7)(this);
	}

private:
	unsigned char m_pad[0x1a8];
};

class Rva00597FC0ClientMember460
{
public:
	~Rva00597FC0ClientMember460()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember460 *))j_00049e72)(this);
	}

private:
	unsigned char m_pad[0x28];
};

class Rva00597FC0ClientMember488
{
public:
	~Rva00597FC0ClientMember488()
	{
		((void (__fastcall *)(Rva00597FC0ClientMember488 *))j_0001bd1f)(this);
	}

private:
	unsigned char m_pad[0x3c];
};

class Rva00597FC0ClientTailFields
{
public:
	__forceinline ~Rva00597FC0ClientTailFields() throw()
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

class Rva00597FC0ClientCoordArray
{
private:
	Coord2D m_data[4];
};

class Rva00597FC0ClientList
{
public:
	~Rva00597FC0ClientList()
	{
		((void (__fastcall *)(Rva00597FC0ClientList *))j_00032ba0)(this);
	}

private:
	unsigned char m_pad[0x14];
};

class Rva00597FC0Client
	: public SubsystemInterface,
	  public Snapshot
{
public:
	virtual ~Rva00597FC0Client();

private:
	void *m_0c;
	CommandTranslator *m_10;
	unsigned char m_14[0x0c];
	Rva00597FC0ClientMember20 m_member20;
	Rva00597FC0ClientMember68 m_member68;
	Rva00597FC0ClientMember154 m_member154;
	Rva00597FC0ClientMember17c m_member17c;
	Rva00597FC0ClientMember2b8 m_member2b8;
	Rva00597FC0ClientMember460 m_member460;
	Rva00597FC0ClientMember488 m_member488;
	Rva00597FC0ClientTailFields m_tail;
	AsciiString m_name;
	Coord2D m_coords[4];
	Rva00597FC0ClientList m_list;
};

Rva00597FC0Client::~Rva00597FC0Client()
{
	*(const void ***)this = Rva00597FC0ClientVftable;
	*(const void ***)((char *)this + 8) = Rva00597FC0ClientSecondaryVftable;

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
