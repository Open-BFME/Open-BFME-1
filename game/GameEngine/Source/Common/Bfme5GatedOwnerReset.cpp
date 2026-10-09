#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

#include "../GameLogic/command_source_type.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_RESET = 0x49
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

struct BfmeAIHolder
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeCommands;
};

class BfmeRelationInterface
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void bfmeReset(int value);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmePrepare(int value);
	// The ILT at 0x00031F7A this call encodes was re-adjudicated in 49a76649f: it
	// fronts 0x00162CD0, which builds an 86-bit ObjectStatusMaskType, so the member
	// is Object::clearStatus(ObjectStatusTypes) -- not clearModelConditionState.
	void clearStatus(ObjectStatusTypes condition);
	void setSingleModelCondition(int value);

	char m_bfmeFields[0x204];
	BfmeAIHolder *m_bfmeAI;
};

// ILT 0x0000B3E3 -> 0x001BFE40, matched as RvaC4390First::getInterface.
struct RvaC4390Interface;
class RvaC4390First
{
public:
	RvaC4390Interface *getInterface(void);
};

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(int id);
};

// retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  Only the symbol name
// matters here; GameLogicFrameSlice is this TU's view of the pointee.
class GameLogic;
extern GameLogic *TheGameLogic;

static inline GameLogicFrameSlice *theGameLogic()
{
	return (GameLogicFrameSlice *)TheGameLogic;
}

class Gen_002875C0
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual bool bfmeAccept(Object *object);

	void bfmeRun(void);

private:
	int m_bfmeObjectID;
	char m_bfme08[4];
	int m_bfmeState;
};

// ?bfmeRun@Gen_002875C0@@QAEXXZ
void Gen_002875C0::bfmeRun(void)
{
	Object *secondary = *reinterpret_cast<Object **>(
		reinterpret_cast<char *>(this) - 0x18);
	Object *object = theGameLogic()->bfmeFind(m_bfmeObjectID);
	if (object != 0) {
		BfmeRelationInterface *relation = (BfmeRelationInterface *)((RvaC4390First *)object)->getInterface();
		if (relation != 0 && bfmeAccept(object)) {
			relation->bfmeReset(0);
			m_bfmeObjectID = 0;
			m_bfmeState = 0;

			secondary->setSingleModelCondition(0x40);
			object->bfmePrepare(0x3F);
			object->clearStatus(OBJECT_STATUS_RESET);
			object->setSingleModelCondition(0x49);
			object->m_bfmeAI->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		}
	}
}

#undef BFME_TEN_VIRTUALS
