// cl: /O2 /Ob0
// stlport

#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_padding[0x74];
	UnsignedInt m_id;
};

class Drawable
{
public:
	char m_padding[0xFC];
	Object *m_object;
};

class CommandButton
{
public:
	char m_padding[0x18];
	UnsignedInt m_options;

	Bool isValidObjectTarget(const Drawable *source, const Drawable *target) const;
};

typedef _STL::list<Drawable *> DrawableList;

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	char m_pad03[3];
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	Coord3D m_position;
	UnsignedInt m_commandButton;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_COMBATDROP_AT_LOCATION = 0x420,
		MSG_COMBATDROP_AT_OBJECT = 0x421
	};

	void appendObjectIDArgument(UnsignedInt arg);
	void appendLocationArgument(const Coord3D &arg);
};

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
	virtual const DrawableList *getAllSelectedLocalDrawables() = 0;
	virtual Drawable *getFirstSelectedDrawable() = 0;
#undef BFME_UI_SLOT
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

extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type,
	PickAndPlayInfo *info);

class Rva005AD330CommandTranslator
{
public:
	enum CommandEvaluateType
	{
		DO_COMMAND = 0,
		DO_HINT = 1,
		EVALUATE_ONLY = 2
	};

	GameMessage::Type issueCombatDropCommand(const CommandButton *command,
		CommandEvaluateType commandType, Drawable *target, const Coord3D *pos);
};

GameMessage::Type Rva005AD330CommandTranslator::issueCombatDropCommand(const CommandButton *command,
	CommandEvaluateType commandType, Drawable *target, const Coord3D *pos)
{
	if (!command)
		return (GameMessage::Type)0;

	if (target != NULL && (command->m_options & 7) != 0)
	{
		if (!command->isValidObjectTarget(TheInGameUI->getFirstSelectedDrawable(), target))
			return (GameMessage::Type)0;

		GameMessage::Type msgType = GameMessage::MSG_COMBATDROP_AT_OBJECT;
		if (commandType == DO_COMMAND)
		{
			GameMessage *msg = TheMessageStream->appendMessage(msgType);
			UnsignedInt targetID = (target && target->m_object) ? target->m_object->m_id : 0;
			msg->appendObjectIDArgument(targetID);

			PickAndPlayInfo info;
			info.m_drawTarget = target;
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
		}
		return msgType;
	}
	else if ((command->m_options & 0x20) != 0)
	{
		GameMessage::Type msgType = GameMessage::MSG_COMBATDROP_AT_LOCATION;
		if (commandType == DO_COMMAND)
		{
			GameMessage *msg = TheMessageStream->appendMessage(msgType);
			msg->appendLocationArgument(*pos);

			PickAndPlayInfo info;
			info.m_position = *pos;
			pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), msgType, &info);
		}
		return msgType;
	}

	return (GameMessage::Type)0;
}
