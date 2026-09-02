// cl: /O2 /Ob0
// stlport

#include <list>

class Drawable;
typedef _STL::list<Drawable *> DrawableList;

class Object
{
public:
	char m_padding[0x74];
	unsigned int m_id;
};

class Drawable
{
public:
	char m_padding[0xFC];
	Object *m_object;
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	bool m_air;
	char m_pad03[3];
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	char m_unmodelled[0x10];
};

class GameMessage
{
public:
	enum Type
	{
		MSG_EVACUATE = 0x41F,
		MSG_DOCK = 0x42C,
		MSG_ENTER = 0x42B
	};

	void appendObjectIDArgument(unsigned int id);
};

#define RVA005AD9C0_SLOT(n) virtual void slot##n();
class InGameUI
{
public:
	RVA005AD9C0_SLOT(00) RVA005AD9C0_SLOT(01) RVA005AD9C0_SLOT(02)
	RVA005AD9C0_SLOT(03) RVA005AD9C0_SLOT(04) RVA005AD9C0_SLOT(05)
	RVA005AD9C0_SLOT(06) RVA005AD9C0_SLOT(07) RVA005AD9C0_SLOT(08)
	RVA005AD9C0_SLOT(09) RVA005AD9C0_SLOT(10) RVA005AD9C0_SLOT(11)
	RVA005AD9C0_SLOT(12) RVA005AD9C0_SLOT(13) RVA005AD9C0_SLOT(14)
	RVA005AD9C0_SLOT(15) RVA005AD9C0_SLOT(16) RVA005AD9C0_SLOT(17)
	RVA005AD9C0_SLOT(18) RVA005AD9C0_SLOT(19) RVA005AD9C0_SLOT(20)
	RVA005AD9C0_SLOT(21) RVA005AD9C0_SLOT(22) RVA005AD9C0_SLOT(23)
	RVA005AD9C0_SLOT(24) RVA005AD9C0_SLOT(25) RVA005AD9C0_SLOT(26)
	RVA005AD9C0_SLOT(27) RVA005AD9C0_SLOT(28) RVA005AD9C0_SLOT(29)
	RVA005AD9C0_SLOT(30) RVA005AD9C0_SLOT(31) RVA005AD9C0_SLOT(32)
	RVA005AD9C0_SLOT(33) RVA005AD9C0_SLOT(34) RVA005AD9C0_SLOT(35)
	RVA005AD9C0_SLOT(36) RVA005AD9C0_SLOT(37) RVA005AD9C0_SLOT(38)
	RVA005AD9C0_SLOT(39) RVA005AD9C0_SLOT(40) RVA005AD9C0_SLOT(41)
	RVA005AD9C0_SLOT(42) RVA005AD9C0_SLOT(43) RVA005AD9C0_SLOT(44)
	RVA005AD9C0_SLOT(45) RVA005AD9C0_SLOT(46) RVA005AD9C0_SLOT(47)
	RVA005AD9C0_SLOT(48) RVA005AD9C0_SLOT(49) RVA005AD9C0_SLOT(50)
	RVA005AD9C0_SLOT(51) RVA005AD9C0_SLOT(52) RVA005AD9C0_SLOT(53)
	RVA005AD9C0_SLOT(54) RVA005AD9C0_SLOT(55) RVA005AD9C0_SLOT(56)
	RVA005AD9C0_SLOT(57) RVA005AD9C0_SLOT(58) RVA005AD9C0_SLOT(59)
	RVA005AD9C0_SLOT(60) RVA005AD9C0_SLOT(61) RVA005AD9C0_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables();
};
#undef RVA005AD9C0_SLOT

#define RVA005AD9C0_STREAM_SLOT(n) virtual void streamSlot##n();
class MessageStream
{
public:
	RVA005AD9C0_STREAM_SLOT(00) RVA005AD9C0_STREAM_SLOT(01)
	RVA005AD9C0_STREAM_SLOT(02) RVA005AD9C0_STREAM_SLOT(03)
	RVA005AD9C0_STREAM_SLOT(04) RVA005AD9C0_STREAM_SLOT(05)
	RVA005AD9C0_STREAM_SLOT(06) RVA005AD9C0_STREAM_SLOT(07)
	RVA005AD9C0_STREAM_SLOT(08) RVA005AD9C0_STREAM_SLOT(09)
	RVA005AD9C0_STREAM_SLOT(10) RVA005AD9C0_STREAM_SLOT(11)
	RVA005AD9C0_STREAM_SLOT(12)
	virtual GameMessage *appendMessage(GameMessage::Type type);
};
#undef RVA005AD9C0_STREAM_SLOT

extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type type,
	PickAndPlayInfo *info);

class CommandTranslator
{
public:
	int createEvacuateMessage(Drawable *target, int commandType);
	int createEnterMessage(Drawable *enter, int commandType);
	int createDockMessage(Drawable *target, int commandType);

private:
	char m_padding[8];
	bool m_teamExists;
};

int CommandTranslator::createEvacuateMessage(Drawable *target, int commandType)
{
	const GameMessage::Type msgType = GameMessage::MSG_EVACUATE;
	if (commandType == 2)
		return msgType;
	if (!target || !target->m_object)
		return 0;
	if (m_teamExists)
	{
		PickAndPlayInfo info;
		info.m_drawTarget = target;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),
			msgType, &info);
		GameMessage *message = TheMessageStream->appendMessage(msgType);
		message->appendObjectIDArgument(target->m_object->m_id);
	}
	return msgType;
}

int CommandTranslator::createEnterMessage(Drawable *enter, int commandType)
{
	const GameMessage::Type msgType = GameMessage::MSG_ENTER;
	if (commandType == 2)
		return msgType;
	if (!enter || !enter->m_object)
		return 0;
	if (m_teamExists)
	{
		PickAndPlayInfo info;
		info.m_drawTarget = enter;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),
			msgType, &info);
		GameMessage *message = TheMessageStream->appendMessage(msgType);
		message->appendObjectIDArgument(0);
		message->appendObjectIDArgument(enter->m_object->m_id);
	}
	return msgType;
}

int CommandTranslator::createDockMessage(Drawable *target, int commandType)
{
	const GameMessage::Type msgType = GameMessage::MSG_DOCK;
	if (commandType == 2)
		return msgType;
	if (!target || !target->m_object)
		return 0;
	if (m_teamExists)
	{
		PickAndPlayInfo info;
		info.m_drawTarget = target;
		pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),
			msgType, &info);
		GameMessage *message = TheMessageStream->appendMessage(msgType);
		message->appendObjectIDArgument(target->m_object->m_id);
	}
	return msgType;
}
