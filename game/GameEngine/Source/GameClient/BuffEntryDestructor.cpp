// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The base table these destructors restore last is 0x01073744, Snapshot's
// (??0Snapshot at 0x0006B180 installs it); SubsystemInterface's is 0x01141640.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

class BuffOwned
{
public:
	virtual ~BuffOwned();
};

class Rva0040AD80ReferenceState
{
public:
	void releaseReferences();
};

class BuffEntryTail : public Snapshot
{
public:
	virtual ~BuffEntryTail() { cleanup(); }
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();
	void cleanup();
	char m_retailTail[0x10];
};

class BuffEntry : public Snapshot
{
public:
	virtual ~BuffEntry();
	virtual void crc(Xfer *);
	virtual void xfer(Xfer *);
	virtual void loadPostProcess();

private:
	char m_head[0x14];
	BuffOwned *m_owned;
	int m_link;
	char m_middle[0x10];
	BuffEntryTail m_tail;
};

// ?Rva00015479Cleanup@BuffEntryTail@@QAEXXZ
void BuffEntryTail::cleanup()
{
	reinterpret_cast<Rva0040AD80ReferenceState *>(this)->releaseReferences();
}

BuffEntry::~BuffEntry()
{
	if (m_owned != 0)
	{
		delete m_owned;
		m_owned = 0;
	}
	m_link = 0;
}
