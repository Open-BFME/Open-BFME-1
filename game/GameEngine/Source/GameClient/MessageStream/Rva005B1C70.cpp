// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Gap 005B1C70: padding-proven start; RET4 at 005B20EC; two local switch tables.
// Rva005B18C0 is the direct target at 005B20B6; retail passes command in EAX,
// mouse in ECX, returns CommandStatus in EAX with no stack arguments.
// Its 005B18C0 body independently reads those registers and constructs message 0x412.
// Static helper definitions retain the compiler-private register conventions.
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
	GUARD_UI_SLOT(44) GUARD_UI_SLOT(45) virtual void setCommand(const CommandButton *) = 0; virtual const CommandButton *getCommand() const = 0;
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


class FireWeaponViewShim
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

class FireWeaponCommandButtonShim
{
public:
	char m_padding00[0x18];
	UnsignedInt m_options;
	char m_padding1c[0x50];
	Int m_weaponSlot;
	char m_padding70[0x10];
	Int m_maxShotsToFire;

	UnsignedInt getOptions() const
	{
		return m_options;
	}

	Int getWeaponSlot() const
	{
		return m_weaponSlot;
	}

	Int getMaxShotsToFire() const
	{
		return m_maxShotsToFire;
	}
};

class FireWeaponDrawableShim
{
public:
	char m_padding[0xFC];
	Object *m_object;

	Object *getObject()
	{
		return m_object;
	}
};

class FireWeaponInGameUIShim
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
	virtual Int getSelectCount() = 0;
	BFME_UI_SLOT(61) BFME_UI_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;
	BFME_UI_SLOT(64)
	virtual FireWeaponDrawableShim *getFirstSelectedDrawable() = 0;
#undef BFME_UI_SLOT
};

class FireWeaponMessageStreamShim
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

static CommandStatus doFireWeaponCommand(const CommandButton *command, const ICoord2D *mouse)
{
	if (command == NULL || mouse == NULL)
		return COMMAND_COMPLETE;

	if (reinterpret_cast<FireWeaponInGameUIShim *>(TheInGameUI)->getSelectCount() == 1) {
		FireWeaponDrawableShim *draw =
			reinterpret_cast<FireWeaponInGameUIShim *>(TheInGameUI)->getFirstSelectedDrawable();
		if (draw == NULL || draw->getObject() == NULL)
			return COMMAND_COMPLETE;
	}

	const FireWeaponCommandButtonShim *fireCommand =
		reinterpret_cast<const FireWeaponCommandButtonShim *>(command);
	UnsignedInt options = fireCommand->getOptions();
	if (options & 0x20) {
		Coord3D world;
		reinterpret_cast<FireWeaponViewShim *>(TheTacticalView)->screenToTerrain(mouse, &world, false);
		GameMessage *msg = reinterpret_cast<FireWeaponMessageStreamShim *>(TheMessageStream)->appendMessage((GameMessage::Type)0x40D);
		msg->appendIntegerArgument(fireCommand->getWeaponSlot());
		msg->appendLocationArgument(world);
		msg->appendIntegerArgument(fireCommand->getMaxShotsToFire());
		Object *target = validUnderCursor(mouse, command, PICK_TYPE_SELECTABLE);
		ObjectID targetID = target ? target->getID() : INVALID_ID;
		msg->appendObjectIDArgument(targetID);
	} else if (options & 7) {
		PickType pickType = PICK_TYPE_SELECTABLE;
		if (options & 0x10)
			pickType = (PickType)((Int)pickType | (Int)PICK_TYPE_SHRUBBERY);
		if (options & 0x200000)
			pickType = (PickType)((Int)pickType | 0x200);

		Object *target = validUnderCursor(mouse, command, pickType);
		if (target) {
			GameMessage *msg = reinterpret_cast<FireWeaponMessageStreamShim *>(TheMessageStream)->appendMessage((GameMessage::Type)0x40E);
			msg->appendIntegerArgument(fireCommand->getWeaponSlot());
			msg->appendObjectIDArgument(target->getID());
			msg->appendIntegerArgument(fireCommand->getMaxShotsToFire());
		}
	} else {
		GameMessage *msg = reinterpret_cast<FireWeaponMessageStreamShim *>(TheMessageStream)->appendMessage((GameMessage::Type)0x40C);
		msg->appendIntegerArgument(fireCommand->getWeaponSlot());
		msg->appendIntegerArgument(fireCommand->getMaxShotsToFire());
	}

	return COMMAND_COMPLETE;
}


#include "GameClient/Keyboard.h"
struct Rva005A49E0Point;
class Rva005A49E0RangeTest {
public: bool isBeyondRange(const Rva005A49E0Point *, const Rva005A49E0Point *) const;
};
extern Rva005A49E0RangeTest *Rva00EF4C5C;
class Rva005B5440 { public: void clearFlags(); };
extern Rva005B5440 *Rva00EF4C84;
extern unsigned char *Rva00EED5C8;

static CommandStatus doAttackMoveCommand(const CommandButton *command, const ICoord2D *mouse) {
    if (!command || !mouse) return COMMAND_COMPLETE;
    GuardDrawable *draw = GuardTheInGameUI->getFirstSelectedDrawable();
    if (!draw || !draw->getObject()) return COMMAND_COMPLETE;
    Coord3D world;
    GuardTheTacticalView->screenToTerrain(mouse, &world, false);
    GameMessage *msg = GuardTheMessageStream->appendMessage((GameMessage::Type)0x42F);
    msg->appendLocationArgument(world);
    PickAndPlayInfo info;
    info.m_position = world;
    pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(), (GameMessage::Type)0x42F, &info);
    return COMMAND_COMPLETE;
}
static CommandStatus Rva005B18C0(const CommandButton *command, const ICoord2D *mouse) {
    if (!command || !mouse) return COMMAND_COMPLETE;
    GuardDrawable *draw = GuardTheInGameUI->getFirstSelectedDrawable();
    if (!draw || !draw->getObject()) return COMMAND_COMPLETE;
    Coord3D world;
    GuardTheTacticalView->screenToTerrain(mouse, &world, false);
    GameMessage *msg = GuardTheMessageStream->appendMessage((GameMessage::Type)0x412);
    msg->appendObjectIDArgument((ObjectID)((GuardTargetObject *)draw->getObject())->getID());
    msg->appendLocationArgument(world);
    Bool shift = TheKeyboard->isShift();
    msg->appendBooleanArgument(shift);
    msg->appendObjectIDArgument((ObjectID)0);
    return COMMAND_COMPLETE;
}
static CommandStatus doPlaceBeacon(const CommandButton *command, const ICoord2D *mouse) {
    if (!command || !mouse) return COMMAND_COMPLETE;
    Coord3D world;
    GuardTheTacticalView->screenToTerrain(mouse, &world, false);
    GameMessage *msg = GuardTheMessageStream->appendMessage((GameMessage::Type)0x443);
    msg->appendLocationArgument(world);
    return COMMAND_COMPLETE;
}

// Member layout and enum ordinals are read from this retail body, not ZH.
class Rva005B1C70 {
    void *at000;
    ICoord2D at004, at00C;
    bool at014;
    unsigned at018, at01C;
    ICoord2D at020, at028;
    bool at030;
    unsigned at034, at038;
public:
    int dispatch(const GameMessage *msg);
};

int Rva005B1C70::dispatch(const GameMessage *msg) {
    int disposition = 0;
    int type = *(const int *)((const char *)msg+0x10);
    switch(type) {
    case 4:
        at004 = msg->getArgument(0)->pixel;
        at018 = msg->getArgument(2)->timestamp;
        at014 = false;
        break;
    case 6:
        at00C = msg->getArgument(0)->pixel;
        at01C = msg->getArgument(2)->timestamp;
        break;
    case 14:
        at020 = msg->getArgument(0)->pixel;
        at034 = msg->getArgument(2)->timestamp;
        at030 = false;
        break;
    case 16:
        at028 = msg->getArgument(0)->pixel;
        at038 = msg->getArgument(2)->timestamp;
        break;
    case 3: {
        ICoord2D mouse = msg->getArgument(0)->pixel;
        if (Rva00EF4C5C->isBeyondRange((const Rva005A49E0Point *)&at004,(const Rva005A49E0Point *)&mouse)) at014=true;
        if (Rva00EF4C5C->isBeyondRange((const Rva005A49E0Point *)&at020,(const Rva005A49E0Point *)&mouse)) at030=true;
        break;
    }
    }
    const CommandButton *command = GuardTheInGameUI->getCommand();
    if (!command) return disposition;
    type = *(const int *)((const char *)msg+0x10);
    bool left = (type == 24 || type == 23) && !at014;
    bool right = (type == 28 || type == 27) && !at030;
    bool raw = type == 4;
    bool accept, cancel;
    if (Rva00EED5C8[0x60]) { cancel=left; accept=right; }
    else { cancel=right; accept=left; }
    if (!accept && !cancel && !raw) return disposition;
    if (raw) { disposition=1; }
    else if (cancel) {
        GuardTheInGameUI->setCommand(0);
    } else if (accept) {
        CommandStatus status = COMMAND_COMPLETE;
        const ICoord2D *mouseArg = &msg->getArgument(0)->pixelRegion.hi;
        ICoord2D mouse = *mouseArg;
        Rva00EF4C84->clearFlags();
        if (!command->isContextCommand()) {
            switch (*(const int *)((const char *)command+0x10)) {
            case 22: {
                status=doFireWeaponCommand(command,&mouse);
                PickAndPlayInfo info;
                int slot=*(const int *)((const char *)command+0x6c);
                info.m_weaponSlot=&slot;
                pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)0x40D,&info);
                break;
            }
            case 16: {
                if (*(const unsigned *)((const char *)command+0x18) & 0x20) {
                    Coord3D world;
                    GuardTheTacticalView->screenToTerrain(&mouse,&world,false);
                    GameMessage *message = GuardTheMessageStream->appendMessage((GameMessage::Type)1053);
                    message->appendLocationArgument(world);
                    PickAndPlayInfo info;
                    info.m_position=world;
                    pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)1053,&info);
                    status=COMMAND_COMPLETE;
                }
                break;
            }
            case 38: {
                if (*(const unsigned *)((const char *)command+0x18) & 0x20) {
                    Coord3D world;
                    GuardTheTacticalView->screenToTerrain(&mouse,&world,false);
                    GameMessage *message = GuardTheMessageStream->appendMessage((GameMessage::Type)1108);
                    message->appendLocationArgument(world);
                    PickAndPlayInfo info;
                    info.m_position=world;
                    pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)1108,&info);
                    status=COMMAND_COMPLETE;
                }
                break;
            }
            case 17: {
                if (*(const unsigned *)((const char *)command+0x18) & 0x20) {
                    Coord3D world;
                    GuardTheTacticalView->screenToTerrain(&mouse,&world,false);
                    GameMessage *message = GuardTheMessageStream->appendMessage((GameMessage::Type)1054);
                    message->appendLocationArgument(world);
                    PickAndPlayInfo info;
                    info.m_position=world;
                    pickAndPlayUnitVoiceResponse(GuardTheInGameUI->getAllSelectedDrawables(),(GameMessage::Type)1054,&info);
                    status=COMMAND_COMPLETE;
                }
                break;
            }
            case 10: status=doGuardCommand(command,(GuardMode)0,&mouse); break;
            case 11: status=doGuardCommand(command,(GuardMode)1,&mouse); break;
            case 12: status=doGuardCommand(command,(GuardMode)2,&mouse); break;
            case 23: case 31: case 36: return 0;
            case 9: status=doAttackMoveCommand(command,&mouse); break;
            case 20: status=Rva005B18C0(command,&mouse); break;
            case 30: status=doPlaceBeacon(command,&mouse); break;
            }
            disposition=1;
            if (status==COMMAND_COMPLETE) GuardTheInGameUI->setCommand(0);
        }
    }
    return disposition;
}
