// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameClient/ControlBar.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/Drawable.h"
#include "GameClient/View.h"

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

Object *BFME_Valid_Under_Cursor(const ICoord2D *mouse, const CommandButton *command, PickType pickType)
{
	return validUnderCursor(mouse, command, pickType);
}

static enum CommandStatus
{
	COMMAND_INCOMPLETE = 0,
	COMMAND_COMPLETE
};

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

CommandStatus BFME_DoFireWeaponCommand(const CommandButton *command, const ICoord2D *mouse)
{
	return doFireWeaponCommand(command, mouse);
}
