// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
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

struct ICoord2D;

class Object;

class Drawable
{
public:
	Object *getObject()
	{
		return *(Object **)((char *)this + 0xFC);
	}
};

class GameMessage
{
public:
	enum Type
	{
		MSG_DO_ATTACKMOVETO = 0x42F
	};

	void appendLocationArgument(const Coord3D &arg);
};

class CommandButton;

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
	BFME_UI_SLOT(64)
	virtual Drawable *getFirstSelectedDrawable() = 0;
#undef BFME_UI_SLOT
};

class TacticalViewShim
{
public:
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01) BFME_VIEW_SLOT(02) BFME_VIEW_SLOT(03)
	BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05) BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07)
	BFME_VIEW_SLOT(08) BFME_VIEW_SLOT(09) BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13) BFME_VIEW_SLOT(14) BFME_VIEW_SLOT(15)
	BFME_VIEW_SLOT(16) BFME_VIEW_SLOT(17) BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19)
	BFME_VIEW_SLOT(20) BFME_VIEW_SLOT(21) BFME_VIEW_SLOT(22) BFME_VIEW_SLOT(23)
	BFME_VIEW_SLOT(24) BFME_VIEW_SLOT(25) BFME_VIEW_SLOT(26) BFME_VIEW_SLOT(27)
	BFME_VIEW_SLOT(28) BFME_VIEW_SLOT(29) BFME_VIEW_SLOT(30) BFME_VIEW_SLOT(31)
	BFME_VIEW_SLOT(32) BFME_VIEW_SLOT(33) BFME_VIEW_SLOT(34) BFME_VIEW_SLOT(35)
	BFME_VIEW_SLOT(36) BFME_VIEW_SLOT(37) BFME_VIEW_SLOT(38) BFME_VIEW_SLOT(39)
	BFME_VIEW_SLOT(40) BFME_VIEW_SLOT(41) BFME_VIEW_SLOT(42) BFME_VIEW_SLOT(43)
	BFME_VIEW_SLOT(44) BFME_VIEW_SLOT(45) BFME_VIEW_SLOT(46) BFME_VIEW_SLOT(47)
	BFME_VIEW_SLOT(48) BFME_VIEW_SLOT(49) BFME_VIEW_SLOT(50) BFME_VIEW_SLOT(51)
	BFME_VIEW_SLOT(52) BFME_VIEW_SLOT(53) BFME_VIEW_SLOT(54) BFME_VIEW_SLOT(55)
	BFME_VIEW_SLOT(56) BFME_VIEW_SLOT(57) BFME_VIEW_SLOT(58) BFME_VIEW_SLOT(59)
	BFME_VIEW_SLOT(60) BFME_VIEW_SLOT(61) BFME_VIEW_SLOT(62) BFME_VIEW_SLOT(63)
	BFME_VIEW_SLOT(64) BFME_VIEW_SLOT(65) BFME_VIEW_SLOT(66) BFME_VIEW_SLOT(67)
	BFME_VIEW_SLOT(68) BFME_VIEW_SLOT(69) BFME_VIEW_SLOT(70) BFME_VIEW_SLOT(71)
	BFME_VIEW_SLOT(72) BFME_VIEW_SLOT(73) BFME_VIEW_SLOT(74) BFME_VIEW_SLOT(75)
	BFME_VIEW_SLOT(76) BFME_VIEW_SLOT(77) BFME_VIEW_SLOT(78) BFME_VIEW_SLOT(79)
	BFME_VIEW_SLOT(80) BFME_VIEW_SLOT(81) BFME_VIEW_SLOT(82) BFME_VIEW_SLOT(83)
	BFME_VIEW_SLOT(84) BFME_VIEW_SLOT(85) BFME_VIEW_SLOT(86) BFME_VIEW_SLOT(87)
	BFME_VIEW_SLOT(88)
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, Bool clamp) = 0;
#undef BFME_VIEW_SLOT
};

class BfmeMessageStream
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
extern TacticalViewShim *TheTacticalView;
extern BfmeMessageStream *TheMessageStream;

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	Int m_specialPowerType;
	Coord3D m_position;
	UnsignedInt m_commandButton;
};

void pickAndPlayUnitVoiceResponse(const _STL::list<Drawable *> *list,
	GameMessage::Type messageType, PickAndPlayInfo *info);

enum CommandStatus
{
	COMMAND_INCOMPLETE = 0,
	COMMAND_COMPLETE
};

static CommandStatus doAttackMoveCommand(const CommandButton *command, const ICoord2D *mouse)
{
	if (command == NULL || mouse == NULL)
		return COMMAND_COMPLETE;

	Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
	if (draw == NULL || draw->getObject() == NULL)
		return COMMAND_COMPLETE;

	Coord3D world;
	TheTacticalView->screenToTerrain(mouse, &world, false);

	GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x42F);
	msg->appendLocationArgument(world);

	PickAndPlayInfo info;
	info.m_position = world;
	pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),
		(GameMessage::Type)0x42F, &info);

	return COMMAND_COMPLETE;
}

CommandStatus BFME_DoAttackMoveCommand(const CommandButton *command, const ICoord2D *mouse)
{
	return doAttackMoveCommand(command, mouse);
}
