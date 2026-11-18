// cl: /DNDEBUG /MD /EHsc
// Contain-list method at 0x002229E0 (112 B, ret 4 then int3 padding).
// Retail reaches it through ILT 0x0000CCA2 from eleven contain vtables (slot 56
// of ??_7CaveContain@@6BCaveContainIface3@@@ and
// ??_7GarrisonContain@@6B?$OpenContainSecondaryBase@$01@@@ among them), on the
// same subobject whose object list (+0x18) the matched
// Rva222970FilteredDispatch::findAndDispatch (0x00222970) walks. It returns the
// contained object nearest to a point in 2D (squared distance, first one wins
// ties). The owning class is unproven, so it keeps an address-derived name.

#include "../../Include/Common/ScalarTypes.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	char m_unmodelled_00[0x38];
	Coord3D m_position;
};

struct Rva002229E0Node
{
	Rva002229E0Node *next;
	Rva002229E0Node *previous;
	Object *object;
};

class Rva002229E0Contain
{
public:
	virtual Object *nearest(const Coord3D *pos);

private:
	char m_unmodelled_04[0x14];
	Rva002229E0Node *m_objects;
};

// ?nearest@Rva002229E0Contain@@UAEPAVObject@@PBUCoord3D@@@Z
Object *Rva002229E0Contain::nearest(const Coord3D *pos)
{
	Object *closest = 0;
	Real closestDistSqr = 3.4028235e38f;
	for (Rva002229E0Node *node = m_objects->next; node != m_objects; node = node->next)
	{
		Object *obj = node->object;
		if (!obj)
			continue;
		Coord3D delta;
		delta.x = pos->x;
		delta.y = pos->y;
		delta.z = 0.0f;
		delta.x -= obj->getPosition()->x;
		delta.y -= obj->getPosition()->y;
		Real distSqr = delta.x * delta.x + delta.y * delta.y;
		if (!closest || closestDistSqr > distSqr)
		{
			closestDistSqr = distSqr;
			closest = obj;
		}
	}
	return closest;
}
