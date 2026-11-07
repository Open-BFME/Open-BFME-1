// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// Rva002C3FE0Owner::rva002C3E00, retail 0x002C3E00 (382 B, thiscall, ret 8; hidden return
// pointer). It steps along the owner object's facing in loco-data increments while the
// 0x002C3FE0 height-clearance helper (through ILT 0x0002A991) accepts each sample, and
// returns the last accepted position by value. ilt_oracle contradicts every placeholder
// spelling at this address, so the name stays address-derived. Handoff:
// targets/game/reverse/attempt_support/20261107-002c3e00-by-value-position.md
// Structural guide: BFME 2 donor Rva0036C6AFState::rva0036C8A5 (open-bfme-2 dbde7dbe,
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00368C7A.cpp): the sample
// position is returned BY VALUE through the hidden pointer, and the position type has a
// user-written copy constructor. Retail leaves the hidden pointer in EAX at every exit.
#include "Libraries/Include/Lib/Coord3D.h"
#include "matrix3d.h"
struct Rva002C3E00Data { char field00[0x74]; float field74,field78,field7C; };
struct Rva002C3E00Loco { char field00[4]; Rva002C3E00Data *field04; };
#define BFME_HAVE_COORD3D 1
#include "GameEngine/Source/GameLogic/Object/object.h"
struct Rva002C3E00Context { char field00[0x10]; Object *field10; };
struct Rva002C3E00Position : public Coord3D
{
	__forceinline Rva002C3E00Position() {}
	__forceinline Rva002C3E00Position(const Rva002C3E00Position &r) { x = r.x; y = r.y; z = r.z; }
	__forceinline void set(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	__forceinline void scale(float s) { x *= s; y *= s; z *= s; }
	__forceinline void add(const Rva002C3E00Position *p) { x += p->x; y += p->y; z += p->z; }
};
class Rva002C3FE0Owner
{
	char field00[0x1c];
	Rva002C3E00Context *field1C;
public:
	Rva002C3E00Position rva002C3E00(bool *shortened, bool doubled);
	bool method(const Coord3D *, float);
};
Rva002C3E00Position Rva002C3FE0Owner::rva002C3E00(bool *shortened, bool doubled)
{
	Object *object = field1C->field10;
	Rva002C3E00Position last = *(const Rva002C3E00Position *)&object->m_cachedPos;
	float achieved = 0.0f;
	void *ai = object->m_ai;
	if (!ai)
		return last;
	float height = object->m_cachedPos.z;
	Vector3 xv = object->m_transform.Get_X_Vector();
	Rva002C3E00Position direction;
	direction.set(xv.X, xv.Y, xv.Z);
	const Rva002C3E00Data *data = ((Rva002C3E00Loco *)ai)->field04;
	float limit = data->field74;
	float step = data->field78;
	float slope = data->field7C;
	if (doubled)
		limit *= 2.0f;
	for (float distance = step; distance <= limit; distance += step)
	{
		Rva002C3E00Position offset = direction;
		offset.scale(distance);
		Rva002C3E00Position candidate = *(const Rva002C3E00Position *)&object->m_cachedPos;
		candidate.add(&offset);
		if (!method(&candidate, slope * distance + height))
			break;
		achieved = distance;
		last = candidate;
	}
	if (limit / 2.0f > achieved)
		*shortened = true;
	else
		*shortened = false;
	return last;
}
