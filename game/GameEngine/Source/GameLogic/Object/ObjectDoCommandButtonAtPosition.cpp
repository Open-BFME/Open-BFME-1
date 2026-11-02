// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

typedef bool Bool;

class Drawable;
class Object;
class SpecialPowerTemplate;
class Waypoint;

class CommandOptions
{
public:
	Bool isClear(unsigned int bit) const
	{
		return ((~(m_bits >> bit)) & 1) != 0;
	}

	unsigned int m_bits;
};

#include "../command_source_type.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	int m_unmodelled00[4];
	int m_commandType;
	int m_unmodelled14;
	CommandOptions m_options;
	int m_unmodelled1C[6];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	int m_unmodelled38[13];
	int m_weaponSlot;
	int m_unmodelled70[4];
	int m_maxShotsToFire;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
// BFME decorates Coord3D as a class: retail's ILT confirms PBVCoord3D for
// AICommandInterface::aiAttackMoveToPosition (0x00153AF0) is defined struct-keyed; the
// call below names it through a member pointer.
extern "C" void __identifier("?aiAttackMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z")(void);
// aiAttackMoveToPosition and doCommandButtonAtPosition.
// class-gate: allow Coord3D canonical header is struct-keyed; retail ILT proves the class-keyed mangling
class Coord3D
{
public:
	float x;
	float y;
	float z;
};

typedef _STL::list<Drawable *> DrawableList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CommandXlat.h
class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	Coord3D m_position;
	unsigned int m_commandButton;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType source);
	void aiIdle(CommandSourceType source);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
private:
	char m_unmodelled00[0x20];

public:
	AICommandInterface m_commandInterface;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();

	void doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos,
		CommandSourceType source, Bool playVoiceResponse);
	void doSpecialPowerUsingWaypoints(const SpecialPowerTemplate *specialPower,
		const Waypoint *way, unsigned int options, Bool fromScript);

private:
	char m_unmodelled004[0x1A0];
	int m_disabledMask;
	char m_unmodelled1A8[0x5C];
	AIUpdateInterface *m_ai;
};

void Object::doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos,
	CommandSourceType source, Bool playVoiceResponse)
{
	if (m_disabledMask)
		return;

	if (playVoiceResponse && getDrawable() && commandButton &&
		commandButton->m_options.isClear(3))
	{
		PickAndPlayInfo info;
		info.m_commandButton = (unsigned int)commandButton;
		if (pos)
			info.m_position = *pos;

		DrawableList list;
		list.push_back(getDrawable());
		pickAndPlayUnitVoiceResponse(&list, (GameMessage::Type)0x7E4, &info);
	}

	AIUpdateInterface *ai = m_ai;
	if (!commandButton)
		return;

	switch (commandButton->m_commandType)
	{
		case 23:
		case 36:
			if (commandButton->m_specialPowerTemplate)
			{
				unsigned int options = commandButton->m_options.m_bits | 0x40000;
				if (playVoiceResponse)
					options |= 0x20000000;
				// Retail calls 0x001C3850 (module slot +0x34) with the position; the ledger
				// names that body doSpecialPowerUsingWaypoints.
				doSpecialPowerUsingWaypoints(commandButton->m_specialPowerTemplate,
					(const Waypoint *)pos, options, source == CMD_FROM_SCRIPT);
			}
			return;

		case 9:
			if (ai)
			{
				union { void (*raw)(void); void (AICommandInterface::*member)(const Coord3D *, int, CommandSourceType); } call;
				call.raw = __identifier("?aiAttackMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z");
				(ai->m_commandInterface.*call.member)(pos, commandButton->m_maxShotsToFire,
					source);
			}
			return;

		case 13:
			if (ai)
				ai->m_commandInterface.aiIdle(source);
			return;
	}
}

// @?doCommandButtonAtPosition@Object@@QAEXPBVCommandButton@@PBVCoord3D@@W4CommandSourceType@@_N@Z 0x001D1FA0
