// Retail 0x00270360, 212 bytes. The matched Locomotor_rva001BC820 caller
// reaches this Bool thiscall predicate through ILT 0x00023795.
// Its semantic method name is unproven; preserve the address-derived identity.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/aiupdatelayout /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "GameLogic/Module/AIUpdate.h"
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
 void setOrientation(Real angle); \
 const Coord3D *getUnitDirectionVector2D() const; \
 void setPosition(const Coord3D *position);
#include "../Object/object.h"

extern Real __cdecl normalizeAngle(Real);

class Rva00270360Query
{
public:
	bool test();
	unsigned char m_head[8];
	Object *m_object;
	unsigned char m_pad00C[0x33C - 0x0C];
	int m_queryCount;
};

bool Rva00270360Query::test()
{
	Object *target = m_object;
	if (target == 0)
		return false;
	int queryCount = m_queryCount;
	m_queryCount = queryCount + 1;
	if (queryCount > 3)
		return false;

	Object *contained = target->m_containedBy;
	if (contained != 0)
		target = contained;
	if (target->m_ai == 0)
		return false;

	target->setOrientation(normalizeAngle(target->m_cachedAngle + 3.14159265358979323846f));
	const Coord3D *direction = target->getUnitDirectionVector2D();
	Coord3D position;
	position.x = direction->x;
	position.y = direction->y;
	position.z = direction->z;
	position.x *= 21.0f;
	position.y *= 21.0f;
	position.z *= 21.0f;
	position.x += target->m_cachedPos.x;
	position.y += target->m_cachedPos.y;
	position.z += target->m_cachedPos.z;
	target->setPosition(&position);
	target->m_ai->destroyPath();
	return true;
}
