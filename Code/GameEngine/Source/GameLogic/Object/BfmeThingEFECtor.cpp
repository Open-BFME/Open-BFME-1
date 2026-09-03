// cl: /DNDEBUG /MD /EHsc

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class ThingTemplate;
	friend class Object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getExperienceScalarTableName() const
	{
		return m_experienceScalarTableName;
	}

private:
	unsigned char m_unreconstructed_008[0x58 - 0x08];
	AsciiString m_experienceScalarTableName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = static_cast<const ThingTemplate *>(
				thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate;
	}

private:
	void *m_vtable;
	ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker
{
public:
	Object *getParent() const
	{
		return m_parent;
	}

private:
	void *m_vtable;
	Object *m_parent;
};

struct BfmeVec
{
	Real *start;
	Real *end;
};

class ExperienceLevelSystem
{
public:
	BfmeVec *findExperienceScalarTable(const AsciiString &name);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeThingEFE
{
public:
	BfmeThingEFE(ExperienceTracker *tracker);
	virtual ~BfmeThingEFE();

private:
	ExperienceTracker *m_tracker;
	Real m_scalar;
	int m_baseCount;
	BfmeVec *m_vec;
};

BfmeThingEFE::BfmeThingEFE(ExperienceTracker *tracker) :
	m_tracker(tracker),
	m_scalar(1.0f),
	m_baseCount(1),
	m_vec(0)
{
	AsciiString tableName =
		m_tracker->getParent()->getTemplate()->getExperienceScalarTableName();
	ExperienceLevelSystem *system = TheExperienceLevelSystem;
	m_vec = system->findExperienceScalarTable(tableName);
}
