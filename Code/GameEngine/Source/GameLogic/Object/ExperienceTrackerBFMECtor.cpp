// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ExperienceTracker@@: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp

typedef int Int;
typedef float Real;

class Object;
class Xfer;
class AsciiString;

template <class T>
class StringBase
{
private:
	friend class AsciiString;

	StringBase(const T *text);
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class ExperienceTracker;

class BfmeThingEFE
{
public:
	BfmeThingEFE(ExperienceTracker *tracker);

private:
	unsigned char m_data[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker : public Snapshot
{
public:
	ExperienceTracker(Object *parent);
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Object *m_parent;
	AsciiString m_levelName;
	Real m_currentExperience;
	Int m_currentLevel;
	Int m_unknown14;
	Int m_experienceSink;
	Real m_experienceScalar;
	Int m_unknown20;
	bool m_unknown24;
	unsigned char m_padding25[3];
	Int m_scalarIndex;
	BfmeThingEFE *m_helper;
};

ExperienceTracker::ExperienceTracker(Object *parent) :
	m_parent(parent),
	m_levelName(""),
	m_currentExperience(0.0f),
	m_currentLevel(0),
	m_unknown14(-1),
	m_experienceSink(0),
	m_experienceScalar(1.0f),
	m_unknown20(0),
	m_unknown24(false),
	m_scalarIndex(0),
	m_helper(0)
{
	m_helper = new BfmeThingEFE(this);
}
