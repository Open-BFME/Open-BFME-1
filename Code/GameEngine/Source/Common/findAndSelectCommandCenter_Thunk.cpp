// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

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
	Bool isLocallyControlled() const;
	void *m_vtable;
	const Overridable *m_template;
};

class GameLogic
{
public:
	void selectObject(Object *, Bool, unsigned long, Bool);
};

extern GameLogic *TheGameLogic;

Bool __cdecl findAndSelectCommandCenter(Object *obj, void *)
{
	if (obj) {
		const Overridable *thingTemplate = obj->m_template;
		if (thingTemplate->m_nextOverride) {
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		}

		if (*reinterpret_cast<const unsigned int *>(
				reinterpret_cast<const char *>(thingTemplate) + 0xc8) & 0x20000) {
			Player *player = obj->getControllingPlayer();
			unsigned long playerMask = 1 << player->m_playerIndex;
			TheGameLogic->selectObject(obj, true, playerMask, obj->isLocallyControlled());
			return false;
		}
	}
	return true;
}
