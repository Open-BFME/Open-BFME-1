// cl: /O2
// stlport
//
// Retail 0x005ACF80 (746 B, thiscall, ret 0x14): the BFME special-power
// command helper of the command translator family.  It issues message 0x411
// (object target, validated through CommandButton::isValidObjectTarget),
// 0x410 (location) or 0x40F (no target), appends the power ID, options and
// the ignore-selection source, and plays the unit voice response through
// PickAndPlayInfo.  Zero Hour's CommandTranslator::issueSpecialPowerCommand
// is the (weak) twin; five callers reach it only through ILT thunks from the
// unconverted 0x005ADE90 dispatcher, so no caller or vtable proves the real
// name and the owner keeps the address token.
//
// The no-target branch reads the final override inline two levels deep:
// getFinalOverride() inlines one call of the const friend_getFinalOverride(),
// whose own recursion stays out of line (ILT 0x00048C61).

#include <list>

struct Coord3D { float x, y, z; };
class Drawable;

class Object {
public:
#define OBJECT_SLOT(n) virtual void slot##n();
    OBJECT_SLOT(00) OBJECT_SLOT(01) OBJECT_SLOT(02) OBJECT_SLOT(03)
    OBJECT_SLOT(04) OBJECT_SLOT(05) OBJECT_SLOT(06) OBJECT_SLOT(07)
    OBJECT_SLOT(08) OBJECT_SLOT(09)
#undef OBJECT_SLOT
    virtual Drawable *getDrawable();
    char pad04[0x70];
    unsigned m_id;
};

class Drawable {
public:
    char pad00[0xfc];
    Object *m_object;
};

class Overridable {
public:
    void *vtable;
    Overridable *m_nextOverride;
    Overridable *friend_getFinalOverride()
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
    // Call-site walk: one retail inlined level, deeper recursion in the
    // friend_getFinalOverride ILT 0x00048C61.
    const Overridable *finalOverrideViaFriendIf() const
    {
        if (m_nextOverride)
            return m_nextOverride->friend_getFinalOverride();
        return this;
    }
};

enum SpecialPowerType { SPECIAL_INVALID };

class SpecialPowerTemplate : public Overridable {
public:
    unsigned getID() const;
    SpecialPowerType getSpecialPowerType() const;
    char pad08[8];
    unsigned m_id;
    int m_type;
};

class CommandButton {
public:
    char pad00[0x18];
    unsigned m_options;
    char pad1c[0x18];
    SpecialPowerTemplate *m_specialPower;
    bool isValidObjectTarget(const Drawable *, const Drawable *) const;
};

class GameMessage {
public:
    enum Type { MSG_SPECIAL = 0x40f, MSG_SPECIAL_LOCATION = 0x410, MSG_SPECIAL_OBJECT = 0x411 };
    void appendIntegerArgument(int);
    void appendObjectIDArgument(unsigned);
    void appendLocationArgument(const Coord3D &);
};

class MessageStream {
public:
#define MESSAGE_SLOT(n) virtual void slot##n();
    MESSAGE_SLOT(00) MESSAGE_SLOT(01) MESSAGE_SLOT(02) MESSAGE_SLOT(03)
    MESSAGE_SLOT(04) MESSAGE_SLOT(05) MESSAGE_SLOT(06) MESSAGE_SLOT(07)
    MESSAGE_SLOT(08) MESSAGE_SLOT(09) MESSAGE_SLOT(10) MESSAGE_SLOT(11)
    MESSAGE_SLOT(12)
#undef MESSAGE_SLOT
    virtual GameMessage *appendMessage(GameMessage::Type);
};

typedef _STL::list<Drawable *> DrawableList;
class InGameUI {
public:
#define UI_SLOT(n) virtual void slot##n();
    UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04)
    UI_SLOT(05) UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09)
    UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14)
    UI_SLOT(15) UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19)
    UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23) UI_SLOT(24)
    UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29)
    UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34)
    UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
    UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44)
    UI_SLOT(45) UI_SLOT(46) UI_SLOT(47) UI_SLOT(48) UI_SLOT(49)
    UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54)
    UI_SLOT(55) UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59)
    UI_SLOT(60) UI_SLOT(61) UI_SLOT(62)
#undef UI_SLOT
    virtual const DrawableList *getAllSelectedDrawables() const;
    virtual void slot64();
    virtual Drawable *getFirstSelectedDrawable();
};

class PickAndPlayInfo {
public:
    PickAndPlayInfo();
    bool m_air;
    char pad01[3];
    Drawable *m_drawTarget;
    void *m_weaponSlot;
    int m_specialPowerType;
    Coord3D m_position;
    unsigned m_commandButton;
};

extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
bool pickAndPlayUnitVoiceResponse(const DrawableList *, GameMessage::Type, PickAndPlayInfo *);

class Rva005ACF80Owner {
public:
    enum CommandEvaluateType { DO_COMMAND, DO_HINT, EVALUATE_ONLY };
    GameMessage::Type issueSpecialPower(const CommandButton *command, CommandEvaluateType commandType,
        Drawable *target, const Coord3D *pos, Object *ignoreSelObj);
};

GameMessage::Type Rva005ACF80Owner::issueSpecialPower(const CommandButton *command,
    CommandEvaluateType commandType, Drawable *target, const Coord3D *pos, Object *ignoreSelObj)
{
    GameMessage::Type msgType = (GameMessage::Type)0;
    if (!command || !command->m_specialPower)
        return msgType;

    Drawable *sourceDraw = ignoreSelObj ? ignoreSelObj->getDrawable() : TheInGameUI->getFirstSelectedDrawable();
    unsigned specificSource = ignoreSelObj ? ignoreSelObj->m_id : 0;

    if ((command->m_options & 7) && target) {
        if (!command->isValidObjectTarget(sourceDraw, target))
            return (GameMessage::Type)0;
        msgType = GameMessage::MSG_SPECIAL_OBJECT;
        if (commandType == DO_COMMAND) {
            GameMessage *msg = TheMessageStream->appendMessage(msgType);
            msg->appendIntegerArgument(command->m_specialPower->getID());
            msg->appendObjectIDArgument(target->m_object->m_id);
            msg->appendIntegerArgument(command->m_options);
            msg->appendObjectIDArgument(specificSource);
            msg->appendLocationArgument(*pos);
            PickAndPlayInfo info;
            info.m_drawTarget = target;
            info.m_specialPowerType = command->m_specialPower->getSpecialPowerType();
            info.m_position = *pos;
            pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
        }
    } else if ((command->m_options & 0x20) && pos) {
        msgType = GameMessage::MSG_SPECIAL_LOCATION;
        if (commandType == DO_COMMAND) {
            GameMessage *msg = TheMessageStream->appendMessage(msgType);
            msg->appendIntegerArgument(command->m_specialPower->getID());
            msg->appendLocationArgument(*pos);
            msg->appendObjectIDArgument(target && target->m_object ? target->m_object->m_id : 0);
            msg->appendIntegerArgument(command->m_options);
            msg->appendObjectIDArgument(specificSource);
            PickAndPlayInfo info;
            info.m_drawTarget = target;
            info.m_specialPowerType = command->m_specialPower->getSpecialPowerType();
            info.m_position = *pos;
            pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
        }
    } else {
        msgType = GameMessage::MSG_SPECIAL;
        if (commandType == DO_COMMAND) {
            GameMessage *msg = TheMessageStream->appendMessage(msgType);
            SpecialPowerTemplate *power = (SpecialPowerTemplate *)command->m_specialPower->finalOverrideViaFriendIf();
            msg->appendIntegerArgument(power->m_id);
            msg->appendIntegerArgument(command->m_options);
            msg->appendObjectIDArgument(specificSource);
            PickAndPlayInfo info;
            info.m_drawTarget = target;
            power = (SpecialPowerTemplate *)command->m_specialPower->finalOverrideViaFriendIf();
            info.m_specialPowerType = power->m_type;
            pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
        }
    }
    return msgType;
}
