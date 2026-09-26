// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct StringInlineData
{
	Int m_refCount;
	Int m_length;
	T m_text[1];
};

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
	Int compare(const char *text) const { return StringBase<char>::compare(text); }
	void format(AsciiString format, ...);
};

struct Coord2D
{
	Real x, y;
	Real length() const { return (Real)sqrt(x * x + y * y); }
	void normalize()
	{
		Real len = length();
		if (len != 0) {
			x /= len;
			y /= len;
		}
	}
};

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real x, y, z;
};

struct Region2D
{
	Coord2D lo, hi;
	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

class Player
{
public:
	Int getMpStartIndex() const { return m_mpStartIndex; }
private:
	char m_unmodelled000[0x224];
	Int m_mpStartIndex;
};

class SpecialPowerTemplate
{
public:
	AsciiString getName() const;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
private:
	char m_unmodelled000[0x0c];
	Coord3D m_location;
};

#define TERRAIN_SLOT(N) virtual void slot##N() = 0;
class TerrainLogic
{
public:
	TERRAIN_SLOT(00) TERRAIN_SLOT(01) TERRAIN_SLOT(02)
	TERRAIN_SLOT(03) TERRAIN_SLOT(04) TERRAIN_SLOT(05)
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const = 0;
	TERRAIN_SLOT(07) TERRAIN_SLOT(08) TERRAIN_SLOT(09)
	TERRAIN_SLOT(10) TERRAIN_SLOT(11) TERRAIN_SLOT(12)
	TERRAIN_SLOT(13) TERRAIN_SLOT(14) TERRAIN_SLOT(15)
	TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18)
	TERRAIN_SLOT(19) TERRAIN_SLOT(20) TERRAIN_SLOT(21)
	TERRAIN_SLOT(22) TERRAIN_SLOT(23) TERRAIN_SLOT(24)
	TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27)
	TERRAIN_SLOT(28) TERRAIN_SLOT(29) TERRAIN_SLOT(30)
	TERRAIN_SLOT(31) TERRAIN_SLOT(32)
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos, AsciiString label) = 0;
};
#undef TERRAIN_SLOT

extern TerrainLogic *TheTerrainLogic;
extern Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
extern void j_0003f4f9();

class AIPlayer
{
public:
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius);
	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);
protected:
	char m_unmodelled004[0x08];
	Player *m_player;
	char m_unmodelled010[0x24];
	Coord3D m_baseCenter;
	char m_unmodelled040[0x04];
	Real m_baseRadius;
};

class AISkirmishPlayer : public AIPlayer
{
public:
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius);
protected:
	Int getMyEnemyPlayerIndex();
};

// ?computeSuperweaponTarget@AISkirmishPlayer@@UAEXPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z
void AISkirmishPlayer::computeSuperweaponTarget(const SpecialPowerTemplate *power, Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	Region2D bounds;
	getPlayerStructureBounds(&bounds, playerNdx);
	if (power->getName().compare("SuperweaponClusterMines") == 0) {
		AsciiString pathLabel;
		Int mode = GetGameLogicRandomValue(0, 2, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AISkirmishPlayer.cpp", 1133);
		if (mode == 1)
			pathLabel.format(AsciiString("%s%d"), "Flank", m_player->getMpStartIndex() + 1);
		else if (mode == 2)
			pathLabel.format(AsciiString("%s%d"), "Backdoor", m_player->getMpStartIndex() + 1);
		else
			pathLabel.format(AsciiString("%s%d"), "Center", m_player->getMpStartIndex() + 1);

		Coord3D goalPos = m_baseCenter;
		Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(&goalPos, pathLabel);
		if (way) {
			goalPos = *way->getLocation();
		} else {
			Region2D enemyBounds;
			getPlayerStructureBounds(&enemyBounds, getMyEnemyPlayerIndex());
			goalPos.x = enemyBounds.lo.x + enemyBounds.width() / 2;
			goalPos.y = enemyBounds.lo.y + enemyBounds.height() / 2;
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
		return;
	}
	typedef void (AIPlayer::*Fallback)(const SpecialPowerTemplate *, Coord3D *, Int, Real);
	union { void (*raw)(); Fallback member; } call;
	call.raw = j_0003f4f9;
	(this->*call.member)(power, retPos, playerNdx, weaponRadius);
}
