// cl: /DNDEBUG /MD /EHsc

typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
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
