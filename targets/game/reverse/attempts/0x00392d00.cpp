// ?d_00392d00@@YAXXZ
// partial score=0.24 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00392D00, 2353 bytes.  The matched caller is
// GameLogic::startNewGame at 0x00394260: it calls the body through ILT
// 0x000298E3 with the same GameLogic receiver.  The body reads
// GameLogic::m_loadScreen (+0x118), updates the progress arrays, and fills
// the multiplayer side/team records.  The compiler-extracted helper has no
// source-level declaration, so the address remains in the method name.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;
typedef bool Bool;

template <typename T> class StringBase
{
protected:
	struct Data
	{
		Int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void set(const T *text, Int length);
	void concat(const T *text, Int length);

	Data *m_data;
};

// Retail exposes the release implementation under this BFME-local spelling;
// AsciiString and the small string records below all have the same one-word
// layout.
class BFMERetailAsciiString : public StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	void __cdecl format(AsciiString format, ...);

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	Int length() const
	{
		return m_data ? m_data->m_length : 0;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString()
	{
		StringBase<WideChar>::releaseBuffer();
	}

	void set(const UnicodeString &other);

	const WideChar *str() const
	{
		return m_data ? m_data->m_text : (const WideChar *)0x0107388C;
	}

	Int length() const
	{
		return m_data ? m_data->m_length : 0;
	}
};

class RetailLayoutString
{
public:
	void set(const char *text, Int length);
	~RetailLayoutString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

private:
	void *m_data;
};

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);
	~GameSpyGroupRoom()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

private:
	void *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

class Dict
{
public:
	Dict(Int reserve = 0);
	~Dict();
	void clear();
	void setAsciiString(NameKeyType key, const AsciiString &value);
	void setUnicodeString(NameKeyType key, const UnicodeString &value);
	void setBool(NameKeyType key, Bool value);
	void setInt(NameKeyType key, Int value);

private:
	void *m_data;
};

class GameSlot
{
};

class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Int getLocalSlotNum() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual Bool slot13() = 0;
};

class LoadScreen
{
public:
	virtual void slot00() = 0;
	virtual void update(Int progress) = 0;
};

class BfmeSideCollection
{
};

class BfmeTeamCollection
{
};

class PlayerTemplateStore
{
};

class NameKeyGenerator
{
};

class PlayerTemplate
{
};

class MultiplayerSettings
{
};

class MultiplayerColorDefinition
{
};

class MapCache
{
};

class MapMetaData
{
};

extern GameInfo *TheGameInfo;

extern void j_00002ecd();
extern void j_00006f64();
extern void j_000074b9();
extern void j_00007efa();
extern void j_00009304();
extern void j_0000af1a();
extern void j_00010a0a();
extern void j_00014475();
extern void j_000153a2();
extern void j_00019880();
extern void j_0001c233();
extern void j_0001ca12();
extern void j_0001ec18();
extern void j_00021ec2();
extern void j_000279cb();
extern void j_00028187();
extern void j_0002af90();
extern void j_0002cd8b();
extern void j_0002f28e();
extern void j_00033f46();
extern void j_00037bd2();
extern void j_0003a20b();
extern void j_0003add7();
extern void j_00040593();
extern void j_00045dc7();
extern void j_000481e4();
extern void j_000887940();
extern void Rva0090F050();

// The external symbols below are only the ILT names printed by callees.py.
// Each adapter gives that thunk the source-level ABI witnessed at its callsite.
static GameSlot *gameGetSlot(GameInfo *game, Int index)
{
	union
	{
		void (*raw)();
		GameSlot *(GameInfo::*member)(Int);
	} call;
	call.raw = j_0001ec18;
	return (game->*call.member)(index);
}

static Bool slotIsOccupied(GameSlot *slot)
{
	union
	{
		void (*raw)();
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_00040593;
	return (slot->*call.member)();
}

static Bool slotIsHuman(GameSlot *slot)
{
	union
	{
		void (*raw)();
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_000279cb;
	return (slot->*call.member)();
}

static void dictConstruct(Dict *dict, Int reserve)
{
	union
	{
		void (*raw)();
		void (Dict::*member)(Int);
	} call;
	call.raw = j_00002ecd;
	(dict->*call.member)(reserve);
}

static void dictClear(Dict *dict)
{
	union
	{
		void (*raw)();
		void (Dict::*member)();
	} call;
	call.raw = j_00033f46;
	(dict->*call.member)();
}

static void dictDestroy(Dict *dict)
{
	union
	{
		void (*raw)();
		void (Dict::*member)();
	} call;
	call.raw = j_00014475;
	(dict->*call.member)();
}

static void dictSetAscii(Dict *dict, NameKeyType key,
	const AsciiString &value)
{
	union
	{
		void (*raw)();
		void (Dict::*member)(NameKeyType, const AsciiString &);
	} call;
	call.raw = j_0002af90;
	(dict->*call.member)(key, value);
}

static void dictSetUnicode(Dict *dict, NameKeyType key,
	const UnicodeString &value)
{
	union
	{
		void (*raw)();
		void (Dict::*member)(NameKeyType, const UnicodeString &);
	} call;
	call.raw = j_00028187;
	(dict->*call.member)(key, value);
}

static void dictSetBool(Dict *dict, NameKeyType key, Bool value)
{
	union
	{
		void (*raw)();
		void (Dict::*member)(NameKeyType, Bool);
	} call;
	call.raw = j_00006f64;
	(dict->*call.member)(key, value);
}

static void dictSetInt(Dict *dict, NameKeyType key, Int value)
{
	union
	{
		void (*raw)();
		void (Dict::*member)(NameKeyType, Int);
	} call;
	call.raw = j_00010a0a;
	(dict->*call.member)(key, value);
}

static NameKeyType staticKey(const StaticNameKey *key)
{
	union
	{
		void (*raw)();
		NameKeyType (StaticNameKey::*member)() const;
	} call;
	call.raw = j_00009304;
	return (key->*call.member)();
}

static UnicodeString slotName(GameSlot *slot)
{
	union
	{
		void (*raw)();
		UnicodeString (GameSlot::*member)() const;
	} call;
	call.raw = j_0003a20b;
	return (slot->*call.member)();
}

static void setSlotName(GameSlot *slot, const AsciiString &name)
{
	UnicodeString *destination =
		(UnicodeString *)((unsigned char *)slot + 0x2c);
	destination->set(*(const UnicodeString *)&name);
}

static PlayerTemplate *getPlayerTemplate(PlayerTemplateStore *store, Int index)
{
	union
	{
		void (*raw)();
		PlayerTemplate *(PlayerTemplateStore::*member)(Int) const;
	} call;
	call.raw = j_00037bd2;
	return (store->*call.member)(index);
}

static NameKeyType nameToKey(NameKeyGenerator *generator, const char *name)
{
	union
	{
		void (*raw)();
		NameKeyType (NameKeyGenerator::*member)(const char *);
	} call;
	call.raw = j_0003add7;
	return (generator->*call.member)(name);
}

static PlayerTemplate *findPlayerTemplate(PlayerTemplateStore *store,
	NameKeyType key)
{
	union
	{
		void (*raw)();
		PlayerTemplate *(PlayerTemplateStore::*member)(NameKeyType) const;
	} call;
	call.raw = j_0002cd8b;
	return (store->*call.member)(key);
}

static Bool isPlayerPreorder(GameInfo *game, Int index)
{
	union
	{
		void (*raw)();
		Bool (GameInfo::*member)(Int);
	} call;
	call.raw = j_000153a2;
	return (game->*call.member)(index);
}

static MultiplayerColorDefinition *getColor(MultiplayerSettings *settings,
	Int index)
{
	union
	{
		void (*raw)();
		MultiplayerColorDefinition *(MultiplayerSettings::*member)(Int);
	} call;
	call.raw = j_00021ec2;
	return (settings->*call.member)(index);
}

static AsciiString gameMap(GameInfo *game)
{
	union
	{
		void (*raw)();
		AsciiString (GameInfo::*member)() const;
	} call;
	call.raw = j_0002f28e;
	return (game->*call.member)();
}

static MapMetaData *findMap(MapCache *cache, AsciiString name)
{
	union
	{
		void (*raw)();
		MapMetaData *(MapCache::*member)(AsciiString);
	} call;
	call.raw = j_00019880;
	return (cache->*call.member)(name);
}

static void sideAdd(BfmeSideCollection *sides, void *value)
{
	union
	{
		void (*raw)();
		Int (BfmeSideCollection::*member)(void *);
	} call;
	call.raw = j_0001ca12;
	(sides->*call.member)(value);
}

static void teamAppend(BfmeTeamCollection *teams, const Dict *dict)
{
	union
	{
		void (*raw)();
		Int (BfmeTeamCollection::*member)(const Dict *);
	} call;
	call.raw = j_00045dc7;
	(teams->*call.member)(dict);
}

static void *sideFind(BfmeSideCollection *sides, AsciiString room,
	Int *index)
{
	union
	{
		void (*raw)();
		void *(BfmeSideCollection::*member)(AsciiString, Int *);
	} call;
	call.raw = j_000074b9;
	return (sides->*call.member)(room, index);
}

static unsigned int currentTime()
{
	union
	{
		void (*raw)();
		unsigned int (*function)();
	} call;
	call.raw = j_000481e4;
	return call.function();
}

static Bool equalUnicode(const UnicodeString &left,
	const UnicodeString &right)
{
	const WideChar *a = left.str();
	const WideChar *b = right.str();
	Int alen = left.length();
	Int blen = right.length();
	Int length = alen < blen ? alen : blen;
	for (Int i = 0; i < length; ++i)
	{
		if (a[i] != b[i])
			return false;
	}
	return alen == blen;
}

static const StaticNameKey *keyAt(unsigned int address)
{
	return (const StaticNameKey *)address;
}

class Rva00392D00GameLogic
{
public:
	void rva00392d00(Int progressBase, Int arg1, Int arg2);

private:
	unsigned char m_unmodelled00[0x118];
	LoadScreen *m_loadScreen;
	unsigned char m_progressComplete[8];
	UnsignedInt m_progressCompleteTimeout[8];
};

void Rva00392D00GameLogic::rva00392d00(Int progressBase, Int arg1, Int arg2)
{
	(void)arg1;
	(void)arg2;
	GameInfo *game = TheGameInfo;
	Bool hasCreepsSide = false;
	Int progress = progressBase;

	if (game)
	{
		for (Int i = 0; i < 8; ++i)
		{
			GameSlot *slot = gameGetSlot(game, i);
			if (!slot || !slotIsOccupied(slot))
				continue;
			if (game->slot13())
				continue;

			AsciiString playerName;
			if (*(Int *)((unsigned char *)slot + 0x14) < 0)
				playerName.format(AsciiString("Observer_%d"), i + 1);
			else
				playerName.format(AsciiString("Player_%d"),
					*(Int *)((unsigned char *)slot + 0x10) + 1);
			setSlotName(slot, playerName);
		}

		BFMERetailAsciiString creepsName("PlyrCreeps");
		AsciiString creepsRoom(
			*(const AsciiString *)&creepsName);
		Int sideIndex = 0;
		hasCreepsSide = sideFind(
			(BfmeSideCollection *)*(void **)0x012EF428,
			creepsRoom, &sideIndex) != 0;

		// The retail helper services the first-update subsystem before reading
		// each slot.  Its object and vtable slot are both witnessed directly.
		for (Int i = 0; i < 8; ++i)
		{
			void *firstUpdate = *(void **)0x0134FAA0;
			if (firstUpdate)
				(*(void (**)(void *))(*(void ***)firstUpdate + 0x14))(firstUpdate);
			Rva0090F050();

			GameSlot *slot = gameGetSlot(game, i);
			if (!slot || slotIsHuman(slot))
				continue;

			if (i >= 0 && i < 8)
			{
				m_progressComplete[i] = true;
				m_progressCompleteTimeout[i] = currentTime();
			}
			if (!slotIsOccupied(slot))
				continue;

			Dict player(0);
			AsciiString name;
			AsciiString slotNameAscii;
			slotNameAscii.concat(" ", 1);
			const AsciiString *slotText =
				(const AsciiString *)((unsigned char *)slot + 0x2c);
			slotNameAscii.concat(slotText->str(), slotText->length());
			dictSetAscii(&player, staticKey(keyAt(0x012A7918)),
				slotNameAscii);
			NameKeyType humanKey = staticKey(keyAt(0x012A7920));
			dictSetBool(&player, humanKey, slotIsHuman(slot));

			UnicodeString displayName = slotName(slot);
			dictSetUnicode(&player,
				staticKey(keyAt(0x012A7930)), displayName);

			PlayerTemplate *templateData = 0;
			Int templateIndex = *(Int *)((unsigned char *)slot + 0x14);
			if (templateIndex >= 0)
				templateData = getPlayerTemplate(
					(PlayerTemplateStore *)*(void **)0x012ED750,
					templateIndex);
			else
				templateData = findPlayerTemplate(
					(PlayerTemplateStore *)*(void **)0x012ED750,
					nameToKey((NameKeyGenerator *)*(void **)0x012ED600,
						"FactionObserver"));
			if (templateData)
			{
				AsciiString faction = gameMap(game);
				dictSetAscii(&player, staticKey(keyAt(0x012A7938)), faction);
			}
			if (isPlayerPreorder(game, i))
				dictSetBool(&player, staticKey(keyAt(0x012A7980)), true);

			AsciiString enemies;
			AsciiString allies;
			Int team = *(Int *)((unsigned char *)slot + 0x18);
			for (Int j = 0; j < 8; ++j)
			{
				void *firstUpdate = *(void **)0x0134FAA0;
				if (firstUpdate)
					(*(void (**)(void *))(*(void ***)firstUpdate + 0x14))(firstUpdate);
				Rva0090F050();

				GameSlot *teamSlot = gameGetSlot(game, j);
				if (i == j || !teamSlot || !slotIsOccupied(teamSlot))
					continue;
				AsciiString teamPlayer;
				teamPlayer.concat("player", 6);
				teamPlayer.format(AsciiString("player%d"), j);
				Bool enemy = team == -1 ||
					*(Int *)((unsigned char *)teamSlot + 0x18) != team;
				AsciiString &destination = enemy ? enemies : allies;
				if (!destination.isEmpty())
					destination.concat(" ", 1);
				destination.concat(teamPlayer.str(), teamPlayer.length());
			}
			if (hasCreepsSide)
			{
				AsciiString observerName;
				observerName.concat(" ", 1);
				observerName.concat(slotText->str(), slotText->length());
				dictSetAscii(&player, staticKey(keyAt(0x012A7948)),
					observerName);
				dictSetAscii(&player, staticKey(keyAt(0x012A7940)),
					enemies);
			}
			else
			{
				dictSetAscii(&player, staticKey(keyAt(0x012A7948)), enemies);
				dictSetAscii(&player, staticKey(keyAt(0x012A7940)), allies);
			}

			MultiplayerSettings *settings =
				(MultiplayerSettings *)*(void **)0x012ED5FC;
			MultiplayerColorDefinition *color = getColor(settings,
				*(Int *)((unsigned char *)slot + 0x0c));
			dictSetInt(&player, staticKey(keyAt(0x012A7958)),
				*(Int *)((unsigned char *)color + 0x10));
			dictSetInt(&player, staticKey(keyAt(0x012A7960)),
				*(Int *)((unsigned char *)color + 0x20));
			dictSetInt(&player, staticKey(keyAt(0x012A7968)),
				*(Int *)((unsigned char *)slot + 0x10));

			if (slotIsHuman(slot))
			{
				Int localIndex = game->getLocalSlotNum();
				GameSlot *localSlot = gameGetSlot(game, localIndex);
				UnicodeString localName = slotName(localSlot);
				UnicodeString currentName = slotName(slot);
				dictSetBool(&player, staticKey(keyAt(0x012A7978)),
					equalUnicode(currentName, localName));
			}

			Int mapIndex = *(Int *)((unsigned char *)game + 0x50);
			if (mapIndex >= 0)
				dictSetInt(&player, staticKey(keyAt(0x012A7950)), mapIndex);

			Int start = *(Int *)((unsigned char *)slot + 0x10);
			if (start >= 0 && start < 8)
			{
				AsciiString mapName = gameMap(game);
				MapMetaData *metadata = findMap(
					(MapCache *)*(void **)0x012F1594, mapName);
				if (metadata && !*((unsigned char *)metadata + 0x56))
				{
					AsciiString value("PlyrCreeps");
					dictSetAscii(&player,
						staticKey(keyAt(0x012A7988)), value);
				}
			}

			Bool hasSpecialMap = false;
			if (*(void **)0x012BC84C || *(void **)0x012BC850)
			{
				void *seed = *(void **)0x012BC84C;
				if (seed)
					hasSpecialMap = ((Bool (__cdecl *)(void *, void *,
						void *, void *))seed)(
						*(void **)0x012BC8D4, *(void **)0x012BC8D8,
						&mapIndex, &start) != false;
			}
			else
			{
				j_0001c233();
			}
			if (hasSpecialMap)
			{
				dictSetBool(&player, staticKey(keyAt(0x012A7928)), true);
				Int state = *(Int *)((unsigned char *)slot + 4) - 2;
				if (state >= 0 && state <= 2)
					dictSetInt(&player, staticKey(keyAt(0x012A7970)), state);
			}

			BFMERetailAsciiString sideName(" ");
			AsciiString sideRoom(
				*(const AsciiString *)&sideName);
			sideFind((BfmeSideCollection *)*(void **)0x012EF428,
				sideRoom, &sideIndex);
			sideAdd((BfmeSideCollection *)*(void **)0x012EF428,
				&player);

			RetailLayoutString teamName;
			teamName.set("team", 4);
			Dict teamDict(0);
			AsciiString teamText("team");
			teamText.concat(slotText->str(), slotText->length());
			dictClear(&teamDict);
			dictSetAscii(&teamDict, staticKey(keyAt(0x012A75B8)),
				teamText);
			dictSetAscii(&teamDict, staticKey(keyAt(0x012A75C0)),
				slotNameAscii);
			dictSetBool(&teamDict, staticKey(keyAt(0x012A75C8)), true);
			teamAppend((BfmeTeamCollection *)((unsigned char *)
				*(void **)0x012EF428 + 0x630), &teamDict);
			if (m_loadScreen)
				m_loadScreen->update(progress + i);
		}
	}

	if (hasCreepsSide)
	{
		BFMERetailAsciiString observer(" ");
		AsciiString observerRoom(
			*(const AsciiString *)&observer);
		Int observerIndex = 0;
		void *side = sideFind(
			(BfmeSideCollection *)*(void **)0x012EF428,
			observerRoom, &observerIndex);
		if (side)
		{
			AsciiString observerName;
			observerName.concat(" ", 1);
			Dict observerDict(0);
			dictSetAscii(&observerDict, staticKey(keyAt(0x012A7948)),
				observerName);
			dictSetAscii(&observerDict, staticKey(keyAt(0x012A7940)),
				*(const AsciiString *)((unsigned char *)side + 4));
		}
	}
}

Dict::Dict(Int reserve)
{
	dictConstruct(this, reserve);
}

Dict::~Dict()
{
	dictDestroy(this);
}

void Dict::clear()
{
	dictClear(this);
}

void Dict::setAsciiString(NameKeyType key, const AsciiString &value)
{
	dictSetAscii(this, key, value);
}

void Dict::setUnicodeString(NameKeyType key, const UnicodeString &value)
{
	dictSetUnicode(this, key, value);
}

void Dict::setBool(NameKeyType key, Bool value)
{
	dictSetBool(this, key, value);
}

void Dict::setInt(NameKeyType key, Int value)
{
	dictSetInt(this, key, value);
}
