// cl: /O2 /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>

#include "../../../Include/Common/ScalarTypes.h"



#include "../../../../Libraries/Include/Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
enum KindOfType { KINDOF_INVALID = 0 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS bool isUsingAirborneLocomotor() const;
#include "../../GameLogic/Object/object.h"

class Drawable
{
public:
	unsigned char m_padding[0xFC];
	Object *m_object;
};

#include "../../Common/System/message_stream.h"

typedef _STL::list<Drawable *> DrawableList;

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;
#undef BFME_UI_SLOT

	unsigned char m_pad004[0x12AC];
	unsigned char m_waypointMode;
	unsigned char m_forceAttackMode;
	unsigned char m_forceMoveMode;
};

class MessageStream
{
public:
#define BFME_MESSAGE_SLOT(n) virtual void slot##n() = 0;
	BFME_MESSAGE_SLOT(00) BFME_MESSAGE_SLOT(01) BFME_MESSAGE_SLOT(02)
	BFME_MESSAGE_SLOT(03) BFME_MESSAGE_SLOT(04) BFME_MESSAGE_SLOT(05)
	BFME_MESSAGE_SLOT(06) BFME_MESSAGE_SLOT(07) BFME_MESSAGE_SLOT(08)
	BFME_MESSAGE_SLOT(09) BFME_MESSAGE_SLOT(10) BFME_MESSAGE_SLOT(11)
	BFME_MESSAGE_SLOT(12)
	virtual GameMessage *appendMessage(GameMessage::Type type);
#undef BFME_MESSAGE_SLOT
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	char m_pad03[3];
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	Int m_specialPowerType;
	Coord3D m_position;
	UnsignedInt m_commandButton;
};

class StatsCollector
{
public:
	char m_padding[0x10];
	UnsignedInt m_moveCommands;
	UnsignedInt m_attackCommands;
};

extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
extern StatsCollector *TheStatsCollector;
extern bool pickAndPlayUnitVoiceResponse(const DrawableList *list,
	GameMessage::Type messageType, PickAndPlayInfo *info);

class BFMERopeDrawableGetPositionShim
{
public:
    const Coord3D *get() const;
};
struct RGBColor;
class Rva0041A2E0
{
public:
    void flash(const RGBColor *);
};
struct Rva005A9BD0Holder;
int __stdcall rva005A9BD0(Rva005A9BD0Holder *, Rva005A9BD0Holder *, int);

class Rva005ACD40CommandTranslator
{
public:
    enum CommandEvaluateType { DO_COMMAND, DO_HINT, EVALUATE_ONLY };
    GameMessage::Type issueAttackCommand(Drawable *target, const Coord3D *pos,
        CommandEvaluateType commandType, int command);
private:
    char m_padding[8];
    Bool m_teamExists;
};

//------------------------------------------------------------------------------------
/**
 * Create DO_ATTACK_GROUND_OBJECT messages for each selected object, instructing it to attack the given enemy.
 * Return TRUE if any attacks actually occurred.
 */
// ?issueAttackCommand@Rva005ACD40CommandTranslator@@QAE?AW4Type@GameMessage@@PAVDrawable@@PBUCoord3D@@W4CommandEvaluateType@1@H@Z
GameMessage::Type Rva005ACD40CommandTranslator::issueAttackCommand(Drawable *target, const Coord3D *pos,
    CommandEvaluateType commandType, int command)
{
    GameMessage::Type msgType = (GameMessage::Type)0;
    if (target == 0)
        return msgType;

    // you cannot attack an enemy that has no object representation
    Object *targetObj = target->m_object;
    if (!targetObj)
        return msgType;

    if (m_teamExists)
    {
        //DEBUG_LOG(("issuing team-attack cmd against %s\n",enemy->getTemplate()->getName().str()));
        // insert team attack command message into stream
        switch (command)
        {
        case 0:
            msgType = (GameMessage::Type)0x424;
            break;
        default:
            //DEBUG_ASSERTCRASH( 0, ("issueAttackCommand was passed in a GUICommandType type that isn't supported yet...") );
            return msgType;
        }
        // only create the message if our command type is DO_COMMAND
        if (commandType == DO_COMMAND)
        {
            GameMessage *attackMsg;
            attackMsg = TheMessageStream->appendMessage(msgType);
            Coord3D location = {0.0f, 0.0f, 0.0f};
            if (pos)
                location = *pos;
            attackMsg->appendObjectIDArgument(targetObj->m_id); // must pass target object ID to logic
            attackMsg->appendLocationArgument(location);
            Drawable *flashTarget = target;
            Object *containedBy = targetObj->m_containedBy;
            if (containedBy && containedBy->isKindOf((KindOfType)0x6c))
                flashTarget = containedBy->getDrawable();
            if (flashTarget)
                ((Rva0041A2E0 *)flashTarget)->flash(0);
            // if we have a stats collector, inrement the stats
            if (TheStatsCollector)
                ++TheStatsCollector->m_attackCommands;
        }  // end if
    }
    else
    {
        //DEBUG_LOG(("issuing NON-team-attack cmd against %s\n",target->getTemplate()->getName().str()));
        // send single attack command for selected drawable
        const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
        // loop through all the selected drawables
        Drawable *draw;
        for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
        {
            draw = *it;
            union AttackCall
            {
                int (__stdcall *function)(Rva005A9BD0Holder *, Rva005A9BD0Holder *, int);
                int (Rva005ACD40CommandTranslator::*member)(Drawable *, Drawable *, CommandEvaluateType);
            } call;
            call.function = rva005A9BD0;
            msgType = (GameMessage::Type)(this->*call.member)(draw, target, commandType);
        }
    }
    // only make sounds if the command was for real
    if (commandType == DO_COMMAND)
    {
        PickAndPlayInfo info;
        info.m_air = targetObj->isUsingAirborneLocomotor();
        info.m_drawTarget = target;
        if (pos)
            info.m_position = *pos;
        else
            info.m_position = *((BFMERopeDrawableGetPositionShim *)target)->get();
        pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
    }  // end if
    // return the actual message type created
    return msgType;
}
