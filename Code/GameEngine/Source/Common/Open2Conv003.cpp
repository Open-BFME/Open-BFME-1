// Four mid-size bodies recovered from byte-true dumps.  Identity is NOT
// recovered: every class, member and function name is address-derived, and the
// padding virtuals exist only to place the slot each body actually calls.

// ---------------------------------------------------------------------------
// 0x006407D0 and 0x00644950 -- two teardowns over the same pair of members: a
// non-polymorphic lock object and a polymorphic live handle.
//
// The lock goes through a DIRECT destructor call followed by `operator delete`,
// so its class has no vtable; the handle goes through `push 1` into vtable slot
// 0, the scalar deleting destructor, so its class does.  Between the two the
// handle is CLOSED and then RE-READ before the delete -- retail loads
// [esi+0x70] a second time and tests it again -- which is what `delete` does
// when a call in between could have changed the member.
//
// The two differ in where the null test sits.  At 0x006407D0 the lock delete is
// unguarded (MSVC's own test) and only the handle work is inside an `if`; at
// 0x00644950 everything is inside one `if (m_handle)` and the final
// `m_handle = 0` is outside it, which is what makes the zero live in a register
// (`xor ebx,ebx`) across the whole body instead of being an immediate store.

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

class Rva006407D0
{
public:
	void shutdown( void );
	char m_pad[0x70];
	Open2LiveHandle *m_handle;
	char m_pad2[8];
	Gen009DB400 *m_lock;
};

// @?shutdown@Rva006407D0@@QAEXXZ 0x006407D0
void Rva006407D0::shutdown( void )
{
	open2DeleteAndClear( m_lock );
	if( m_handle == 0 )
		return;
	m_handle->close();
	delete m_handle;
	m_handle = 0;
}

class Rva00644950
{
public:
	void shutdown( void );
	char m_pad[0x64];
	Open2LiveHandle *m_handle;
	char m_pad2[0xc];
	Gen009DB400 *m_lock;
};

// @?shutdown@Rva00644950@@QAEXXZ 0x00644950
void Rva00644950::shutdown( void )
{
	if( m_handle )
	{
		open2DeleteAndClear( m_lock );
		m_handle->close();
		delete m_handle;
	}
	m_handle = 0;
}

// ---------------------------------------------------------------------------
// 0x006A2FD0 -- resolve a key to a drawable id, then hand both on.
//
//     test edi,edi / jne have / xor al,al / ret 4
//     ... call <find> / xor esi,esi / test eax,eax / je send
//     mov edx,[eax] / mov ecx,eax / call [edx+0x28] / test eax,eax / je send
//     mov ecx,eax / call <getID> / mov esi,eax
//     send: push esi / push edi / mov ecx,ebx / call <deliver>
//
// The early exit is `xor al,al`, the byte form, so the result is byte-wide and
// comes from the final call, which is why that call is not a tail jump: its
// return value is this one's.  The id starts at zero and survives both misses.

class Open26A2FD0Drawable
{
public:
	unsigned int getID( void );
};

class Open26A2FD0Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Open26A2FD0Drawable *slot28();
};

class Open26A2FD0Logic
{
public:
	Open26A2FD0Object *find( void *key );
};

extern Open26A2FD0Logic *TheOpen26A2FD0Logic;

class Rva006A2FD0
{
public:
	char handle( void *key );
	char deliver( void *key, unsigned int id );
};

// @?handle@Rva006A2FD0@@QAEDPAX@Z 0x006A2FD0
char Rva006A2FD0::handle( void *key )
{
	if( !key )
		return 0;

	Open26A2FD0Object *object = TheOpen26A2FD0Logic->find( key );
	unsigned int id = 0;
	if( object )
	{
		Open26A2FD0Drawable *drawable = object->slot28();
		if( drawable )
			id = drawable->getID();
	}
	return deliver( key, id );
}
