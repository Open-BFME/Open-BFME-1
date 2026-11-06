// ?method@Rva0016F150@@QAE_NPAUCoord3D@@PAVObject@@PAX@Z
// cl: /DNDEBUG /MD /Igame/Libraries/Include
//
// Retail RVA 0x0016F150, 352 bytes, ret 0x0C (this unused). Reached through
// ILT 0x0002255C from 0x00182F70 (+0x2DC/+0x33C), the horde melee approach
// computePath. Steps the destination back toward the object in 10-unit steps
// (count -(int)(len2D * -0.05f) - 1, the idiom of Rva0016EE00) until
// Pathfinder::lineClear (ILT 0x000432A2) accepts the candidate on the
// object's layer (Object::getLayer, ILT 0x0003A391), then stores it.
//
// BFME 2 donor: Open-BFME-2 dbde7dbe Code/GameEngine/Source/GameLogic/AI/
// AIStatesBfmeOnExit.cpp AIAttackMeleeHordeApproachTargetState::rva00344D60
// (same step-back body) supplied the shape: memberwise copies of the
// destination into direction and candidate, a three-field sub with z cleared
// afterwards, and Normalize through an accumulated GetLength. That shape
// fixes the x87 load order and lets the y scale consume its register. The
// third argument is never read. No BFME 1 name evidence: the method keeps
// the address name.
#include <math.h>
#include "Lib/Coord3D.h"

struct MemberwiseCoord3D : public Coord3D
{
	MemberwiseCoord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
	float GetLength2D() const { return (float)sqrt(x * x + y * y); }
	float GetLength() const { float a = x * x; a += y * y; a += z * z; return (float)sqrt(a); }
	float Normalize() { float len = GetLength(); float inv = 1.0f / len; x *= inv; y *= inv; z *= inv; return len; }
};

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class AIUpdateInterface
{
public:
	char m_unreconstructed000[0x1b8];
	Int m_1b8;
};

class Object
{
public:
	Int getLayer() const;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_unreconstructed000[0x38];
	Coord3D m_position;
	char m_unreconstructed044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class Pathfinder
{
public:
	Int lineClear(Object *obj, Int locomotorSet, PathfindLayerEnum layer,
		const Coord3D *from, const Coord3D *to);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

	char m_unreconstructed00[0x0c];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class Rva0016F150
{
public:
	Bool method(Coord3D *destination, Object *obj, void *unused);
};

Bool Rva0016F150::method(Coord3D *destination, Object *obj, void *unused)
{
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;
	MemberwiseCoord3D direction(*destination);
	MemberwiseCoord3D candidate(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	Int count = -(Int)(direction.GetLength2D() * -0.05f) - 1;
	direction.Normalize();
	direction.scale(10.0f);
	for (Int i = 0; i < count; i++)
	{
		Int loco = ai->m_1b8;
		if ((unsigned char)TheAI->pathfinder()->lineClear(obj, loco,
				(PathfindLayerEnum)obj->getLayer(), &candidate, &candidate))
		{
			*destination = candidate;
			return true;
		}
		candidate.sub(&direction);
	}
	return false;
}
