// cl: /DNDEBUG /MD /EHsc

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

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class BfmeThingEFE
{
public:
	virtual ~BfmeThingEFE();
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class ExperienceTracker : public Snapshot
{
public:
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Object *m_parent;
	AsciiString m_levelName;
	float m_currentExperience;
	int m_currentLevel;
	int m_unknown14;
	int m_experienceSink;
	float m_experienceScalar;
	int m_unknown20;
	bool m_unknown24;
	unsigned char m_padding25[3];
	int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

ExperienceTracker::~ExperienceTracker()
{
	if (m_scalarTable)
		delete m_scalarTable;
	m_scalarTable = 0;
}
