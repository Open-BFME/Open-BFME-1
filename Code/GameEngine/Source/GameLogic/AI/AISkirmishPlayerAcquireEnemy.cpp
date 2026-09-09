// cl: /DNDEBUG /MD /EHsc
// Retail 0x00168ED0, 716 bytes: AISkirmishPlayer::acquireEnemy.
//
// The identity is anchored by the BFME "PlyrCreeps" filter, the retail
// "acquiring target enemy player: " literal, the AISkirmishPlayer field
// layout, and the matching reference AISkirmishPlayer::acquireEnemy source.
// The BFME body uses the one-argument hasAnyObjects query and filters the
// creep player before doing the reference enemy-distance selection.
// The derived table at VA 0x01096FB0 selects getAiEnemy at RVA 0x00169250;
// that body calls this implementation through ILT RVA 0x00004A70.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;

	Real width(void) const { return hi.x - lo.x; }
	Real height(void) const { return hi.y - lo.y; }
};

template <class T> class StringBase
{
	friend class AsciiString;

public:
	struct Data
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

private:
	StringBase(void);
	StringBase(const StringBase<T> &other);
	void concat(const T *text, Int length);
	void releaseBuffer(void);

	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) { m_data = 0; }
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void concat(const char *text, Int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	const char *str(void) const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

	Int getLength(void) const
	{
		return m_data ? m_data->length : 0;
	}

	void concat(const AsciiString &other)
	{
		((StringBase<char> *)this)->concat(other.str(), other.getLength());
	}

	Int bfmeCompare1294(const char *text) const;

private:
};

class Team;

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	Bool hasAnyUnits(void) const;
	Bool hasAnyObjects(Bool includeReserved) const;
	Bool hasAnyBuildFacility(void) const;
	Bool isSkirmishAIPlayer(void);
	Player *getCurrentEnemy(void);

	Team *getDefaultTeam(void) const
	{
		return *(Team **)((const char *)this + 0x230);
	}

	NameKeyType getPlayerNameKey(void) const
	{
		return *(const NameKeyType *)((const char *)this + 0x20);
	}

	char m_prefix[0x1c];
	AsciiString m_playerName;
};

class PlayerList
{
public:
	Int getPlayerCount(void) const
	{
		return *(const Int *)((const char *)this + 0x10);
	}

	Player *getNthPlayer(Int index);
};

class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

class AIPlayer
{
protected:
	char m_prefix[0x0c];
	Player *m_player;
	char m_beforeBaseCenter[0x24];
	Coord3D m_baseCenter;
	char m_afterBaseCenter[0x38];

	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);
};

class AISkirmishPlayer : public AIPlayer
{
protected:
	Int m_curFrontBaseDefense;
	Int m_curFlankBaseDefense;
	Real m_curFrontLeftDefenseAngle;
	Real m_curFrontRightDefenseAngle;
	Real m_curLeftFlankLeftDefenseAngle;
	Real m_curLeftFlankRightDefenseAngle;
	Real m_curRightFlankLeftDefenseAngle;
	Real m_curRightFlankRightDefenseAngle;
	UnsignedInt m_frameToCheckEnemy;
	Player *m_currentEnemy;

	void acquireEnemy(void);
};

class BfmeZeroRangeType;

extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ScriptEngine *TheScriptEngine;
extern const Real g_bfmeK1253;
extern const Real BfmeZeroRange;

extern void j_00015460(void);
extern void j_00015438(void);
extern void j_000362aa(void);

static __forceinline Bool bfmeIsSkirmishAIPlayer(Player *player)
{
	typedef Bool (Player::*Function)(void);
	union
	{
		void (*raw)(void);
		Function member;
	} call;
	call.raw = j_00015460;
	return (player->*call.member)();
}

static __forceinline Player *bfmeGetCurrentEnemy(Player *player)
{
	typedef Player *(Player::*Function)(void);
	union
	{
		void (*raw)(void);
		Function member;
	} call;
	call.raw = j_00015438;
	return (player->*call.member)();
}

static __forceinline void bfmeGetPlayerStructureBounds(Region2D *bounds,
	Int playerIndex)
{
	typedef void (*Function)(Region2D *, Int);
	union
	{
		void (*raw)(void);
		Function typed;
	} call;
	call.raw = j_000362aa;
	call.typed(bounds, playerIndex);
}

static const Real HUGE_DIST = 1000000.0f;

void AISkirmishPlayer::acquireEnemy(void)
{
	Player *bestEnemy = 0;
	Real bestDistanceSqr = HUGE_DIST * HUGE_DIST;

	if (m_currentEnemy) {
		Bool inBadShape = !m_currentEnemy->hasAnyUnits()
			|| !m_currentEnemy->hasAnyBuildFacility();
		if (!inBadShape) return;
	}

	Int i;
	for (i = 0; i < ThePlayerList->getPlayerCount(); i++) {
		Player *curPlayer = ThePlayerList->getNthPlayer(i);
		if (m_player->getRelationship(curPlayer->getDefaultTeam()) == ENEMIES) {
			if (curPlayer->hasAnyObjects(false) == false) continue;

			if (curPlayer->m_playerName.bfmeCompare1294(
				"PlyrCreeps") == 0)
				continue;

			Bool inBadShape = !curPlayer->hasAnyUnits()
				|| !curPlayer->hasAnyBuildFacility();

			Coord3D enemyPos = m_baseCenter;
			Region2D bounds;
			bfmeGetPlayerStructureBounds(&bounds, i);
			enemyPos.x = bounds.lo.x + bounds.width() / 2;
			enemyPos.y = bounds.lo.y + bounds.height() / 2;
			Real xDelta = enemyPos.x - m_baseCenter.x;
			Real yDelta = enemyPos.y - m_baseCenter.y;
			Real curDistSqr = xDelta * xDelta + yDelta * yDelta;

			if (inBadShape) {
				curDistSqr = HUGE_DIST * HUGE_DIST * 0.5f;
			}

			Int k;
			for (k = 0; k < ThePlayerList->getPlayerCount(); k++) {
				if (k == i) continue;
				Player *somePlayer = ThePlayerList->getNthPlayer(k);
				if (bfmeIsSkirmishAIPlayer(somePlayer)
					&& (bfmeGetCurrentEnemy(somePlayer) == curPlayer)) {
				curDistSqr += (500 * 500);
				}
				if (bfmeIsSkirmishAIPlayer(somePlayer)
					&& (bfmeGetCurrentEnemy(somePlayer) == m_player)) {
					curDistSqr -= (25 * 25);
					if (curDistSqr < BfmeZeroRange) curDistSqr = 0;
				}
			}

			if (curDistSqr < bestDistanceSqr) {
				bestEnemy = curPlayer;
				bestDistanceSqr = curDistSqr;
			}
		}
	}

	if (bestEnemy != 0 && bestEnemy != m_currentEnemy) {
		m_currentEnemy = bestEnemy;
		AsciiString msg = TheNameKeyGenerator->keyToName(
			m_player->getPlayerNameKey());
		msg.concat(" acquiring target enemy player: ", 32);
		msg.concat(TheNameKeyGenerator->keyToName(
			m_currentEnemy->getPlayerNameKey()));
		TheScriptEngine->AppendDebugMessage(msg, false);
	}
}
