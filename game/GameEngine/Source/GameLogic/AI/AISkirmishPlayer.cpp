// cl: /DNDEBUG /MD /EHsc
// AISkirmishPlayer's extend-base overrides, retail 0x00168780-0x00168900.
// Each is the Zero Hour body unchanged (AISkirmishPlayer.cpp): a qualified
// call of the AIPlayer method with the same arguments, which VC7.1 emits as
// a five-byte tail jump to the AIPlayer ILT. ilt_oracle CONFIRMS every
// AISkirmishPlayer name at the ILT that reaches its body and every AIPlayer
// target name at the ILT the jump hits.

class Object;
class TeamPrototype;
class Coord3D;

#include "../../../Include/Common/ScalarTypes.h"


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	virtual void onUnitProduced( Object *factory, Object *unit );
	virtual void buildSpecificAITeam( TeamPrototype *teamProto, Bool priorityBuild );

protected:
	virtual Bool selectTeamToReinforce( Int minPriority );
	virtual Bool selectTeamToBuild( void );
	virtual void checkReadyTeams( void );
	virtual void checkQueuedTeams( void );
	virtual void queueDozer( void );
	virtual Object *findDozer( const Coord3D *pos );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AISkirmishPlayer.h
class AISkirmishPlayer : public AIPlayer
{
public:
	virtual void onUnitProduced( Object *factory, Object *unit );
	virtual void buildSpecificAITeam( TeamPrototype *teamProto, Bool priorityBuild );

protected:
	virtual Bool selectTeamToReinforce( Int minPriority );
	virtual Bool selectTeamToBuild( void );
	virtual void checkReadyTeams( void );
	virtual void checkQueuedTeams( void );
	virtual void queueDozer( void );
	virtual Object *findDozer( const Coord3D *pos );
};

// Retail 0x00168780 (ILT 0x0000F6F5) -> AIPlayer ILT 0x0001B1B2.
void AISkirmishPlayer::onUnitProduced( Object *factory, Object *unit )
{
	AIPlayer::onUnitProduced(factory, unit);
}

// Retail 0x00168790 (ILT 0x00040895) -> AIPlayer ILT 0x0003EE5A.
Bool AISkirmishPlayer::selectTeamToReinforce( Int minPriority )
{
	return AIPlayer::selectTeamToReinforce(minPriority);
}

// Retail 0x001687A0 (ILT 0x000421BD) -> AIPlayer ILT 0x0001B216.
Bool AISkirmishPlayer::selectTeamToBuild( void )
{
	return AIPlayer::selectTeamToBuild();
}

// Retail 0x00168800 (ILT 0x00015771) -> AIPlayer ILT 0x0003C79F.
void AISkirmishPlayer::buildSpecificAITeam( TeamPrototype *teamProto, Bool priorityBuild )
{
	AIPlayer::buildSpecificAITeam(teamProto, priorityBuild);
}

// Retail 0x00168830 (ILT 0x0003F134) -> AIPlayer ILT 0x0002403C.
void AISkirmishPlayer::checkReadyTeams( void )
{
	AIPlayer::checkReadyTeams();
}

// Retail 0x00168840 (ILT 0x0001C6F7) -> AIPlayer ILT 0x0001E27C.
void AISkirmishPlayer::checkQueuedTeams( void )
{
	AIPlayer::checkQueuedTeams();
}

// Retail 0x001688F0 (ILT 0x00001087) -> AIPlayer ILT 0x00033802.
void AISkirmishPlayer::queueDozer( void )
{
	AIPlayer::queueDozer();
}

// Retail 0x00168900 (ILT 0x0000808A) -> AIPlayer ILT 0x0002CA57. BFME keys
// Coord3D as a class, so the pointer mangles PBVCoord3D.
Object *AISkirmishPlayer::findDozer( const Coord3D *pos )
{
	return AIPlayer::findDozer(pos);
}
