// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupOverrideSpecialPowerDestination, retail 0x00151510,
// 62 bytes.
//
// The reference's body unchanged: every member that has an overridable special
// power in progress gets its destination moved.
//
// setSpecialPowerOverridableDestination is vtable slot 5 (+0x14) on the update
// interface; the power type and the location are loop invariant and sit in edi
// and ebp for the whole walk.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Coord3D;

enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h
class SpecialPowerUpdateInterface
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void setSpecialPowerOverridableDestination(const Coord3D *loc);	// vtable +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerUpdateInterface *findSpecialPowerWithOverridableDestinationActive(SpecialPowerType spType) const;	// ILT 0x00039766
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupOverrideSpecialPowerDestination(SpecialPowerType spType, const Coord3D *loc, CommandSourceType cmdSource);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::groupOverrideSpecialPowerDestination( SpecialPowerType spType, const Coord3D *loc, CommandSourceType cmdSource )
{
	_STL::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *object = (*i);
		if( object )
		{
			SpecialPowerUpdateInterface *spuInterface = object->findSpecialPowerWithOverridableDestinationActive( spType );
			if( spuInterface )
			{
				spuInterface->setSpecialPowerOverridableDestination( loc );
			}
		}
	}
}
