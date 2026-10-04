// ?computeSuperweaponTarget@AISkirmishPlayer@@UAE_NPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z
// AISkirmishPlayer identity: vtable 0x01096FB0 slot 4; constructor 0x00168660.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <math.h>
typedef bool Bool;
typedef int Int;
typedef float Real;
template <typename T> struct StringInlineData;
template <typename T> class StringBase
{
	friend class AsciiString;
public:
	Int compare(const T *text) const throw();
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
	Int compare(const char *text) const
	{
		return StringBase<char>::compare(text);
	}
	void format(AsciiString fmt, ...);
};


extern Int GetGameLogicRandomValue(int minimum, int maximum, char *file, int line);
extern void j_0003f4f9();
extern void j_000362aa();

struct Coord2D
{
	Real x;
	Real y;

	Real length() const { return (Real)sqrt(x * x + y * y); }

	void normalize()
	{
		Real len = length();
		if (len != 0)
		{
			x /= len;
			y /= len;
		}
	}
};

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

class Overridable
{
public:
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	AsciiString getName() const;
};

class Player
{
public:
	unsigned char m_pad000[0x224];
	Int m_mpStartIndex;
	Int getMpStartIndex() const { return m_mpStartIndex; }
};

class AIPlayer
{
public:
	virtual void _ai_00() = 0;
	virtual void _ai_01() = 0;
	virtual void _ai_02() = 0;
	virtual void _ai_03() = 0;
	virtual Bool computeSuperweaponTarget(const SpecialPowerTemplate *power,
		Coord3D *retPos, Int playerNdx, Real weaponRadius);
};

// Retail's AIPlayer::getPlayerStructureBounds is reached through the
// incremental-link thunk at 0x000362AA; both static call sites below go there
// directly instead of through a linker alternate-name alias.
typedef void (__cdecl *PlayerStructureBounds)(Region2D *, Int);

class AISkirmishPlayer : public AIPlayer
{
public:
	virtual Bool computeSuperweaponTarget(const SpecialPowerTemplate *power,
		Coord3D *retPos, Int playerNdx, Real weaponRadius);

protected:
	Int getMyEnemyPlayerIndex();

private:
	unsigned char m_pad004[8];
	Player *m_player;
	unsigned char m_pad010[0x24];
	Coord3D m_baseCenter;
	unsigned char m_pad040[4];
	Real m_baseRadius;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	void *m_vtable;
	Int m_id;
	void *m_name;
	Coord3D m_location;
};

class TerrainLogic
{
public:
	virtual void _tl_00() = 0;
	virtual void _tl_01() = 0;
	virtual void _tl_02() = 0;
	virtual void _tl_03() = 0;
	virtual void _tl_04() = 0;
	virtual void _tl_05() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) = 0;
	virtual void _tl_07() = 0;
	virtual void _tl_08() = 0;
	virtual void _tl_09() = 0;
	virtual void _tl_10() = 0;
	virtual void _tl_11() = 0;
	virtual void _tl_12() = 0;
	virtual void _tl_13() = 0;
	virtual void _tl_14() = 0;
	virtual void _tl_15() = 0;
	virtual void _tl_16() = 0;
	virtual void _tl_17() = 0;
	virtual void _tl_18() = 0;
	virtual void _tl_19() = 0;
	virtual void _tl_20() = 0;
	virtual void _tl_21() = 0;
	virtual void _tl_22() = 0;
	virtual void _tl_23() = 0;
	virtual void _tl_24() = 0;
	virtual void _tl_25() = 0;
	virtual const void *_tl_26(AsciiString) = 0;
	virtual void _tl_27() = 0;
	virtual void _tl_28() = 0;
	virtual void _tl_29() = 0;
	virtual Waypoint *getFirstWaypoint() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
	virtual Waypoint *getWaypointByID(Int id) = 0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *position,
		AsciiString label) = 0;
};

extern TerrainLogic *TheTerrainLogic;


Bool AISkirmishPlayer::computeSuperweaponTarget(const SpecialPowerTemplate *power,
	Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	Region2D bounds;
	union { void (*raw)(); PlayerStructureBounds route; } playerBounds = { j_000362aa };
	playerBounds.route(&bounds, playerNdx);

	if (power->getName().compare("SuperweaponClusterMines") == 0)
	{
		AsciiString pathLabel;
		Int mode = GetGameLogicRandomValue(0, 2,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AISkirmishPlayer.cpp", 0x46D);
		if (mode == 1)
		{
			pathLabel.format(AsciiString("%s%d"),
				"Flank", m_player->getMpStartIndex() + 1);
		}
		else if (mode == 2)
		{
			pathLabel.format(AsciiString("%s%d"),
				"Backdoor", m_player->getMpStartIndex() + 1);
		}
		else
		{
			pathLabel.format(AsciiString("%s%d"),
				"Center", m_player->getMpStartIndex() + 1);
		}
		Coord3D goalPos = m_baseCenter;
		Waypoint *waypoint = TheTerrainLogic->getClosestWaypointOnPath(
			&goalPos, pathLabel);
		if (waypoint)
		{
			goalPos = *waypoint->getLocation();
		}
		else
		{
			Region2D bounds;
			union { void (*raw)(); PlayerStructureBounds route; } enemyBounds = { j_000362aa };
			enemyBounds.route(&bounds, getMyEnemyPlayerIndex());
			goalPos.x = bounds.lo.x + bounds.width() / 2.0f;
			goalPos.y = bounds.lo.y + bounds.height() / 2.0f;
		}

		Coord2D offset;
		offset.x = goalPos.x - m_baseCenter.x;
		offset.y = goalPos.y - m_baseCenter.y;
		offset.normalize();
		offset.x *= m_baseRadius;
		offset.y *= m_baseRadius;
		*retPos = m_baseCenter;
		retPos->x += offset.x;
		retPos->y += offset.y;
		retPos->z = TheTerrainLogic->getGroundHeight(retPos->x, retPos->y);
	}
	else
	{
		typedef Bool (AIPlayer::*Fallback)(const SpecialPowerTemplate *,
			Coord3D *, Int, Real);
		union { void (*raw)(); Fallback member; } call;
		call.raw = j_0003f4f9;
		return (this->*call.member)(power, retPos, playerNdx, weaponRadius);
	}
}
