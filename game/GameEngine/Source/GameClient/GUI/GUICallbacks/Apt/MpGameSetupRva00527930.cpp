// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// MpGameSetup method at retail 0x00527930 (1516 bytes, ret 4 at +0x581 and
// +0x5E9).  Same receiver as the matched MpGameSetup::bfmeDispatchWindow
// (0x005253D0, called three times on this) and the Rva00526660Body owner
// validation; the literal set (LAN:NoMapSelected, GUI:PlayerNoMap,
// GUI:NeedHumanPlayers, LAN:TooManyPlayers, LAN:NeedMoreTeams,
// GUI:SandboxMode) is the Zero Hour StartPressed host validation, restructured
// for the BFME setup screen.  No selector string names the method, so the
// name keeps its address.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WCHAR;
typedef bool Bool;

enum { MAX_SLOTS = 8, PLAYERTEMPLATE_OBSERVER = -2 };

#include <set>
#include <string.h>

extern const char g_bfmeEmptyUnicode[];

template <typename T> struct BfmeSetupStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set(const StringBase<T> &other);

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase(void) { releaseBuffer(); }
	void releaseBuffer(void);

	BfmeSetupStringData<T> *m_data;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void)
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}
};

class UnicodeString : private StringBase<WCHAR>
{
public:
	UnicodeString(void) : StringBase<WCHAR>() {}
	UnicodeString(const WCHAR *text) : StringBase<WCHAR>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WCHAR>(other) {}
	~UnicodeString(void) {}
	const WCHAR *str(void) const
	{
		return m_data ? m_data->m_text : (const WCHAR *)g_bfmeEmptyUnicode;
	}
	void set(const UnicodeString &other) { StringBase<WCHAR>::set(other); }
	void format(UnicodeString format, ...);
};

class GameWindow;

class GameSlot
{
public:
	Bool isOccupied(void) const;
	Bool isHuman(void) const;
	Bool isOpen(void) const;
	UnicodeString getName(void) const;

	Bool hasMap(void) const { return m_hasMap; }
	void setAccept(void) { m_isAccepted = true; }
	Int getPlayerTemplate(void) const { return m_playerTemplate; }
	Int getTeamNumber(void) const { return m_teamNumber; }

private:
	void *m_vtable;
	UnsignedByte m_unmodelled04[4];
	Bool m_isAccepted;
	Bool m_hasMap;
	UnsignedByte m_unmodelled0A[10];
	Int m_playerTemplate;
	Int m_teamNumber;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
	AsciiString getMap(void) const;
};

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(void);

	UnsignedByte m_unmodelled00[0x20];
	Int m_numPlayers;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class GameTextInterface
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
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

// The BFME GlobalData witness used by the matched LAN StartPressed places
// netMinPlayers at +0xB0C.
class GlobalData
{
public:
	UnsignedByte m_unmodelled[0xB0C];
	Int m_netMinPlayers;
};

extern GlobalData *TheWritableGlobalData;
extern MapCache *TheMapCache;
extern GameTextInterface *TheGameText;
#define TheGlobalData TheWritableGlobalData

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// The BFME callsite passes the GameInfo object, not an AsciiString map name.
Bool WouldMapTransfer(GameInfo *game);

// Owner interface at MpGameSetup+4.  Slot 2 receives the text by reference
// (MpGameSetup::bfmeDispatchWindow forwards its argument here), slot 9 is the
// game-validity test and slot 12 the gate at entry; slot 13 takes two ints.
class Gen00525EE0Owner
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(const UnicodeString &text, Int color) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual void bfmeSlot4(void) = 0;
	virtual void bfmeSlot5(void) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual Bool bfmeContains(GameInfo *game) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual Bool bfmeShouldRestoreBackground(void) = 0;
	virtual void bfmeSlot13(Int a, Int b) = 0;
};

class Rva00525080SkirmishScreenState
{
public:
	void rva00525080(Int index, Int state);
};

class MpGameSetup
{
public:
	Bool rva00527930(Bool arg);
	void dispatchWindow(GameWindow *window);
	Bool rva005280A0(void);

private:
	void dispatchText(const UnicodeString &text)
	{
		dispatchWindow((GameWindow *)&text);
	}

	UnsignedByte m_unmodelled00[4];
	Gen00525EE0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	UnsignedByte m_unmodelled10[7];
	Bool m_pending;
	Bool m_backgroundVisible;
	UnsignedByte m_unmodelled19[3];
	UnsignedInt m_1C;
	Int m_20;
	UnsignedByte m_unmodelled24[0x120 - 0x24];
	UnsignedInt m_120;
	Bool m_isMultiplayer;
	UnsignedByte m_unmodelled125[3];
	Int m_128;
	Bool m_ready[MAX_SLOTS];
};

Bool MpGameSetup::rva00527930(Bool arg)
{
	if (!m_owner->bfmeShouldRestoreBackground())
		return false;

	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;
	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;
	if (!m_first)
		return false;

	Bool allHaveMap = true;
	m_first->getSlot(0)->setAccept();

	Int numUsers = 0;
	Int numHumans = 0;
	UnicodeString text;
	const MapMetaData *md = TheMapCache->findMap(m_first->getMap());
	UnicodeString mapDisplayName;
	Bool willTransfer = WouldMapTransfer(m_first);
	if (md)
	{
		mapDisplayName.format(UnicodeString(L"%ls"),
			const_cast<MapMetaData *>(md)->bfme_getDisplayName().str());

		Int i;
		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = m_first->getSlot(i);
			if (slot)
			{
				if (slot->isHuman() && !slot->hasMap() && !willTransfer)
				{
					UnicodeString msg;
					msg.format(TheGameText->fetch("GUI:PlayerNoMap"),
						slot->getName().str(), mapDisplayName.str());
					m_owner->bfmeSlot2(msg, 2);
					allHaveMap = false;
				}
				if (slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
				{
					if (slot->isHuman())
						numHumans++;
					numUsers++;
				}
			}
		}

		if ((m_120 & 0x10) && numHumans <= 1)
		{
			text.set(TheGameText->fetch("GUI:NeedHumanPlayers"));
			m_owner->bfmeSlot2(text, 0);
			return false;
		}

		if (arg)
		{
			m_128 = numHumans;
			memset(m_ready, 0, sizeof(m_ready));
			m_ready[0] = true;
		}

		if (!allHaveMap)
		{
			dispatchText(TheGameText->fetch("GUI:CouldNotTransferMap"));
			return false;
		}

		if (md->m_numPlayers < numUsers)
		{
			text.format(TheGameText->fetch("LAN:TooManyPlayers"), md->m_numPlayers);
			dispatchText(text);
			return false;
		}

		if (TheGlobalData->m_netMinPlayers && !numHumans)
		{
			text.set(TheGameText->fetch("GUI:NeedHumanPlayers"));
			dispatchText(text);
			return false;
		}

		if (numUsers < TheGlobalData->m_netMinPlayers)
		{
			text.set(TheGameText->fetch("GUI:NeedHumanPlayers"));
			dispatchText(text);
			return false;
		}

		Int numRandom = 0;
		std::set<Int> teams;
		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = m_first->getSlot(i);
			if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
			{
				if (slot->getTeamNumber() >= 0)
					teams.insert(slot->getTeamNumber());
				else
					++numRandom;
			}
		}
		if (numRandom + teams.size() < (UnsignedInt)TheGlobalData->m_netMinPlayers)
		{
			text.set(TheGameText->fetch("LAN:NeedMoreTeams"));
			dispatchText(text);
			return false;
		}

		if (numRandom + teams.size() < 2)
		{
			text.set(TheGameText->fetch("GUI:SandboxMode"));
			m_owner->bfmeSlot2(text, 0);
		}

		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = m_first->getSlot(i);
			if (slot && slot->isOpen())
				((Rva00525080SkirmishScreenState *)this)->rva00525080(i, 1);
		}

		if (arg)
		{
			m_20 = 6;
			m_1C = timeGetTime() + m_20 * 1000 - 1;
			m_pending = true;
			rva005280A0();
		}
		else
		{
			m_pending = false;
			m_owner->bfmeSlot13(1, numHumans);
			text.set(TheGameText->fetch("APT:ConnectingTitle"));
			m_owner->bfmeSlot2(text, 2);
		}
		return true;
	}
	else
	{
		text.format(TheGameText->fetch("LAN:NoMapSelected"));
		dispatchText(text);
		return false;
	}
}
