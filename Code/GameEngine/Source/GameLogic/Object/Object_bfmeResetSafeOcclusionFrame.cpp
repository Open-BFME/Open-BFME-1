// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	UnsignedInt getOcclusionDelay() const { return m_occlusionDelay; }

private:
	unsigned char m_pad[0x428 - 0x08];
	UnsignedInt m_occlusionDelay;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;

private:
	virtual ~Thing();
	const ThingTemplate *m_template;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *thingTemplate = m_template;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object : public Thing
{
public:
	void bfmeResetSafeOcclusionFrame();

private:
	unsigned char m_pad[0x334 - 0x08];
	UnsignedInt m_safeOcclusionFrame;
};

// Object.cpp preserves this assignment as frame + ThingTemplate occlusion delay.
void Object::bfmeResetSafeOcclusionFrame()
{
	GameLogic *gameLogic = TheGameLogic;
	if (gameLogic)
	{
		UnsignedInt frame = gameLogic->m_frame;
		const ThingTemplate *thingTemplate = getTemplate();
		m_safeOcclusionFrame = frame + thingTemplate->getOcclusionDelay();
	}
}
