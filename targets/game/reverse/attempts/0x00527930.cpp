// ?dup_00527930@@YAXXZ
// partial score=0.4 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_NEWALLOC

#define _STLP_USE_NEWALLOC 1
#include <set>
//
// Retail 0x00527930 is an anonymous Gen_00525EE0 map-preview update.  The
// receiver layout is established by the neighbouring Gen_00525EE0 methods;
// the method spelling remains address-derived until the UI callback is
// independently named.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;
typedef bool Bool;

template <typename T> class StringBase
{
    friend class UnicodeString;
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }
	void set(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}
	void format(UnicodeString format, ...);
	void set(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
	}
	void *data() const { return m_data; }
	const WideChar *str() const
	{
		return m_data ? (const WideChar *)((const unsigned char *)m_data + 8)
			: (const WideChar *)0x0107388c;
	}
};

class AsciiString
{
public:
	void *m_data;
	const char *str() const
	{
		return m_data ? (const char *)((const unsigned char *)m_data + 8)
			: (const char *)0x0107388b;
	}
};

class GameInfo;
class MapMetaData;
class MapCache;
class GameSlot;

class Gen_00525EE0Owner
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08(void *, Int) = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual Bool contains(GameInfo *) = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual Bool shouldRestoreBackground() = 0;
	virtual void setBackgroundVisible(Bool) = 0;
	virtual void slot38() = 0;
};

class GameInfo
{
};

class MapMetaData
{
};

class MapCache
{
};

class GameSlot
{
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
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *, Bool * = 0) = 0;
};

class Gen_00525EE0
{
public:
	void Rva00527930(Bool unused);
};

extern void j_00008c51();
extern void j_0000a6fa();
extern void j_00011c43();
extern void j_00019880();
extern void j_0001e957();
extern void j_0001ec18();
extern void j_00022ba6();
extern void j_000279cb();
extern void j_0002d4b6();
extern void j_0002f28e();
extern void j_00032fd3();
extern void j_000393fb();
extern void j_0003a20b();
extern void j_0003b61a();
extern void j_00040593();
extern "C" unsigned int __cdecl timeGetTime();

#define TheMapCache (*(MapCache **)0x012F1594)
#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheWritableGlobalData (*(unsigned char **)0x012ED5C8)
#define EmptyUnicode ((const WideChar *)0x0107388C)

static __forceinline Gen_00525EE0Owner *ownerOf(Gen_00525EE0 *self)
{
	return *(Gen_00525EE0Owner **)((unsigned char *)self + 4);
}

static __forceinline GameInfo *firstGame(Gen_00525EE0 *self)
{
	return *(GameInfo **)((unsigned char *)self + 8);
}

static __forceinline GameInfo *secondGame(Gen_00525EE0 *self)
{
	return *(GameInfo **)((unsigned char *)self + 0xc);
}

static __forceinline GameSlot *bfmeAt1079(GameInfo *game, Int index)
{
	union
	{
		void (*raw)(void);
		GameSlot *(GameInfo::*member)(Int);
	} call;
	call.raw = j_0001ec18;
	return (game->*call.member)(index);
}

static __forceinline Bool slotOccupied(const GameSlot *slot)
{
	union
	{
		void (*raw)(void);
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_00040593;
	return (slot->*call.member)();
}

static __forceinline Bool slotHuman(const GameSlot *slot)
{
	union
	{
		void (*raw)(void);
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_000279cb;
	return (slot->*call.member)();
}

static __forceinline Bool slotOpen(const GameSlot *slot)
{
	union
	{
		void (*raw)(void);
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_00011c43;
	return (slot->*call.member)();
}

static __forceinline Int slotPlayerTemplate(const GameSlot *slot)
{
	return *(const Int *)((const unsigned char *)slot + 0x14);
}

static __forceinline Int slotTeamNumber(const GameSlot *slot)
{
	return *(const Int *)((const unsigned char *)slot + 0x18);
}

static __forceinline Bool slotHasMap(const GameSlot *slot)
{
	return *((const unsigned char *)slot + 9) != 0;
}

static __forceinline AsciiString getMap(GameInfo *game)
{
	union
	{
		void (*raw)(void);
		AsciiString (GameInfo::*member)() const;
	} call;
	call.raw = j_0002f28e;
	return (game->*call.member)();
}

static __forceinline const MapMetaData *findMap(MapCache *cache,
	AsciiString name)
{
	union
	{
		void (*raw)(void);
		const MapMetaData *(MapCache::*member)(AsciiString);
	} call;
	call.raw = j_00019880;
	return (cache->*call.member)(name);
}

static __forceinline Bool wouldTransfer(GameInfo *game)
{
	union
	{
		void (*raw)(void);
		Bool (*function)(GameInfo *);
	} call;
	call.raw = j_000393fb;
	return call.function(game);
}

static __forceinline UnicodeString displayName(const MapMetaData *map)
{
	union
	{
		void (*raw)(void);
		UnicodeString (MapMetaData::*member)();
	} call;
	call.raw = j_0000a6fa;
	return (const_cast<MapMetaData *>(map)->*call.member)();
}

static __forceinline UnicodeString slotName(const GameSlot *slot)
{
	union
	{
		void (*raw)(void);
		UnicodeString (GameSlot::*member)() const;
	} call;
	call.raw = j_0003a20b;
	return (slot->*call.member)();
}

static __forceinline void dispatchWindow(Gen_00525EE0 *self, void *window)
{
	union
	{
		void (*raw)(void);
		void (Gen_00525EE0::*member)(void *);
	} call;
	call.raw = j_00022ba6;
	(self->*call.member)(window);
}

static __forceinline void closeOpenSlot(Gen_00525EE0 *self,
	Int index, Int notify)
{
	union
	{
		void (*raw)(void);
		void (Gen_00525EE0::*member)(Int, Int);
	} call;
	call.raw = j_0003b61a;
	(self->*call.member)(index, notify);
}

static __forceinline void refreshMapState(Gen_00525EE0 *self)
{
	union
	{
		void (*raw)(void);
		void (Gen_00525EE0::*member)();
	} call;
	call.raw = j_0001e957;
	(self->*call.member)();
}

static __forceinline Int mapPlayerCount(const MapMetaData *map)
{
	return *(const Int *)((const unsigned char *)map + 0x20);
}

static const WideChar *const RvaWideFormat =
	(const WideChar *)0x010ff4bc;
static const char *const RvaPlayerNoMap = (const char *)0x010ff4fc;
static const char *const RvaNeedPlayers = (const char *)0x010ff5c0;
static const char *const RvaNeedMoreTeams = (const char *)0x01106bb4;
static const char *const RvaSandbox = (const char *)0x01106b9c;
static const char *const RvaNotifiedStart = (const char *)0x01106b84;

// ?Rva00527930@Gen_00525EE0@@QAEX_N@Z
void Gen_00525EE0::Rva00527930(Bool unused)
{
	GameInfo *candidate;
	GameSlot *slot;
	Int index;
	Int numUsers;
	Int numHumans;
	Int numRandom;
	register Bool allHaveMap;

	if (!ownerOf(this)->shouldRestoreBackground())
		return;

	candidate = firstGame(this);
	if (candidate != 0 && !ownerOf(this)->contains(candidate))
		*(GameInfo **)((unsigned char *)this + 8) = 0;

	candidate = secondGame(this);
	if (candidate != 0 && !ownerOf(this)->contains(candidate))
		*(GameInfo **)((unsigned char *)this + 0xc) = 0;

	if (firstGame(this) == 0)
		return;

	allHaveMap = true;

	slot = bfmeAt1079(firstGame(this), 0);
	*((unsigned char *)slot + 8) = 1;

	numHumans = 0;
	numUsers = 0;
	numRandom = 0;

	AsciiString mapName = getMap(firstGame(this));
	const MapMetaData *map = findMap(TheMapCache, mapName);
	Bool willTransfer = wouldTransfer(firstGame(this));
	if (map == 0)
	{
		UnicodeString text;
		text.format(TheGameText->fetch(RvaNotifiedStart), mapName.str());
		dispatchWindow(this, &text);
		return;
	}

	UnicodeString display = displayName(map);
	UnicodeString format(RvaWideFormat);
	UnicodeString mapDisplayName;
	mapDisplayName.format(format, display.str());

	for (index = 0; index < 8; ++index)
	{
		slot = bfmeAt1079(firstGame(this), index);
		if (slot != 0 && slotHuman(slot) &&
			!slotHasMap(slot) && !willTransfer)
		{
			UnicodeString text;
			text.format(TheGameText->fetch(RvaPlayerNoMap),
				slotName(slot).str(), mapDisplayName.str());
			ownerOf(this)->slot08(&text, 2);
			allHaveMap = false;
		}

		if (slot != 0 && slotOccupied(slot) &&
			slotPlayerTemplate(slot) != -2 && slotHuman(slot))
		{
			++numHumans;
			++numUsers;
		}
	}

	if ((*((unsigned char *)this + 0x120) & 0x10) != 0 &&
		numHumans <= 1)
	{
		UnicodeString text;
		text.set(TheGameText->fetch(RvaNeedPlayers));
		ownerOf(this)->slot08(&text, 2);
		return;
	}

	if (mapPlayerCount(map) < numUsers)
	{
		UnicodeString text;
		text.format(TheGameText->fetch((const char *)0x010ff4c8),
			numUsers);
		dispatchWindow(this, &text);
		return;
	}

	if (TheWritableGlobalData != 0 &&
		*(Int *)(TheWritableGlobalData + 0xb0c) != 0 &&
		numHumans == 0)
	{
		UnicodeString text;
		text.set(TheGameText->fetch(RvaNeedPlayers));
		dispatchWindow(this, &text);
		return;
	}

	if (TheWritableGlobalData != 0 &&
		numUsers < *(Int *)(TheWritableGlobalData + 0xb0c))
	{
		UnicodeString text;
		text.set(TheGameText->fetch(RvaNeedPlayers));
		dispatchWindow(this, &text);
		return;
	}

	{
			std::set<Int> teams;
			for (index = 0; index < 8; ++index)
			{
				slot = bfmeAt1079(firstGame(this), index);
				if (slot == 0 || !slotOccupied(slot) ||
					slotPlayerTemplate(slot) == -2)
					continue;

				Int team = slotTeamNumber(slot);
				if (team >= 0)
					teams.insert(team);
				else
					++numRandom;
			}

			if (TheWritableGlobalData != 0 &&
				numRandom + (Int)teams.size() <
				*(Int *)(TheWritableGlobalData + 0xb0c))
			{
				UnicodeString text;
				text.set(TheGameText->fetch(RvaNeedMoreTeams));
				dispatchWindow(this, &text);
				return;
			}

			if (numRandom + (Int)teams.size() < 2)
			{
				UnicodeString text;
				text.set(TheGameText->fetch((const char *)0x01106b10));
				ownerOf(this)->slot08(&text, 0);
			}
		}

		for (index = 0; index < 8; ++index)
		{
			slot = bfmeAt1079(firstGame(this), index);
			if (slot != 0 && slotOpen(slot))
				closeOpenSlot(this, index, 1);
		}

		if (allHaveMap)
		{
			*((Int *)((unsigned char *)this + 0x20)) = 6;
			UnsignedInt now = timeGetTime();
			Int delay = *((Int *)((unsigned char *)this + 0x20));
			*((Int *)((unsigned char *)this + 0x1c)) = now + delay * 1000 - 1;
			*((unsigned char *)this + 0x17) = 1;
			refreshMapState(this);
		}
		else
		{
			*((unsigned char *)this + 0x17) = 0;
			ownerOf(this)->setBackgroundVisible(true);
			UnicodeString text;
			text.set(TheGameText->fetch(RvaSandbox));
			ownerOf(this)->slot08(&text, 0);
		}
}
