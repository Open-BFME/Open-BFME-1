// ?Rva00150100Rotate@@YAXPBUCoord3D@@0PAUCoord2D@@@Z
// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /DNDEBUG /DWIN32 /MD
#include "Lib/BaseType.h"

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern const Real g_rva01075350;
extern Real g_bfmeDefaultBU;

// Retail RVA 0x00150100. The matched waypoint caller reaches it through ILT
// 0x0003D104 with two Coord3D inputs and one Coord2D output. This address-
// derived name keeps the helper's unproven owner and semantic name opaque.
void Rva00150100Rotate(const Coord3D *pB, const Coord3D *pA, Coord2D *vec)
{
	volatile Real scratch[6];
	Real dx = pA->x;
	_ReadWriteBarrier();
	scratch[4] = pA->y;
	dx -= pB->x;
	Real dy = scratch[4];
	dy -= pB->y;
	Real len = (Real)sqrt(dy * dy + dx * dx);
	if (len != g_rva01075350)
	{
		Real scale = g_bfmeDefaultBU / len;
		dx *= scale;
		dy *= scale;
	}
	scratch[0] = -dy;
	scratch[1] = dx;
	Real inputX = vec->x;
	scratch[3] = inputX * dx;
	scratch[4] = inputX * dy;
	Real inputY = vec->y;
	scratch[0] *= inputY;
	scratch[1] *= inputY;
	Real outX = scratch[0];
	outX += scratch[3];
	Real outY = scratch[1];
	outY += scratch[4];
	vec->x = outX;
	vec->y = outY;
}

// Retail RVA 0x00150A70 (181 B): AIGroup's place-members-in-formation walk,
// the helper's caller through ILT 0x0003D104. It is defined in this unit
// because it is exact only when the compiler sees that the helper does not
// keep the offset's address (a non-capturing stub gives the same bytes; with
// the helper only declared both offset words cannot load before the first
// store). Owner: the group member list at +0x04 and prepFollow (ILT
// 0x0002E636), as in the AIGroup sibling bodies; the method name keeps its
// address because ilt_oracle contradicts the BFME 2 donor's
// groupSetPositionInFormation spellings at ILT 0x0002059A. From the BFME 2
// donor (open-bfme-2 b5a7b8290 AIGroupSetPositionInFormation.cpp): a null
// member ends the walk instead of being skipped.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2,
	CMD_FROM_DOZER = 3,
	CMD_DEFAULT_SWITCH_WEAPON = 4
};

class Object;

class BfmePosTP
{
public:
	float x;
	float y;
	unsigned int zBits;
};

class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const BfmePosTP *position, bool flag);
};

class BfmeOwnerGK
{
public:
	void bfmeRunGK();
};

class Thing
{
public:
	float bfmeRelativeAngleTo(const Coord3D *position) const;
	void setOrientation(float angle);
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;					// +0x08
};

class AIGroup
{
public:
	void rva00150A70(Coord3D *anchor, const Coord3D *facing, int commandSource);
	void prepFollow(::CommandSourceType commandSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_memberList;			// +0x04
};

// ?rva00150A70@AIGroup@@QAEXPAUCoord3D@@PBU2@H@Z
void AIGroup::rva00150A70(Coord3D *anchor, const Coord3D *facing,
		int commandSource)
{
	((BfmeOwnerGK *)this)->bfmeRunGK();
	prepFollow((::CommandSourceType)commandSource, 0);

	BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
	if (memberNode != m_memberList)
	{
		const Coord3D *anchorPosition = anchor;
		while (memberNode != m_memberList)
		{
			Object *member = ((BfmeMemberNode *)memberNode)->m_bfmeValue;
			if (member == 0)
				return;
			Coord2D offset;
			offset.x = *(float *)((char *)member + 0x320);
			offset.y = *(float *)((char *)member + 0x324);
			Rva00150100Rotate(anchorPosition, facing, &offset);
			BfmePosTP position;
			position.x = offset.x + anchorPosition->x;
			position.y = offset.y + anchorPosition->y;
			position.zBits = *(unsigned int *)((char *)anchorPosition + 0x08);
			((BfmeHostTP *)member)->bfmeSetPositionTP(&position, false);

			float angle = ((Thing *)member)->bfmeRelativeAngleTo(facing);
			((Thing *)member)->setOrientation(angle);
			memberNode = memberNode->m_bfmeNext;
		}
	}
}
