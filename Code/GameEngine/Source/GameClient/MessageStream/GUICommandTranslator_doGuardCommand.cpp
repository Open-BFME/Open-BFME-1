// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// doGuardCommand (retail 0x005B1A80): Zero Hour GUICommandTranslator.cpp twin; the
// caller at 0x005B2077/0x005B2088/0x005B2099 passes GUARDMODE 0/1/2 and &mouse beside
// the doAttackMoveCommand (0x005B17E0) call. BFME adds PickAndPlayInfo to the voice call.

#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/MessageStream.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"
#include "GameClient/InGameUI.h"

class GuardTargetObject
{
public:
#define GUARD_OBJECT_SLOT(n) virtual void slot##n() = 0;
	GUARD_OBJECT_SLOT(00) GUARD_OBJECT_SLOT(01) GUARD_OBJECT_SLOT(02)
	GUARD_OBJECT_SLOT(03) GUARD_OBJECT_SLOT(04) GUARD_OBJECT_SLOT(05)
	GUARD_OBJECT_SLOT(06) GUARD_OBJECT_SLOT(07) GUARD_OBJECT_SLOT(08)
	GUARD_OBJECT_SLOT(09)
	virtual Drawable *getDrawable() const = 0;
#undef GUARD_OBJECT_SLOT

	UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}
};

static Object *validUnderCursor(const ICoord2D *mouse, const CommandButton *command, PickType pickType)
{
	Object *pickObj = NULL;
	Drawable *pick = TheTacticalView->pickDrawable(mouse, FALSE, pickType);

	Object *pickedObject = pick ? *reinterpret_cast<Object **>(reinterpret_cast<char *>(pick) + 0xFC) : NULL;
	if (pickedObject) {
		Player *player = ThePlayerList->getLocalPlayer();
		pickObj = pickedObject;
		if (!command->isValidObjectTarget(player, pickObj))
			pickObj = NULL;
	}

	return pickObj;
}

typedef _STL::list<Drawable *> GuardDrawableList;

class GuardTacticalView
{
public:
#define GUARD_VIEW_SLOT(n) virtual void slot##n() = 0;
	GUARD_VIEW_SLOT(00) GUARD_VIEW_SLOT(01) GUARD_VIEW_SLOT(02) GUARD_VIEW_SLOT(03)
	GUARD_VIEW_SLOT(04) GUARD_VIEW_SLOT(05) GUARD_VIEW_SLOT(06) GUARD_VIEW_SLOT(07)
	GUARD_VIEW_SLOT(08) GUARD_VIEW_SLOT(09) GUARD_VIEW_SLOT(10) GUARD_VIEW_SLOT(11)
	GUARD_VIEW_SLOT(12) GUARD_VIEW_SLOT(13) GUARD_VIEW_SLOT(14) GUARD_VIEW_SLOT(15)
	GUARD_VIEW_SLOT(16) GUARD_VIEW_SLOT(17) GUARD_VIEW_SLOT(18) GUARD_VIEW_SLOT(19)
	GUARD_VIEW_SLOT(20) GUARD_VIEW_SLOT(21) GUARD_VIEW_SLOT(22) GUARD_VIEW_SLOT(23)
	GUARD_VIEW_SLOT(24) GUARD_VIEW_SLOT(25) GUARD_VIEW_SLOT(26) GUARD_VIEW_SLOT(27)
	GUARD_VIEW_SLOT(28) GUARD_VIEW_SLOT(29) GUARD_VIEW_SLOT(30) GUARD_VIEW_SLOT(31)
	GUARD_VIEW_SLOT(32) GUARD_VIEW_SLOT(33) GUARD_VIEW_SLOT(34) GUARD_VIEW_SLOT(35)
	GUARD_VIEW_SLOT(36) GUARD_VIEW_SLOT(37) GUARD_VIEW_SLOT(38) GUARD_VIEW_SLOT(39)
	GUARD_VIEW_SLOT(40) GUARD_VIEW_SLOT(41) GUARD_VIEW_SLOT(42) GUARD_VIEW_SLOT(43)
	GUARD_VIEW_SLOT(44) GUARD_VIEW_SLOT(45) GUARD_VIEW_SLOT(46) GUARD_VIEW_SLOT(47)
	GUARD_VIEW_SLOT(48) GUARD_VIEW_SLOT(49) GUARD_VIEW_SLOT(50) GUARD_VIEW_SLOT(51)
	GUARD_VIEW_SLOT(52) GUARD_VIEW_SLOT(53) GUARD_VIEW_SLOT(54) GUARD_VIEW_SLOT(55)
	GUARD_VIEW_SLOT(56) GUARD_VIEW_SLOT(57) GUARD_VIEW_SLOT(58) GUARD_VIEW_SLOT(59)
	GUARD_VIEW_SLOT(60) GUARD_VIEW_SLOT(61) GUARD_VIEW_SLOT(62) GUARD_VIEW_SLOT(63)
	GUARD_VIEW_SLOT(64) GUARD_VIEW_SLOT(65) GUARD_VIEW_SLOT(66) GUARD_VIEW_SLOT(67)
	GUARD_VIEW_SLOT(68) GUARD_VIEW_SLOT(69) GUARD_VIEW_SLOT(70) GUARD_VIEW_SLOT(71)
	GUARD_VIEW_SLOT(72) GUARD_VIEW_SLOT(73) GUARD_VIEW_SLOT(74) GUARD_VIEW_SLOT(75)
	GUARD_VIEW_SLOT(76) GUARD_VIEW_SLOT(77) GUARD_VIEW_SLOT(78) GUARD_VIEW_SLOT(79)
	GUARD_VIEW_SLOT(80) GUARD_VIEW_SLOT(81) GUARD_VIEW_SLOT(82) GUARD_VIEW_SLOT(83)
	GUARD_VIEW_SLOT(84) GUARD_VIEW_SLOT(85) GUARD_VIEW_SLOT(86) GUARD_VIEW_SLOT(87)
	GUARD_VIEW_SLOT(88)
	virtual void screenToTerrain(const ICoord2D *, Coord3D *, Bool) = 0;
#undef GUARD_VIEW_SLOT
};

class GuardCommandButton
{
public:
	char m_padding00[0x18];
	UnsignedInt m_options;

	UnsignedInt getOptions() const
	{
		return m_options;
	}
};

class GuardObject
{
public:
	Coord3D *getPosition()
	{
		return (Coord3D *)((char *)this + 0x38);
	}
};

class GuardDrawable
{
public:
	char m_padding[0xFC];
	GuardObject *m_object;

	GuardObject *getObject()
	{
		return m_object;
	}
};

class GuardInGameUI
{
public:
#define GUARD_UI_SLOT(n) virtual void slot##n() = 0;
	GUARD_UI_SLOT(00) GUARD_UI_SLOT(01) GUARD_UI_SLOT(02) GUARD_UI_SLOT(03)
	GUARD_UI_SLOT(04) GUARD_UI_SLOT(05) GUARD_UI_SLOT(06) GUARD_UI_SLOT(07)
	GUARD_UI_SLOT(08) GUARD_UI_SLOT(09) GUARD_UI_SLOT(10) GUARD_UI_SLOT(11)
	GUARD_UI_SLOT(12) GUARD_UI_SLOT(13) GUARD_UI_SLOT(14) GUARD_UI_SLOT(15)
	GUARD_UI_SLOT(16) GUARD_UI_SLOT(17) GUARD_UI_SLOT(18) GUARD_UI_SLOT(19)
	GUARD_UI_SLOT(20) GUARD_UI_SLOT(21) GUARD_UI_SLOT(22) GUARD_UI_SLOT(23)
	GUARD_UI_SLOT(24) GUARD_UI_SLOT(25) GUARD_UI_SLOT(26) GUARD_UI_SLOT(27)
	GUARD_UI_SLOT(28) GUARD_UI_SLOT(29) GUARD_UI_SLOT(30) GUARD_UI_SLOT(31)
	GUARD_UI_SLOT(32) GUARD_UI_SLOT(33) GUARD_UI_SLOT(34) GUARD_UI_SLOT(35)
	GUARD_UI_SLOT(36) GUARD_UI_SLOT(37) GUARD_UI_SLOT(38) GUARD_UI_SLOT(39)
	GUARD_UI_SLOT(40) GUARD_UI_SLOT(41) GUARD_UI_SLOT(42) GUARD_UI_SLOT(43)
	GUARD_UI_SLOT(44) GUARD_UI_SLOT(45) GUARD_UI_SLOT(46) GUARD_UI_SLOT(47)
	GUARD_UI_SLOT(48) GUARD_UI_SLOT(49) GUARD_UI_SLOT(50) GUARD_UI_SLOT(51)
	GUARD_UI_SLOT(52) GUARD_UI_SLOT(53) GUARD_UI_SLOT(54) GUARD_UI_SLOT(55)
	GUARD_UI_SLOT(56) GUARD_UI_SLOT(57) GUARD_UI_SLOT(58) GUARD_UI_SLOT(59)
	virtual Int getSelectCount() = 0;
	GUARD_UI_SLOT(61) GUARD_UI_SLOT(62)
	virtual const GuardDrawableList *getAllSelectedDrawables() const = 0;
	GUARD_UI_SLOT(64)
	virtual GuardDrawable *getFirstSelectedDrawable() = 0;
#undef GUARD_UI_SLOT
};

class GuardMessageStream
{
public:
#define GUARD_MESSAGE_SLOT(n) virtual void slot##n() = 0;
	GUARD_MESSAGE_SLOT(00) GUARD_MESSAGE_SLOT(01) GUARD_MESSAGE_SLOT(02)
	GUARD_MESSAGE_SLOT(03) GUARD_MESSAGE_SLOT(04) GUARD_MESSAGE_SLOT(05)
	GUARD_MESSAGE_SLOT(06) GUARD_MESSAGE_SLOT(07) GUARD_MESSAGE_SLOT(08)
	GUARD_MESSAGE_SLOT(09) GUARD_MESSAGE_SLOT(10) GUARD_MESSAGE_SLOT(11)
	GUARD_MESSAGE_SLOT(12)
	virtual GameMessage *appendMessage(GameMessage::Type);
#undef GUARD_MESSAGE_SLOT
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	char m_padding01[3];
	Drawable *m_drawTarget;
	int *m_weaponSlot;
	int m_specialPowerType;
	Coord3D m_position;
	void *m_field1c;
};

enum CommandStatus
{
	COMMAND_INCOMPLETE = 0,
	COMMAND_COMPLETE
};

extern Bool pickAndPlayUnitVoiceResponse(const GuardDrawableList *,
	GameMessage::Type, PickAndPlayInfo *);

#define GuardTheTacticalView (reinterpret_cast<GuardTacticalView *>(TheTacticalView))
#define GuardTheInGameUI (reinterpret_cast<GuardInGameUI *>(TheInGameUI))
#define GuardTheMessageStream (reinterpret_cast<GuardMessageStream *>(TheMessageStream))

static CommandStatus doGuardCommand(const CommandButton *command,
	GuardMode guardMode, const ICoord2D *mouse)
{
	if (command == NULL || mouse == NULL)
		return COMMAND_COMPLETE;

	if (GuardTheInGameUI->getSelectCount() == 0)
		return COMMAND_COMPLETE;

	GameMessage *msg = NULL;
	const GuardCommandButton *guardCommand =
		(const GuardCommandButton *)command;
	if (msg == NULL && (guardCommand->getOptions() & 7))
	{
		GuardTargetObject *target = reinterpret_cast<GuardTargetObject *>(
			validUnderCursor(mouse, command, PICK_TYPE_SELECTABLE));
		if (target)
		{
			msg = GuardTheMessageStream->appendMessage(
				(GameMessage::Type)0x433);
			msg->appendObjectIDArgument((ObjectID)target->getID());
			msg->appendIntegerArgument((Int)guardMode);
			PickAndPlayInfo info;
			info.m_drawTarget = target->getDrawable();
			pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),
				(GameMessage::Type)0x433, &info);
		}
	}

	if (msg == NULL)
	{
		Coord3D world;
		if (guardCommand->getOptions() & 0x20)
		{
			GuardTheTacticalView->screenToTerrain(mouse, &world, FALSE);
		}
		else
		{
			GuardDrawable *draw = GuardTheInGameUI->getFirstSelectedDrawable();
			if (draw == NULL || draw->getObject() == NULL)
				return COMMAND_COMPLETE;
			world = *draw->getObject()->getPosition();
		}

		msg = GuardTheMessageStream->appendMessage(
			(GameMessage::Type)0x432);
		msg->appendLocationArgument(world);
		msg->appendIntegerArgument((Int)guardMode);
		PickAndPlayInfo info;
		info.m_position = world;
		pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),
			(GameMessage::Type)0x432, &info);
	}

	return COMMAND_COMPLETE;
}

CommandStatus BFME_DoGuardCommand(const CommandButton *command,
	GuardMode guardMode, const ICoord2D *mouse)
{
	return doGuardCommand(command, guardMode, mouse);
}
