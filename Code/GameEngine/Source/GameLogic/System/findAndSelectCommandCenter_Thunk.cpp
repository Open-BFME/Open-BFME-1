// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: recover the command-center visitor from its retail body.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	const Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	char m_pad[0x24];
	int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
	bool isLocallyControlled() const;

	__forceinline int isCommandCenter() const
	{
		const Overridable *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
		{
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		}
		return *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const char *>(thingTemplate) + 0xc8) & 0x20000;
	}

	void *m_vtable;
	const Overridable *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void selectObject(Object *, bool, unsigned short, bool);
};

extern GameLogic *TheGameLogic;

// ?findAndSelectCommandCenter@@YAHPAVObject@@PAX@Z
int __cdecl findAndSelectCommandCenter(Object *obj, void *)
{
	if (obj && obj->isCommandCenter())
	{
		Player *player = obj->getControllingPlayer();
		unsigned short playerMask = 1 << player->m_playerIndex;
		TheGameLogic->selectObject(
			obj, true, playerMask, obj->isLocallyControlled());
		return 0;
	}
	return 1;
}
