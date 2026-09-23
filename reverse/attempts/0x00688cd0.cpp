// ?OnHasMap@LANAPI@@UAEXPAUBfmeNetAddress@@_N@Z
// partial score=0.98 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../Code/Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(void)
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const wchar_t *text)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(text);
}

inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&other);
}

inline UnicodeString::~UnicodeString(void)
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct BfmeLANSlot
{
	BfmeNetAddress m_address;
	unsigned char m_rest[0x68 - sizeof(BfmeNetAddress)];
};

struct BfmeLANGameInfoSlots
{
	unsigned char m_beforeSlots[0x88];
	BfmeLANSlot m_slot[8];
};

class GameInfo
{
public:
	AsciiString getMap(void) const;
};

class MapMetaData;

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class GameSlot
{
public:
	void setMapAvailability(Bool available);
	UnicodeString getName(void) const;
};

struct Rva0068D3E0Slot;

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

class StringBaseWideAP
{
protected:
	StringBaseWideAP(void);
	StringBaseWideAP(const StringBaseWideAP &other);
	StringBaseWideAP(const unsigned short *text);
	~StringBaseWideAP(void);

	unsigned short *m_bfmeWideAP;
};

class UnicodeStringAP : public StringBaseWideAP
{
public:
	UnicodeStringAP(void) {}
	UnicodeStringAP(const UnicodeStringAP &other) : StringBaseWideAP(other) {}
	~UnicodeStringAP(void) {}

	const unsigned short *bfmeTextAP(void) const
	{
		return m_bfmeWideAP != 0 ? m_bfmeWideAP + 4
			: (const unsigned short *)0x0107388C;
	}
};

class BfmeEntryAP
{
public:
	UnicodeStringAP bfmeDisplayNameAP(void);

	unsigned char m_bfmePadAP[0x20];
	Int m_bfmeCountAP;
};

class GameTextInterface
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists) = 0;
};

class LANAPI
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void bfmeSlot29(void) = 0;
	virtual void bfmeSlot30(void) = 0;
	virtual void bfmeSlot31(void) = 0;
	virtual void bfmeSlot32(void) = 0;
	virtual void bfmeSlot33(void) = 0;
	virtual void OnHasMap(BfmeNetAddress *sender, Bool status);
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, Int chatType) = 0;
	virtual void bfmeSlot36(void) = 0;
	virtual void OnGameStartTimer(Int seconds) = 0;
	virtual void bfmeSlot38(void) = 0;
	virtual void bfmeSlot39(void) = 0;
	virtual void bfmeSlot40(void) = 0;
	virtual void bfmeSlot41(void) = 0;
	virtual void bfmeSlot42(void) = 0;
	virtual void bfmeSlot43(void) = 0;
	virtual void bfmeSlot44(void) = 0;
	virtual void bfmeSlot45(void) = 0;
	virtual Int AmIHost(void) = 0;
	virtual void bfmeSlot47(void) = 0;
	virtual void bfmeSlot48(void) = 0;
	virtual void bfmeSlot49(void) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;

	unsigned char m_beforeLobby[0x3D - 4];
	Bool m_inLobby;
	unsigned char m_beforeCurrentGame[2];
	GameInfo *m_currentGame;
};

struct BfmeObj935C
{
	unsigned char m_beforeRva00688CD0_26c[0x26C];
	unsigned char m_rva00688CD0_26c;
};

extern MapCache *TheMapCache;
extern GameTextInterface *TheGameText;
extern BfmeObj935C *g_bfme935GlobC;
extern Bool __cdecl WouldMapTransfer(GameInfo *game);
extern void __cdecl rva004CAF70(void);

inline const wchar_t *Rva00688CD0WideText(const UnicodeString &text)
{
	const void *data = *(void *const *)&text;
	return data != 0 ? (const wchar_t *)((const unsigned char *)data + 8)
		: (const wchar_t *)0x0107388C;
}

inline const char *Rva00688CD0AsciiText(const AsciiString &text)
{
	const void *data = *(void *const *)&text;
	return data != 0 ? (const char *)((const unsigned char *)data + 8)
		: (const char *)0x0107388B;
}

void LANAPI::OnHasMap(BfmeNetAddress *sender, Bool status)
{
	if ((unsigned char)AmIHost() == 0)
		return;

	UnsignedInt senderIP = sender->m_ip;
	BfmeLANGameInfoSlots *gameSlots =
		(BfmeLANGameInfoSlots *)m_currentGame;
	Int i;
	for (i = 0; i < 8; ++i)
	{
		BfmeNetAddress *slot = &gameSlots->m_slot[i].m_address;
		if (slot->m_ip == senderIP && slot->m_port == sender->m_port)
		{
			((GameSlot *)((Rva0068D3E0Arr *)m_currentGame)->at(i))
				->setMapAvailability(status);
			break;
		}
	}
	if (i == 8)
		return;

	UnicodeString mapDisplayName;
	const MapMetaData *mapData = TheMapCache->findMap(m_currentGame->getMap());
	Bool willTransfer = WouldMapTransfer(m_currentGame);
	if (mapData != 0)
	{
		mapDisplayName.format(UnicodeString(L"%ls"),
			((BfmeEntryAP *)mapData)->bfmeDisplayNameAP().bfmeTextAP());
	}
	else
	{
		mapDisplayName.format(UnicodeString(L"%hs"),
			Rva00688CD0AsciiText(m_currentGame->getMap()));
	}

	if (!status)
	{
		UnicodeString text;
		if (willTransfer)
		{
			text.format(TheGameText->fetch("GUI:PlayerNoMapWillTransfer", 0),
				Rva00688CD0WideText(
					((GameSlot *)((Rva0068D3E0Arr *)m_currentGame)->at(i))
						->getName()),
				Rva00688CD0WideText(mapDisplayName));
		}
		else
		{
			text.format(TheGameText->fetch("GUI:PlayerNoMap", 0),
				Rva00688CD0WideText(
					((GameSlot *)((Rva0068D3E0Arr *)m_currentGame)->at(i))
						->getName()),
				Rva00688CD0WideText(mapDisplayName));
		}
		OnChat(UnicodeString(L"SYSTEM"), _bfme_localAddress(), text, 2);
	}

	if (g_bfme935GlobC != 0)
		g_bfme935GlobC->m_rva00688CD0_26c = 1;
	else
		rva004CAF70();
}
