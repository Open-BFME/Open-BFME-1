// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?getCrushableLevel@Object@@QBEEXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// readable body of ?getCrusherLevel@Object@@QBEEXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// Open-BFME5: focused reconstruction of BFME's mounted-aware crush levels.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled[0x499 - sizeof(Overridable)];
	UnsignedByte m_crusherLevel;
	UnsignedByte m_crushableLevel;
	UnsignedByte m_mountedCrusherLevel;
	UnsignedByte m_mountedCrushableLevel;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	UnsignedByte getCrusherLevel() const;
	UnsignedByte getCrushableLevel() const;

private:
	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *base = m_template;
		if (base == 0)
			return 0;

		const Overridable *next = base->m_nextOverride;
		if (next != 0)
			next = next->getFinalOverride();
		else
			next = base;

		return static_cast<const ThingTemplate *>(next);
	}

	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_unmodelled[0x128 - 8];
	UnsignedInt m_mountedConditionWord;
};

// ?getCrusherLevel@Object@@QBEEXZ
UnsignedByte Object::getCrusherLevel() const
{
	const ThingTemplate *thingTemplate = getFinalTemplate();
	UnsignedByte level = thingTemplate->m_mountedCrusherLevel;
	if (level == 0xFF || (m_mountedConditionWord & 0x00000800) == 0)
		level = thingTemplate->m_crusherLevel;
	return level;
}

// ?getCrushableLevel@Object@@QBEEXZ
UnsignedByte Object::getCrushableLevel() const
{
	const ThingTemplate *thingTemplate = getFinalTemplate();
	UnsignedByte level = thingTemplate->m_mountedCrushableLevel;
	if (level == 0xFF || (m_mountedConditionWord & 0x00000800) == 0)
		level = thingTemplate->m_crushableLevel;
	return level;
}
