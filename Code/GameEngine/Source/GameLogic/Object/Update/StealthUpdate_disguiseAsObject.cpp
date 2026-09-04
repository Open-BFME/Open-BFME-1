// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x002AC440: StealthUpdate::disguiseAsObject.  The BFME Object and
// StealthUpdate layouts in this TU preserve the retail module and template
// slots while the implementation follows the Zero Hour twin.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_NONE = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	Int getPlayerIndex() const
	{
		return *(const Int *)((const char *)this + 0x24);
	}
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[4];
	Overridable *m_override;
};

class Drawable
{
public:
	Bool isSelected() const
	{
		return *(const Bool *)((const char *)this + 0x3AC);
	}
};

class Module;

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

	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;

	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate =
			*(const ThingTemplate * const *)((const char *)this + 4);
		if (!thingTemplate)
		{
			thingTemplate = 0;
			goto template_done;
		}
		if (thingTemplate->m_override)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_override->getFinalOverride();
	template_done:
		return thingTemplate;
	}
};

class ControlBar
{
public:
	void markUIDirty()
	{
		*(Bool *)((char *)this + 0x24) = 1;
	}
};

extern ControlBar *TheControlBar;

class UpdateModule
{
public:
	virtual void unused() = 0;

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class StealthUpdate : public UpdateModule
{
public:
	void disguiseAsObject(const Object *target);

private:
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextBlackMarketCheckFrame;
	Bool m_enabled;
	Bool m_pad2D[7];
	Int m_disguiseAsPlayerIndex;
	const ThingTemplate *m_disguiseAsTemplate;
	UnsignedInt m_disguiseTransitionFrames;
	Bool m_disguiseHalfpointReached;
	Bool m_transitioningToDisguise;
	Bool m_disguised;
};

class StealthUpdateModuleData
{
private:
	unsigned char m_pad00[0x54];

public:
	UnsignedInt m_disguiseTransitionFrames;
	UnsignedInt m_disguiseRevealTransitionFrames;
};

// ?disguiseAsObject@StealthUpdate@@QAEXPBVObject@@@Z
void StealthUpdate::disguiseAsObject(const Object *target)
{
	Object *self = m_object;
	const StealthUpdateModuleData *data =
		(const StealthUpdateModuleData *)m_moduleData;

	if (target && target->getControllingPlayer())
	{
		static NameKeyType key_StealthUpdate =
			TheNameKeyGenerator->nameToKey("StealthUpdate");
		StealthUpdate *stealth =
			(StealthUpdate *)target->findModule(key_StealthUpdate);
		if (stealth && stealth->m_disguiseAsTemplate)
		{
			m_disguiseAsTemplate = stealth->m_disguiseAsTemplate;
			m_disguiseAsPlayerIndex = stealth->m_disguiseAsPlayerIndex;
		}
		else
		{
			m_disguiseAsTemplate = target->getTemplate();
			m_disguiseAsPlayerIndex =
				target->getControllingPlayer()->getPlayerIndex();
		}

		m_enabled = 1;
		m_transitioningToDisguise = 1;
		m_disguiseTransitionFrames = data->m_disguiseTransitionFrames;
		m_disguiseHalfpointReached = 0;
		setWakeFrame(m_object, UPDATE_SLEEP_NONE);
	}
	else if (m_disguised)
	{
		m_disguiseAsTemplate = 0;
		m_disguiseAsPlayerIndex = 0;
		m_disguiseTransitionFrames =
			data->m_disguiseRevealTransitionFrames;
		m_transitioningToDisguise = 0;
		m_disguiseHalfpointReached = 0;
	}

	Drawable *draw = self->getDrawable();
	if (draw && draw->isSelected())
		TheControlBar->markUIDirty();
}
