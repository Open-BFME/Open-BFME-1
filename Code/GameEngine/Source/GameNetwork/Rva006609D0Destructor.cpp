// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x006609D0 (197 B) of a 0xB4-byte network
// results object: after a clearing member call (0x0065F100) the members
// unwind in reverse -- the owning holder of a mutex lock at +0xB0 (its inline
// destructor is the eighth EH state) -- a
// GameResultsCounter at +0xA8 a red-black tree at +0x74 two deques at +0x44
// and +0x1C and three GameResultsCounters at +0x14 +0xC and +4 -- and the
// base vtable is restored.  Member types are opaque address-derived shells
// sized from the offsets with out-of-line destructors.

class GameResultsCounter
{
public:
	~GameResultsCounter();

private:
	char m_body[ 8 ];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};
};

struct Rva00660470Deque
{
	~Rva00660470Deque();
	char m_body[ 0x28 ];
};

struct Rva00660610Deque
{
	~Rva00660610Deque();
	char m_body[ 0x28 ];
};

struct Rva0064C290Tree
{
	~Rva0064C290Tree();
	char m_body[ 0x0C ];
};

struct Rva006609D0LockHolder
{
	~Rva006609D0LockHolder()
	{
		if( m_lock )
			delete m_lock;
	}

	MutexClass::LockClass *m_lock;
};

class Rva006609D0Base
{
public:
	virtual ~Rva006609D0Base() {}
};

class Rva006609D0 : public Rva006609D0Base
{
public:
	virtual ~Rva006609D0();

private:
	void bfmeClearVHX( void );

	GameResultsCounter m_counter04;
	GameResultsCounter m_counter0C;
	GameResultsCounter m_counter14;
	Rva00660470Deque m_deque1C;
	Rva00660610Deque m_deque44;
	char m_unreconstructed6C[ 8 ];
	Rva0064C290Tree m_tree74;
	char m_unreconstructed80[ 0xA8 - 0x80 ];
	GameResultsCounter m_counterA8;
	Rva006609D0LockHolder m_lockB0;
};

// ??1Rva006609D0@@UAE@XZ
Rva006609D0::~Rva006609D0()
{
	bfmeClearVHX();
}
