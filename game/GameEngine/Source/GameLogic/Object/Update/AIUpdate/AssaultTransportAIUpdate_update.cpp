// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA 0x002B4C00, 1199 bytes, terminal RET at +0x4AE then INT3.
// Derived from EA GeneralsMD AssaultTransportAIUpdate.cpp (GPL-3.0-or-later).
// BFME AssaultTransportAIUpdate::update. Member layout witnessed by landed
// xfer/giveFinalOrders/retrieveMembers, health tests by isMemberWoundedTwin.
// Constructor 0x002B46F0 installs vtable 0x010C604C at +0x10; slot 0
// reaches this body through ILT 0x00042802.
// update receives the secondary UpdateModuleInterface at complete object+0x10.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef bool Bool;
typedef float Real;
#define TRUE true
#define FALSE false
#define INVALID_ID 0
#define MAX_TRANSPORT_SLOTS 10
#define NO_MAX_SHOTS_LIMIT 0x7fffffff
class Object;
enum CommandSourceType { CMD_FROM_PLAYER=0, CMD_FROM_AI=2 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
enum AIStateType { AI_ENTER=15, AI_ATTACK_MOVE_TO=33 };
enum ObjectStatusTypes { OBJECT_STATUS_IS_ATTACKING=22 };
struct Coord3D {
    Real x,y,z;
    void zero() { x=0; y=0; z=0; }
    void add(const Coord3D *p) { x+=p->x; y+=p->y; z+=p->z; }
};
class StateMachine { public: Object *getGoalObject(); };
template<int N> class Rva002B4C00Slots : public Rva002B4C00Slots<N-1> {
public: virtual void slot(char (*)[N])=0;
};
template<> class Rva002B4C00Slots<0> {};
class BodyModuleInterface : public Rva002B4C00Slots<4> {
public:
    virtual Real getHealth() const=0;
    virtual void slot14()=0;
    virtual Real getMaxHealth() const=0;
};
typedef _STL::list<Object*> ContainedItemsList;
class ContainModuleInterface : public Rva002B4C00Slots<65> {
public: virtual const ContainedItemsList *getContainedItemsList() const=0;
};
class AICommandInterface {
public:
    virtual void aiDoCommand(const void*)=0;
    void aiAttackObject(Object*,Int,CommandSourceType);
    void aiAttackMoveToPosition(const Coord3D*,Int,CommandSourceType);
    void aiIdle(CommandSourceType);
    void aiEnter(Object*,CommandSourceType);
    void aiExit(Object*,CommandSourceType);
};
struct AssaultTransportAIUpdateModuleData {
    char m_pad00[0x64];
    Real m_membersGetHealedAtLifeRatio;
};
class BehaviorModule : public Rva002B4C00Slots<128> {
public:
    virtual CommandSourceType getLastCommandSource() const=0; // primary slot 0x200
    const AssaultTransportAIUpdateModuleData *m_moduleData; // +4
    Object *m_object; // +8
    char m_pad0c[4];
    Object *getObject() const { return m_object; }
};
class UpdateModuleInterface {
public: virtual UpdateSleepTime update()=0;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface {
    char m_pad14[0xc];
};
class AIUpdateInterface : public UpdateModule, public AICommandInterface {
public:
    virtual UpdateSleepTime update();
    AIStateType getAIStateType() const;
    Bool bfmeBlocksFormationRefresh();
    void setAllowedToChase(Bool value) { m_allowedToChase=value; }
    Object *getGoalObject() const { return m_stateMachine->getGoalObject(); }
private:
    char m_pad24[0xc];
    StateMachine *m_stateMachine; // +0x30
    char m_pad34[0x32f-0x34];
    Bool m_allowedToChase;
    char m_pad330[0x344-0x330];
};
class Object {
public:
    ObjectID getID() const { return m_id; }
    Bool isEffectivelyDead() const { return (m_privateStatus & 1)!=0; }
    Bool testStatus(ObjectStatusTypes bit) const { return (m_status & (1u<<bit))!=0; }
    AIUpdateInterface *getAI() const { return m_ai; }
    BodyModuleInterface *getBodyModule() const { return m_body; }
    ContainModuleInterface *getContain() const { return m_contain; }
    Bool isContained() const { return m_containedBy!=0; }
    const Coord3D *getPosition() const { return &m_position; }
private:
    char m_pad00[0x38];
    Coord3D m_position;
    char m_pad44[0x74-0x44];
    ObjectID m_id;
    char m_pad78[0x90-0x78];
    UnsignedInt m_status;
    char m_pad94[0x1fc-0x94];
    ContainModuleInterface *m_contain;
    BodyModuleInterface *m_body;
    AIUpdateInterface *m_ai;
    char m_pad208[0xc];
    Object *m_containedBy;
    char m_pad218[0x344-0x218];
    unsigned char m_privateStatus;
};
typedef _STL::hash_map<ObjectID,Object*,_STL::hash<ObjectID>,_STL::equal_to<ObjectID> > ObjectPtrHash;
class GameLogic {
public:
    Object *findObjectByID(ObjectID id) {
        if (id==0) return 0;
        ObjectPtrHash::iterator it=m_objHash.find(id);
        if (it==m_objHash.end()) return 0;
        return (*it).second;
    }
private:
    char m_pad00[0xb0];
    ObjectPtrHash m_objHash;
};
extern GameLogic *TheGameLogic;
// The decoded moving-state query at 0x00278830 already has the pinned
// AIUpdateInterface::bfmeBlocksFormationRefresh contract. Its ILT is 0x00044774;
// the callee reads Object+0x214, nested AI+0x204, and primary isIdle slot+0x180.

class AssaultTransportAIUpdate : public AIUpdateInterface {
public:
    virtual UpdateSleepTime update();
    void giveFinalOrders();
    void retrieveMembers();
    const AssaultTransportAIUpdateModuleData *getAssaultTransportAIUpdateModuleData() const { return m_moduleData; }
    Bool isMemberWounded(const Object*) const;
    Bool isMemberHealthy(const Object*) const;
    Bool isAttackPointless() const;
private:
    ObjectID m_memberIDs[10];
    Bool m_memberHealing[10];
    Bool m_newMember[10];
    Coord3D m_attackMoveGoalPos;
    ObjectID m_designatedTarget;
    Int m_state;
    UnsignedInt m_framesRemaining;
    Int m_currentMembers;
    Bool m_isAttackMove;
    Bool m_isAttackObject;
    Bool m_newOccupantsAreNewMembers;
};

UpdateSleepTime AssaultTransportAIUpdate::update( void )
{
	Object *transport = getObject();
	//const AssaultTransportAIUpdateModuleData *data = getAssaultTransportAIUpdateModuleData();

	if( transport->isEffectivelyDead() )
	{
		giveFinalOrders();
		return UPDATE_SLEEP_FOREVER;
	}

	//First removing dead members or members that have been ordered to do something outside of this AI.
	if( m_currentMembers )
	{
		for( int i = 0; i < m_currentMembers; i++ )
		{
			Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
			AIUpdateInterface *ai = member ? member->getAI() : NULL;
			if( !member || member->isEffectivelyDead() || ai->getLastCommandSource() != CMD_FROM_AI )
			{
				//Member is toast -- so remove him from our list!
				if( m_currentMembers - 1 > i )
				{
					//Move the last slot to this slot to keep array contiguous.
					m_memberIDs[ i ]			= m_memberIDs[ m_currentMembers - 1 ];
					m_memberHealing[ i ]	= m_memberHealing[ m_currentMembers - 1 ];
					m_newMember[ i ]			= m_newMember[ m_currentMembers - 1 ];
				}
				else
				{
					//Just clean out last slot.
					m_memberIDs[ i ]			= INVALID_ID;
					m_memberHealing[ i ]	= FALSE;
					m_newMember[ i ]			= FALSE;
				}
				if( ai )
				{
					//Important! Members of our assault transport must be allowed to chase down designated enemies.
					//Generally only player commands allow this, so this flag allows AI commands to do the same.
					//We need to turn this off though, because this ex-member is no longer under transport control.
					ai->setAllowedToChase( FALSE );
				}
				m_currentMembers--;
			}
		}
	}

	//Now add any potentially new members to the group.
	ContainModuleInterface *contain = transport->getContain();
	if( contain )
	{
		const ContainedItemsList *passengerList = contain->getContainedItemsList();
		ContainedItemsList::const_iterator passengerIterator;
		passengerIterator = passengerList->begin();
		while( passengerIterator != passengerList->end() )
		{
			Object *passenger = *passengerIterator;
			//Advance to the next iterator
			passengerIterator++;

			//Make sure it isn't in our list already.
			Bool found = FALSE;
			for( int i = 0; i < m_currentMembers; i++ )
			{
				if( passenger->getID() == m_memberIDs[ i ] )
				{
					//He is in the list... so skip him.
					found = TRUE;
					break;
				}
			}
			if( found )
			{
				//Get next passenger.
				continue;
			}

			//It's possible to add members manually -- but if we already have 10 members, then wait!
			if( m_currentMembers < MAX_TRANSPORT_SLOTS )
			{
				//Not in list, so add him!
				m_memberIDs[ m_currentMembers ] = passenger->getID();
				if( passenger->getAI() )
				{
					//Important! Members of our assault transport must be allowed to chase down designated enemies.
					//Generally only player commands allow this, so this flag allows AI commands to do the same.
					passenger->getAI()->setAllowedToChase( TRUE );
				}
				
				//Check if the passenger is wounded below threshhold (if so make sure we heal him before ordering him to fight!)
				if( isMemberWounded( passenger ) )
				{
					m_memberHealing[ m_currentMembers ] = TRUE;
				}
				if( m_newOccupantsAreNewMembers )
				{
					//New members won't eject out until a new attack order is issued.
					m_newMember[ m_currentMembers ] = TRUE;
				}

				m_currentMembers++;
			}
		}
		m_newOccupantsAreNewMembers = TRUE;
	}

	if( isAttackPointless() )
	{
		aiIdle( CMD_FROM_AI );
		return UPDATE_SLEEP_NONE;
	}

	//Keep track of the average position of all combat units assigned to me.
	Coord3D fighterCentroidPos;
	UnsignedInt fightingMembers = 0;
	fighterCentroidPos.zero();

	//If we're already in the process, reacquire the designated target again... see if
	//it's still alive.
	Object *designatedTarget = TheGameLogic->findObjectByID( m_designatedTarget );
	if( designatedTarget && designatedTarget->isEffectivelyDead() )
	{
		designatedTarget = NULL;
	}
	if( designatedTarget )
	{
		//Look for members not currently attacking this target.
		for( int i = 0; i < m_currentMembers; i++ )
		{
			Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
			AIUpdateInterface *ai = member ? member->getAI() : NULL;
			
			if( member && ai )
			{
				Bool contained = member->isContained();
				Bool wounded = isMemberWounded( member );
				if( contained && isMemberHealthy( member ) && !m_newMember[ i ] )
				{
					//This contained member is healthy so order him to exit to start fighting!
					//New members are exempt!
					ai->aiExit( transport, CMD_FROM_AI );
				}
				if( !contained ) 
				{
					if( wounded )
					{
						if( ai->getAIStateType() != AI_ENTER )
						{
							//Order wounded members back to get healed.
							ai->aiEnter( transport, CMD_FROM_AI );
						}
					}
					else 
					{
						//Increment the number of fighters and their position.
						fighterCentroidPos.add( member->getPosition() );
						fightingMembers++;

						if( !ai->bfmeBlocksFormationRefresh() )
						{
							if( ai->getGoalObject() != designatedTarget )
							{
								//Okay, this dude is outside and waiting... order him to attack the designated target
								ai->aiAttackObject( designatedTarget, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI );
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if( m_isAttackMove && getAIStateType() != AI_ATTACK_MOVE_TO )
		{
			//Continue to move towards the attackmove area.
			aiAttackMoveToPosition( &m_attackMoveGoalPos, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI );
		}
		else if( m_isAttackObject )
		{
			retrieveMembers();
		}
	}

	
	
	AIUpdateInterface::update();
	//return (mine < ret) ? mine : ret;
	/// @todo srj -- someday, make sleepy. for now, must not sleep.
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
// ?isAttackPointless@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isAttackPointless() const
{
	//If all members are new members (thus can't attack), and the transport itself
	//is still attacking, stop!
	const Object *transport = getObject();
	if( transport->testStatus( OBJECT_STATUS_IS_ATTACKING ) )
	{
		for( int i = 0; i < m_currentMembers; i++ )
		{
			if( !m_newMember[ i ] )
			{
				//We have a non-new member, so attack is valid.
				return FALSE;
			}
		}

		//We are trying to attack, but can't because all our members are new.
		return TRUE;
	}

	//We aren't trying to attack, so everything is good.
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?isMemberWounded@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isMemberWounded( const Object *member ) const
{
	const AssaultTransportAIUpdateModuleData *data = getAssaultTransportAIUpdateModuleData();
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		Real ratio = body->getHealth() / body->getMaxHealth();
		if( ratio < data->m_membersGetHealedAtLifeRatio )
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?isMemberHealthy@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isMemberHealthy( const Object *member ) const
{
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		if( body->getHealth() == body->getMaxHealth() )
		{
			return TRUE;
		}
	}
	return FALSE;
}


