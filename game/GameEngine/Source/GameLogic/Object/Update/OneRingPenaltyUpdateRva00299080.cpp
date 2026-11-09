// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// stlport
//
// Retail 0x00299080, 257 bytes: a OneRingPenaltyUpdate helper that spawns
// the module data's object near the owner. It finds the template named at
// module data +0x08, creates it on the neutral player's default team (or the
// owner's team when there is no neutral player), and records the new
// object's id at +0x24. It then picks a random angle in [-PI, PI] (the
// GameLogic random draw tagged OneRingPenaltyUpdate.cpp line 219), places the
// object at the owner's position offset by the module data radius (+0x18)
// along that angle, on the terrain, and records the angle at +0x2C. Its only
// caller is the dump at 0x002995E0 in the same file.
//
// A naked lift named it PathfindLayer::isPointOnWall, which this body is not.
// The source file literal proves the owning file; the method name is not
// proven, so it keeps its address.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#define NULL 0
#define PI 3.14159265359f

enum ObjectID { INVALID_ID = 0 };

#include "Lib/Coord3D.h"

Real Cos(Real angle);
Real Sin(Real angle);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <size_t NUMBITS>
class BitFlags
{
private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<86> ObjectStatusMaskType;

class ThingTemplate;
class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Team *getDefaultTeam() { return m_defaultTeam; }
private:
	char m_unmodelled000[0x230];
	Team *m_defaultTeam;						// +0x230
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNeutralPlayer() { return m_neutralPlayer; }
private:
	char m_unmodelled000[0x14];
	Player *m_neutralPlayer;					// +0x14
};

extern PlayerList *ThePlayerList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	Team *getTeam() const { return m_team; }
private:
	char m_unmodelled000[0x38];
	Coord3D m_pos;							// +0x38
	char m_unmodelled044[0x74 - 0x44];
	ObjectID m_id;							// +0x74
	char m_unmodelled078[0x23c - 0x78];
	Team *m_team;							// +0x23C
};

// Thing::setPosition is the retail callee (ILT 0x0003A1A7); Object derives from Thing.
class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

// The existing retail lookup owner is BfmeThingFactory at RVA 0x00137E80.
// This pointer-only declaration models no factory layout or new object.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team,
		const ObjectStatusMaskType &statusBits, unsigned int flags);
};

extern ThingFactory *TheThingFactory;

#define BFME_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	BFME_SLOT(0) BFME_SLOT(1) BFME_SLOT(2) BFME_SLOT(3) BFME_SLOT(4) BFME_SLOT(5)
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const;	// +0x18
};

#undef BFME_SLOT

extern TerrainLogic *TheTerrainLogic;

// OneRingPenaltyUpdate's module data: the spawned object's template name and
// the spawn radius are the only fields this body reads.
struct Rva00299080ModuleData
{
	char m_unmodelled000[0x08];
	AsciiString m_objectName;					// +0x08
	char m_unmodelled00c[0x18 - 0x0c];
	Real m_radius;							// +0x18
};

class OneRingPenaltyUpdate
{
public:
	void rva00299080(void);
private:
	void *m_vptr;
	const Rva00299080ModuleData *m_moduleData;			// +0x04
	Object *m_object;						// +0x08
	char m_unmodelled00c[0x24 - 0x0c];
	ObjectID m_spawnedID;						// +0x24
	char m_unmodelled028[0x2c - 0x28];
	Real m_spawnAngle;						// +0x2C
};

void OneRingPenaltyUpdate::rva00299080(void)
{
	const Rva00299080ModuleData *moduleData = m_moduleData;
	Object *owner = m_object;
	const ThingTemplate *tmpl =
		reinterpret_cast<BfmeThingFactory *>(TheThingFactory)->findTemplate(moduleData->m_objectName);
	if (tmpl)
	{
		Team *team = ThePlayerList->getNeutralPlayer()
			? ThePlayerList->getNeutralPlayer()->getDefaultTeam() : owner->getTeam();
		Object *spawned;
		{
			ObjectStatusMaskType statusBits;
			spawned = TheThingFactory->newObject(tmpl, team, statusBits, 0);
		}
		if (spawned)
		{
			m_spawnedID = spawned->getID();
			Coord3D pos;
			pos.x = owner->getPosition()->x;
			pos.y = owner->getPosition()->y;
			pos.z = owner->getPosition()->z;
			Real angle = GetGameLogicRandomValueReal(-PI, PI,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\OneRingPenaltyUpdate.cpp", 219);
			pos.x += Cos(angle) * moduleData->m_radius;
			pos.y += Sin(angle) * moduleData->m_radius;
			pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
			((Thing *)spawned)->setPosition(&pos);
			m_spawnAngle = angle;
		}
	}
}
