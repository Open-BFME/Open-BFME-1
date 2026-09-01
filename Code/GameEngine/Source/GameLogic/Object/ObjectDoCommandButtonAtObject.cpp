// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

typedef bool Bool;

class Drawable;
class Object;
class SpecialPowerTemplate;

class CommandOptions
{
public:
	Bool isClear(unsigned int bit) const
	{
		return ((~(m_bits >> bit)) & 1) != 0;
	}

	unsigned int m_bits;
};

enum CommandSourceType
{
	CMD_FROM_GUI,
	CMD_FROM_SCRIPT
};

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
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

typedef _STL::list<Drawable *> DrawableList;

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

class GameMessage
{
public:
	enum Type
	{
		MSG_DO_ATTACK_OBJECT = 0x7E4
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class AICommandInterface
{
public:
	void aiAttackObject(Object *object, int shots, CommandSourceType source);
	void aiIdle(CommandSourceType source);
	void aiEnter(Object *object, CommandSourceType source);
};

class AIUpdateInterface
{
private:
	char m_unmodelled00[0x20];

public:
	AICommandInterface m_commandInterface;
};

class GameLogic
{
public:
	char m_unmodelled00[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

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

	void doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
		CommandSourceType source, Bool playVoiceResponse);
	void doSpecialPowerAtObject(const SpecialPowerTemplate *specialPower, Object *object,
		unsigned int options, Bool fromScript);
	void setWeaponLock(int slot, int lockType);

private:
	char m_unmodelled004[0x1A0];
	int m_disabled;
	char m_unmodelled1A8[0x5C];
	AIUpdateInterface *m_ai;
	char m_unmodelled208[0x164];
	unsigned int m_weaponLockExpirationFrame;
};

void Object::doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
	CommandSourceType source, Bool playVoiceResponse)
{
	if (m_disabled)
		return;

	if (playVoiceResponse && getDrawable() && commandButton &&
		commandButton->m_options.isClear(3))
	{
		PickAndPlayInfo info;
		info.m_commandButton = (unsigned int)commandButton;
		info.m_drawTarget = object ? object->getDrawable() : 0;

		DrawableList list;
		list.push_back(getDrawable());
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_DO_ATTACK_OBJECT, &info);
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
				doSpecialPowerAtObject(commandButton->m_specialPowerTemplate, object,
					options, source == CMD_FROM_SCRIPT);
			}
			return;

		case 22:
			m_weaponLockExpirationFrame = TheGameLogic->m_frame + 50;
			setWeaponLock(commandButton->m_weaponSlot, 1);
			ai->m_commandInterface.aiAttackObject(object, 1, source);
			return;

		case 13:
			if (ai)
				ai->m_commandInterface.aiIdle(source);
			return;

		case 28:
			if (ai)
				ai->m_commandInterface.aiEnter(object, source);
			return;
	}
}

// @?doCommandButtonAtObject@Object@@QAEXPBVCommandButton@@PAV1@W4CommandSourceType@@_N@Z 0x001D1D10
