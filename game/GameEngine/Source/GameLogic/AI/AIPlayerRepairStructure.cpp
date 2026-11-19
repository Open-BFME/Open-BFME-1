// cl: /DNDEBUG /MD /EHsc
// readable body of ?repairStructure@AIPlayer@@UAEXW4ObjectID@@@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::repairStructure, 0x00165070, 101 bytes (ret 4 at +0x62).
// Identity: slot 14 (+0x38) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x000105B4 here, and the matched AISkirmishPlayer::checkBridges
// (0x00168A10) calls that slot with a broken bridge's id. The body is the Zero
// Hour twin: it queues a damaged structure for the dozer unless it is already
// queued or the queue is MAX_STRUCTURES_TO_REPAIR deep.
//
// BFME differences: there is no empty isKindOf(KINDOF_BRIDGE) block, and
// findObjectByID is the out-of-line BFME1 GameLogic lookup (ILT 0x0001F253),
// so GameLogic stays declaration-only here instead of using Zero Hour's inline
// vector lookup.
//
// Layout: Object id +0x74 and body module +0x200; body module getDamageState
// slot 8 (+0x20); AIPlayer repair queue +0x48 and queued count +0x60.

#define NULL 0

#include "../../../Include/Common/ObjectID.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
#include "../../../Include/Common/Enums/BodyDamageType.h"

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual BodyDamageType getDamageState() const;	// +0x20
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	char m_unmodelled000[0x74];
	ObjectID m_id;							// +0x74
	char m_unmodelled078[0x200 - 0x78];
	BodyModuleInterface *m_body;					// +0x200
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
enum { MAX_STRUCTURES_TO_REPAIR = 2 };

class AIPlayer
{
public:
	virtual void repairStructure(ObjectID structure);

private:
	char m_unmodelled004[0x48 - 0x04];
	ObjectID m_structuresToRepair[MAX_STRUCTURES_TO_REPAIR];	// +0x48
	char m_unmodelled050[0x60 - 0x50];
	int m_structuresInQueue;					// +0x60
};

// ------------------------------------------------------------------------------------------------
/** Repair a bridge or other structure. */
// ------------------------------------------------------------------------------------------------
void AIPlayer::repairStructure(ObjectID structure)
{
	Object *structureObj = TheGameLogic->findObjectByID(structure);
	if (structureObj==NULL) return;
	if (structureObj->getBodyModule()==NULL) return;
	// If the structure is not noticably damaged, don't bother.
	enum BodyDamageType structureState = structureObj->getBodyModule()->getDamageState();
	if (structureState==BODY_PRISTINE) {
		return;
	}
	int i;
	for (i=0; i<m_structuresInQueue; i++) {
		if (m_structuresToRepair[i] == structureObj->getID()) {
			return;
		}
	}
	if (m_structuresInQueue==MAX_STRUCTURES_TO_REPAIR) {
		return;
	}
	m_structuresToRepair[m_structuresInQueue] = structureObj->getID();
	m_structuresInQueue++;
}
