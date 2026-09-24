// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva000EDDE0@Rva000EDDE0Team@@QBEMPAVObject@@@Z
//
// Address-derived: no proven owner or real name. `this` has the same
// TeamMemberList-head-at-+0x0c layout the landed Rva000EDB30TeamIsIdle.cpp
// proved (AIPlayer::checkReadyTeams caller, ILT 0x0003A143), and walks it
// through the identical BfmeObjectDlinkBase::dlink_next_TeamMemberList PMF
// (ILT 0x00001140), so the Object/DLINK shim below is copied verbatim from
// that landed body rather than re-derived.
//
// Shape: read `other`'s current locomotor speed (999999.0f, i.e. unlimited,
// when `other` carries no AI); take the slowest getCurLocomotorSpeed() among
// every team member that has an AI; clamp that minimum to at least a fixed
// fraction -- the float GlobalData-style constant at retail 0x01083B6C -- of
// `other`'s own speed, and return the larger of the two.
//
// getCurLocomotorSpeed itself is real: ?getCurLocomotorSpeed@AIUpdateInterface@@QAEMXZ,
// pinned in reverse/symbols.csv at its ILT 0x0003DAA5, body 0x0026EC30 in
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceHelpers.cpp.

typedef bool Bool;
typedef float Real;

class AIUpdateInterface
{
public:
	Real getCurLocomotorSpeed();
};

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[ 4 ];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[ 4 ];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[ 0x64 ];
};

extern void j_00001140();
#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	unsigned char m_tail[ 0x2c0 ];
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)() const;

class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator( Object *cur, BfmeGetNextTeamMemberFunc getNext )
		: m_cur( cur ), m_getNext( getNext ) { }

	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }

	void advance()
	{
		if ( m_cur )
			m_cur = (m_cur->*m_getNext)();
	}

private:
	Object *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

class Rva000EDDE0Team
{
public:
	Real rva000EDDE0( Object *other ) const;

private:
	unsigned char m_beforeMemberList[ 0x0c ];
	Object *m_memberList;
};

Real Rva000EDDE0Team::rva000EDDE0( Object *other ) const
{
	Real otherSpeed = 999999.0f;
	AIUpdateInterface *otherAi = other->getAIUpdateInterface();
	if ( otherAi )
		otherSpeed = otherAi->getCurLocomotorSpeed();

	Real bestSpeed = otherSpeed;

	for ( BfmeDlinkIterator iter( m_memberList, BfmeObjectDlinkBase::dlink_next_TeamMemberList ); !iter.done(); iter.advance() )
	{
		Object *obj = iter.cur();
		if ( obj == 0 )
			continue;
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if ( ai )
		{
			if ( ai->getCurLocomotorSpeed() < bestSpeed )
				bestSpeed = ai->getCurLocomotorSpeed();
		}
	}

	Real scaledOtherSpeed = otherSpeed * *(const Real *)0x01083B6C;
	return ( bestSpeed < scaledOtherSpeed ) ? scaledOtherSpeed : bestSpeed;
}
