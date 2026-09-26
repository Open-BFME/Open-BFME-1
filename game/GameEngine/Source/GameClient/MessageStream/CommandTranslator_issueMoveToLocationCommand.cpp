// cl: /O2
// stlport

#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

class Object
{
public:
	void *m_vftable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x30];
	Coord3D m_cachedPos;
	unsigned char m_pad44[0x30];
	UnsignedInt m_id;

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}
};

class Drawable
{
public:
	unsigned char m_padding[0xFC];
	Object *m_object;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_DO_MOVETO = 0x42e,
		MSG_DO_ATTACK_OBJECT = 0x424,
		MSG_DO_FORCEMOVETO = 0x430,
		MSG_ADD_WAYPOINT = 0x431
	};

	void appendObjectIDArgument(UnsignedInt id);
	void appendLocationArgument(const Coord3D &location);
};

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
};

extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
extern StatsCollector *TheStatsCollector;
extern void pickAndPlayUnitVoiceResponse(const DrawableList *list,
	GameMessage::Type messageType, PickAndPlayInfo *info);

class CommandTranslator
{
public:
	enum CommandEvaluateType
	{
		DO_COMMAND = 0,
		DO_HINT = 1,
		EVALUATE_ONLY = 2
	};

	GameMessage::Type issueMoveToLocationCommand(const Coord3D *pos,
		Drawable *drawableInWay, CommandEvaluateType commandType);

private:
	char m_padding[8];
	Bool m_teamExists;
};

GameMessage::Type CommandTranslator::issueMoveToLocationCommand(const Coord3D *pos,
	Drawable *drawableInWay, CommandEvaluateType commandType)
{
	GameMessage::Type msgType = (GameMessage::Type)0;
	Object *obj = drawableInWay ? drawableInWay->m_object : 0;

	Bool isForceAttackable = false;
	if (obj)
	{
		ThingTemplate *thing = obj->m_template;
		if (thing && thing->m_nextOverride)
			thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
		isForceAttackable = (thing->m_kindof[2] >> 3) & 1;
	}
	const Coord3D *destination = pos;

	if (m_teamExists)
	{
		if (TheInGameUI->m_waypointMode)
			msgType = GameMessage::MSG_ADD_WAYPOINT;
		else if (TheInGameUI->m_forceMoveMode)
			msgType = GameMessage::MSG_DO_FORCEMOVETO;
		else if (TheInGameUI->m_forceAttackMode && isForceAttackable)
			msgType = GameMessage::MSG_DO_ATTACK_OBJECT;
		else
			msgType = GameMessage::MSG_DO_MOVETO;

		if (commandType == DO_COMMAND)
		{
			GameMessage *movemsg = TheMessageStream->appendMessage(msgType);
			if (msgType == GameMessage::MSG_DO_ATTACK_OBJECT)
				movemsg->appendObjectIDArgument(obj->m_id);
			else
				movemsg->appendLocationArgument(*destination);
		}
	}

	if (commandType == DO_COMMAND)
	{
		PickAndPlayInfo info;
		info.m_drawTarget = drawableInWay;
		if (msgType == GameMessage::MSG_DO_ATTACK_OBJECT)
			info.m_position = *obj->getPosition();
		else
			info.m_position = *destination;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),
			GameMessage::MSG_DO_MOVETO, &info);
	}

	if (TheStatsCollector)
		++TheStatsCollector->m_moveCommands;

	return msgType;
}
