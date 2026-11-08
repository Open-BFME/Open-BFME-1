// Open-BFME5 conversions.

typedef int Int;

#include "../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeQ1098
{
	char m_bfmePad[0xbd];
	char m_bfmebd;
};

class Object;

// The row name of bfmeGo1098A keeps its invented return type; the object is a Player.
class BfmeR1098;

// TU-local layout view of Player. The `this`-only helpers are the rows at the ILTs retail
// calls: Player::isPlayerActive (0x000C9D10) and Player::iterateObjects (0x000CDCF0).
class Player
{
public:
	bool isPlayerActive(void) const;
	int iterateObjects(void (*callback)(Object *, void *), void *context) const;
	char m_bfmePad[4];
	BfmeQ1098 *m_playerTemplate;
};

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); this view carries the pinned rows
// getEachPlayerFromMask (0x000DF4A0) and getPlayersWithRelationship (0x000DF5A0).
class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
	unsigned short getPlayersWithRelationship(int playerIndex, int relationship, bool flag);
};

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

// Retail keeps the relationship mask's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int playersWithRelationship(int playerIndex, int relationship, bool flag)
{
	typedef int (PlayerList::*Raw)(int, int, bool);
	Raw raw = reinterpret_cast<Raw>(&PlayerList::getPlayersWithRelationship);
	return (ThePlayerList->*raw)(playerIndex, relationship, flag);
}

BfmeR1098 *bfmeGo1098A(short *h)
{
	while (*h) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)h);

		if (r && r->isPlayerActive() && r->m_playerTemplate && r->m_playerTemplate->m_bfmebd)
			return (BfmeR1098 *)r;
	}
	return 0;
}

class BfmeCtx1098
{
public:
	char m_bfmePad[0x0c];
	Coord3D m_bfmeCoord;
	char m_bfme18;
	char m_bfmePad1[3];
};

// Row at 0x0036BDD0 (?set@Rva0036BDD0@@QAEAAV1@PBURva0036BDD0Vec@@0@Z), reached through
// ILT 0x00021F21; the context block is its receiver.
struct Rva0036BDD0Vec;
class Rva0036BDD0
{
public:
	Rva0036BDD0 &set(const Rva0036BDD0Vec *first, const Rva0036BDD0Vec *second);
};

// The player-object walk callback is Rva00372210::callback (defined below); retail passes
// its ILT (0x00012D69, the defined row ?j_00012d69@@YAXXZ).
void __cdecl j_00012d69(void);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Overridable;
class PolygonTrigger;

class Rva00372210Vector
{
public:
	inline PolygonTrigger **begin() const
	{
		return m_begin;
	}
	inline int size() const
	{
		return (unsigned int)((char *)m_end - (char *)m_begin);
	}
private:
	PolygonTrigger **m_begin;
	PolygonTrigger **m_end;
};

class Object
{
public:
	char m_bfmeHead[4];
	Overridable *m_bfmeTemplate;
	char m_bfmePad08[0xe0];
protected:
	Module *findModule(NameKeyType key) const;
	friend class Rva00372210;
};

class Module
{
public:
	char m_bfmePad[0xe8];
	Rva00372210Vector m_triggers;
};

class PolygonTrigger
{
public:
	bool bfmeContainsPointAt0018FA20(Coord3D &point) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	char m_bfmeHead[4];
	Overridable *m_nextOverride;
	char m_bfmePad[0xcc];
	unsigned int m_bfmeFlags;
};

class Rva00372210
{
public:
	static int __cdecl callback(Object *object,
		BfmeCtx1098 *context);
};

// ?callback@Rva00372210@@SAHPAVObject@@PAVBfmeCtx1098@@@Z
int __cdecl Rva00372210::callback(Object *objectParameter,
	BfmeCtx1098 *context)
{
	Object *object = objectParameter;
	Module *module;
	const Overridable *objectTemplate = object->m_bfmeTemplate;
	if (objectTemplate == 0)
	{
		objectTemplate = 0;
		goto templateDone;
	}
	if (objectTemplate->m_nextOverride != 0)
		objectTemplate = objectTemplate->m_nextOverride->getFinalOverride();
templateDone:
	PolygonTrigger *trigger;
	if ((objectTemplate->m_bfmeFlags & 0x00800000) == 0)
		return 1;

	static NameKeyType key =
		TheNameKeyGenerator->nameToKey("CastleBehavior");
	module = object->findModule(key);
	if (module == 0)
		return 1;
	if ((module->m_triggers.size() & ~3) <= 0)
		return 1;
	BfmeCtx1098 *ctx = context;
	Int index = 0;

	do
	{
		if (index >= (unsigned int)(module->m_triggers.size() >> 2))
			trigger = 0;
		else
			trigger = *(module->m_triggers.begin() + index);
		if (trigger->bfmeContainsPointAt0018FA20(
			*(Coord3D *)context))
			return 0;

		if (!ctx->m_bfme18 &&
			trigger->bfmeContainsPointAt0018FA20(
			ctx->m_bfmeCoord))
			ctx->m_bfme18 = 1;
		++index;
	} while (index < module->m_triggers.size() >> 2);

	return 1;
}

char bfmeGo1098B(int a, int b, int c)
{
	BfmeCtx1098 ctx;
	int h;

	h = playersWithRelationship(a, 3, false);
	((Rva0036BDD0 *)&ctx)->set((const Rva0036BDD0Vec *)b, (const Rva0036BDD0Vec *)c);
	while ((short)h) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&h);

		if (r && !r->iterateObjects((void (*)(Object *, void *))j_00012d69, &ctx))
			return 0;
	}
	return ctx.m_bfme18;
}
