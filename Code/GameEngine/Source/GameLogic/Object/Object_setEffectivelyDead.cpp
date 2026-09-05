// cl: /DNDEBUG /MD /EHsc
// BFME Object::setEffectivelyDead. Retail 0x001C7E60, 337 bytes.
// ZH twin only sets EFFECTIVELY_DEAD and removes from radar; BFME also stamps
// GameLogic+0x16c, notifies ScriptEngine, fires HeroDie for kind 0x59, and
// walks drawable slots 1..5.

typedef bool Bool;

enum KindOfType
{
	KINDOF_RETAIL_59 = 0x59
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class Module;
class DamageInfo;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Radar
{
public:
	void removeObject(Object *obj);
	void addObject(Object *obj);
};

extern Radar *TheRadar;

class GameLogicFrameSlice
{
public:
	unsigned char m_pad00[0x3c];
	unsigned int m_frame;
	unsigned char m_pad40[0x16c - 0x40];
	unsigned int m_objectChangeFrame;
};

extern GameLogicFrameSlice *TheGameLogic;

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

extern ScriptEngine *TheScriptEngine;

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class ObjectModule
{
public:
	virtual void unused0() = 0;
private:
	void *m_data;
	void *m_object;
	void *m_extra;
};

class DieModule : public ObjectModule, public DieModuleInterface
{
};

class Drawable
{
public:
	// 4125F0 forwards to 409850: signed slot bounds1..5 and bool action.
	void forward4125F0(int slot, bool immediately);
};

class BfmeObjectDrawableDispatch
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Drawable *getDrawable() = 0;
};

class Thing
{
public:
	Bool isKindOf(KindOfType k) const;
};

class Object : public Thing
{
public:
	void setEffectivelyDead(Bool dead);
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad00[0x20c];
	void *m_radarData;
	unsigned char m_pad210[0x344 - 0x210];
	unsigned char m_privateStatus;
};

void Object::setEffectivelyDead(Bool dead)
{
	if (*(unsigned char *)&dead)
	{
		unsigned char status = m_privateStatus;
		if ((status & 1) != 0)
			return;
		m_privateStatus = (unsigned char)(status | 1);
		if (m_radarData)
			TheRadar->removeObject(this);
		TheGameLogic->m_objectChangeFrame = TheGameLogic->m_frame;
		TheScriptEngine->notifyOfObjectCreationOrDestruction();
		if (isKindOf(KINDOF_RETAIL_59))
		{
			static NameKeyType heroDieKey =
				TheNameKeyGenerator->nameToKey("HeroDie");
			Module *mod = findModule(heroDieKey);
			if (mod)
				reinterpret_cast<DieModule *>(mod)->onDie(0);
		}
		Drawable *drawable =
			reinterpret_cast<BfmeObjectDrawableDispatch *>(this)->getDrawable();
		if (drawable)
		{
			for (int slot = 1; slot < 6; ++slot)
				drawable->forward4125F0(slot, false);
		}
	}
	else
	{
		unsigned char status = m_privateStatus;
		if ((status & 1) == 0)
			return;
		m_privateStatus = (unsigned char)(status & 0xfe);
		if (m_radarData)
			TheRadar->addObject(this);
		TheGameLogic->m_objectChangeFrame = TheGameLogic->m_frame;
		TheScriptEngine->notifyOfObjectCreationOrDestruction();
	}
}
