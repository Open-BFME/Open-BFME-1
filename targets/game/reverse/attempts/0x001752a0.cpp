// ?Rva001752A0@@YA_NPAUCoord3D@@PAVObject@@1@Z
// partial score=0.949 date=2026-09-28
// ?Rva001752A0@@YA_NPAUCoord3D@@PAVObject@@1@Z
// cl: /DNDEBUG /MD /EHsc
// Retail 0x001752A0, 943 bytes, cdecl (destination, source, victim); called
// through ILT 0x0001E0D3 by AIAttackMeleeEngageState::computePath.
// REWRITE (opus-5.5, 2026-09-28): real member declarations on existing pins
// (Thing::isKindOf, NameKeyGenerator::nameToKey, Object::findModule,
// Object::getCurrentWeapon, BfmePathfinderMethods::check,
// Pathfinder::slowDoesPathExist) and ledger body names reached through
// auto-discovered ILTs (TerrainLogic::getLayerForDestination,
// Pathfinder::bfmeCellTypeFourWithFlag, Coord3D::normalize,
// Pathfinder::adjustToPossibleDestination, Rva00266340::is).
// Levers that moved it: one address-taken Coord3D (normalize) for phases 1-2
// with dy a separate float; 3D length (z=0) for the unit scale so the two
// sqrts do not CSE; final phase reads delta = *destination into float dx/dy;
// TheAI cached in a local at the found label. Measured 944B vs 943B, 412
// non-reloc diffs, shape 0.949. Residue: source ESI (retail EBP), destination
// EDI (retail ESI), &pos EBX (retail EDI); x/y offset products load offset
// first (retail loads delta first).
#include <math.h>

typedef bool Bool;
typedef float Real;
enum KindOfType { KINDOF_5C = 0x5c };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum WeaponSlotType { WEAPONSLOT_DUMMY = 0 };
enum ObjectID { INVALID_ID = 0 };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

struct Coord3D
{
	Real x, y, z;
	void normalize();
};

class Module {};
class Weapon {};
class LocomotorSet {};
class Rva00266340 { public: Bool is() const; };

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class AIUpdateInterface
{
	char m_pad000[0x1a8];
public:
	LocomotorSet m_locomotorSet;
};

class Object : public Thing
{
	char m_pad000[0x38];
public:
	Coord3D m_pos038;
	char m_pad044[0xbc - 0x44];
	Real m_bfmeBC;
	char m_pad0c0[0x204 - 0xc0];
	AIUpdateInterface *m_ai204;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Module *findModule(NameKeyType key) const;
};

class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, ObjectID ignore);
	Bool bfmeCellTypeFourWithFlag(const Coord3D *pos, PathfindLayerEnum layer);
	Bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

class BfmePathfinderMethods
{
public:
	Bool check(const Object *obj, const Coord3D *pos, const Weapon *weapon, int flag);
};

class AIData
{
	char m_pad000[0xd0];
public:
	Real m_meleeOffset;
};

class AI
{
	char m_pad000[0x0c];
public:
	Pathfinder *m_pathfinder;
	char m_pad010[4];
	AIData *m_data14;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern AI *TheAI;
extern NameKeyGenerator *TheNameKeyGenerator;
extern TerrainLogic *TheTerrainLogic;

bool Rva001752A0(Coord3D *destination, Object *source, Object *victim)
{
	AIUpdateInterface *ai = source->m_ai204;
	if (ai == 0)
		return false;

	Coord3D victimPos;
	Coord3D candidate;
	Real initialDistance;
	Bool pathCheck;
	Bool adjusted;
	Coord3D delta;
	AI *theAI;
	{
		delta.x = destination->x - source->m_pos038.x;
		Real dy = destination->y - source->m_pos038.y;
		victimPos = *destination;
		initialDistance = (Real)sqrt(delta.x * delta.x + dy * dy);

		if (victim)
		{
			victimPos = victim->m_pos038;
			if (victim->isKindOf(KINDOF_5C))
			{
				static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
				Module *module = victim->findModule(key);
				if (module && ((Rva00266340 *)module)->is())
					return true;
			}
		}

		Pathfinder *pathfinder = TheAI->m_pathfinder;
		pathCheck = ((BfmePathfinderMethods *)pathfinder)->check(
			source, &victimPos, source->getCurrentWeapon(0), 0);
		if (pathCheck && TheAI->m_pathfinder->slowDoesPathExist(
			source, &source->m_pos038, destination, INVALID_ID))
			return true;

		delta = *destination;
		candidate = *destination;
		delta.x -= source->m_pos038.x;
		delta.y -= source->m_pos038.y;
		delta.z = 0.0f;
		int limit = -1 - (int)((Real)sqrt(delta.y * delta.y + delta.x * delta.x) * -0.05f);
		Real length = (Real)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		Real scale = 1.0f / length;
		delta.x *= scale;
		delta.y *= scale;
		delta.z *= scale;
		delta.x *= 20.0f;
		delta.y *= 20.0f;
		delta.z *= 20.0f;

		Bool specialCell = false;
		for (int index = 0; index < limit; ++index)
		{
			candidate.x -= delta.x;
			candidate.y -= delta.y;
			candidate.z -= delta.z;
			if (TheAI->m_pathfinder->slowDoesPathExist(source, &source->m_pos038, &candidate, INVALID_ID))
				goto found;
			if (TheTerrainLogic->getLayerForDestination(source, &candidate) > LAYER_GROUND ||
				TheAI->m_pathfinder->bfmeCellTypeFourWithFlag(&candidate, LAYER_GROUND))
				specialCell = true;
		}
		return false;

found:
		theAI = TheAI;
		adjusted = false;
		if (specialCell && !pathCheck)
		{
			Real offset = theAI->m_data14->m_meleeOffset + source->m_bfmeBC;
			delta.normalize();
			adjusted = true;
			delta.x *= offset;
			delta.y *= offset;
			delta.z *= offset;
			candidate.x -= delta.x;
			candidate.y -= delta.y;
			candidate.z -= delta.z;
		}
	}

	delta = *destination;
	Real dx = delta.x - candidate.x;
	Real dy = delta.y - candidate.y;
	if (!adjusted)
	{
		if ((Real)sqrt(dx * dx + dy * dy) + 20.0f > initialDistance)
			return false;
	}

	theAI->m_pathfinder->adjustToPossibleDestination(source, ai->m_locomotorSet, &candidate);
	*destination = candidate;
	return true;
}
