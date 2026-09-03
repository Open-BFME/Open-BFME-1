// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface() {}
};

class BuffOwned
{
public:
	virtual ~BuffOwned();
};

class BuffEntryTail : public SubsystemInterface
{
public:
	virtual ~BuffEntryTail() { cleanup(); }
	void cleanup();
	char m_retailTail[0x10];
};

class BuffEntry : public SubsystemInterface
{
public:
	virtual ~BuffEntry();

private:
	char m_head[0x14];
	BuffOwned *m_owned;
	int m_link;
	char m_middle[0x10];
	BuffEntryTail m_tail;
};

BuffEntry::~BuffEntry()
{
	if (m_owned != 0)
	{
		delete m_owned;
		m_owned = 0;
	}
	m_link = 0;
}
