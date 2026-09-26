// Near-twin of Rva00644950::shutdown (Open2Conv003.cpp): same teardown shape
// over a lock object and a polymorphic live handle, but the padding between
// m_handle and m_lock is 4 bytes narrower here, so m_lock sits at +0x70
// instead of +0x74.

class Gen009DB400
{
public:
	~Gen009DB400();
};

class Open2LiveHandle
{
public:
	virtual ~Open2LiveHandle();
	void close( void );
};

inline void open2DeleteAndClear( Gen009DB400 *&slot )
{
	delete slot;
	slot = 0;
}

class Rva0063B750
{
public:
	void shutdown( void );
	char m_pad[0x64];
	Open2LiveHandle *m_handle;
	char m_pad2[8];
	Gen009DB400 *m_lock;
};

// @?shutdown@Rva0063B750@@QAEXXZ 0x0063B750
void Rva0063B750::shutdown( void )
{
	if( m_handle )
	{
		open2DeleteAndClear( m_lock );
		m_handle->close();
		delete m_handle;
	}
	m_handle = 0;
}
