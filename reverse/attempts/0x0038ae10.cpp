// ?findAndSelectCommandCenter@@YAHPAVObject@@PAX@Z
// partial score=0.9 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class Player
{
public:
	char m_pad[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool isLocallyControlled() const;
	__forceinline int isCommandCenter() const
	{
		const Overridable *thingTemplate = m_template;
		if (thingTemplate->m_nextOverride) {
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		}
		return *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const char *>(thingTemplate) + 0xc8) & 0x20000;
	}
	void *m_vtable;
	const Overridable *m_template;
};

class GameLogic
{
public:
	void selectObject(Object *, bool, unsigned short, bool);
};

extern GameLogic *TheGameLogic;

int __cdecl findAndSelectCommandCenter(Object *obj, void *)
{
	register Object *object = obj;
	if (object && object->isCommandCenter()) {
		Player *player = object->getControllingPlayer();
		unsigned short playerMask = 1 << player->m_playerIndex;
		TheGameLogic->selectObject(
			object, true, playerMask, object->isLocallyControlled());
		return false;
	}
	return true;
}
