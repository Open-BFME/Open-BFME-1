// cl: /Od /GZ /GS /MD /DNDEBUG
// Retail 0x00819630: DirtySock TAPI transport allocation called by
// Rva00812DD0.  The address-derived entry keeps the raw cdecl ABI proved by
// that caller; the object view is local because no shared layout is justified.

struct Rva00819630Comm
{
	void *m_ops[ 14 ];
	char m_gap38[ 0x14 ];
	char m_name[ 0x2c ];
	void *m_transport;
	int m_handle;
	char m_gap80[ 8 ];
	int m_field88;
	int m_field8c;
	void *m_event0;
	char m_gap94[ 0x10 ];
	void *m_event1;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	char m_gapBC[ 0x0c ];
	int m_threadId;
	int m_state;
	int m_pendingValue;
	int m_recvRecordSize;
	int m_recvBufferSize;
	int m_recvWriteOffset;
	int m_recvReadOffset;
	void *m_recvBuffer;
	int m_recvSequence;
	int m_sendRecordSize;
	int m_sendBufferSize;
	int m_sendWriteOffset;
	int m_sendReadOffset;
	int m_sendAckOffset;
	void *m_sendBuffer;
	unsigned int m_sendSequence;
	char m_gap108[ 0x800 ];
	int m_field908;
	char m_gap90c[ 0x1000 ];
	int m_field190c;
	int m_field1910;
	int m_field1914;
	char m_gap1918[ 8 ];
	char m_lock[ 0x18 ];
	int m_depth;
	int m_flags;
	char m_tail[ 4 ];
};

extern "C"
{
	void *memset( void *destination, int value, unsigned int count );
	char *strcpy( char *destination, const char *source );
	int __cdecl strcmp( const char *left, const char *right );
	unsigned int __cdecl strlen( const char *text );
	__declspec( dllimport ) int __cdecl wsprintfA( char *output,
		const char *format, ... );
	__declspec( dllimport ) void *__stdcall CreateFileA(
		const char *name, unsigned int desiredAccess, unsigned int shareMode,
		void *security, unsigned int creation, unsigned int flags,
		void *templateHandle );

	void Rva0081ACD0( void *comm );
	int Rva0081B790( void *comm, void *argument );
	int Rva0081B830( void *comm );
	int Rva0081B910( void *comm, void *argument );
	int Rva0081BA60( void *comm, const void *payload, int length );
	int Rva0081BC80( void *comm, void *buffer, int size, unsigned int *when );
	int Rva0081BD40( void *comm, void *buffer, int size, unsigned int *when );

	__declspec( dllimport ) void __stdcall InitializeCriticalSection( void *lock );
	__declspec( dllimport ) unsigned long __stdcall GetCurrentThreadId( void );
	__declspec( dllimport ) void *__stdcall CreateThread(
		void *security, unsigned long stackSize,
		unsigned long (__stdcall *start)( void * ), void *parameter,
		unsigned long flags, unsigned long *identifier );
	__declspec( dllimport ) int __stdcall SetThreadPriority(
		void *thread, int priority );
	__declspec( dllimport ) int __stdcall CloseHandle( void *thread );
	__declspec( dllimport ) void *__stdcall CreateEventA(
		void *security, int manualReset, int initialState, const char *name );
}

// Retail installs this typed five-argument cdecl callback in operation-table
// slot 2 and returns a status in EAX.  Its upstream spelling is unavailable,
// so the address-derived name is retained.
typedef int ( __cdecl *Rva0081AE20Proc )( void *comm, const char *name,
	char *output, int outputSize, int flags );
extern void Rva0081B000( void );
extern void Rva0081AE10( void );
extern void Rva0081BA40( void );
extern "C" void Rva0081B9B0( void *comm );

extern "C" int Rva0081B9D0( void *comm );
// The generated row keeps the exact retail COFF spelling/address. CreateThread
// consumes that address as a DWORD WINAPI(void *) thread entry.
extern void d_00819920( void );
typedef unsigned long ( __stdcall *Rva00819920ThreadProc )( void *parameter );
extern void *Rva007F0000Alloc( int size );

extern "C" int Rva0081AE20( void *comm, const char *name, char *output,
	int outputSize, int separator )
{
	int i;
	void *handle;
	const char *ports[ 5 ] = { "COM1", "COM2", "COM3", "COM4", 0 };
	char *originalOutput;

	originalOutput = output;
	output[ 0 ] = '*';
	output[ 1 ] = 0;
	output[ 2 ] = 0;

	if ( name == 0 || *name == 0 )
		return -1;

	if ( outputSize < 0x40
		|| (unsigned int)outputSize < strlen( name ) + 2 )
		return -6;

	if ( strcmp( name, "localhost" ) != 0 )
	{
		wsprintfA( output, "%s%c", name, 0 );
		return 1;
	}

	for ( i = 0; ports[ i ] != 0; i++ )
	{
		handle = CreateFileA( ports[ i ], 0xc0000000, 0, 0, 3,
			0x40000080, 0 );

		if ( handle == (void *)-1 )
			continue;

		CloseHandle( handle );

		if ( output != originalOutput )
			*output++ = (char)separator;

		output += wsprintfA( output, "%s", ports[ i ] );
	}

	*output++ = 0;
	*output++ = 0;
	return 1;
}

extern "C" void *Rva00819630( int first, int second, int third )
{
	unsigned long pid;
	void *result;
	Rva00819630Comm *comm;

	comm = (Rva00819630Comm *)Rva007F0000Alloc( 0x1944 );
	if( comm == 0 )
		return 0;

	memset( comm, 0, 0x1944 );
	comm->m_ops[ 0 ] = (void *)Rva00819630;
	comm->m_ops[ 1 ] = (void *)Rva0081ACD0;
	comm->m_ops[ 2 ] = (void *)(Rva0081AE20Proc)Rva0081AE20;
	comm->m_ops[ 3 ] = (void *)Rva0081B000;
	comm->m_ops[ 4 ] = (void *)Rva0081B790;
	comm->m_ops[ 5 ] = (void *)Rva0081B830;
	comm->m_ops[ 6 ] = (void *)Rva0081B910;
	comm->m_ops[ 7 ] = (void *)Rva0081B9B0;
	comm->m_ops[ 8 ] = (void *)Rva0081AE10;
	comm->m_ops[ 9 ] = (void *)Rva0081B9D0;
	comm->m_ops[ 10 ] = (void *)Rva0081BA40;
	comm->m_ops[ 11 ] = (void *)Rva0081BA60;
	comm->m_ops[ 12 ] = (void *)Rva0081BC80;
	comm->m_ops[ 13 ] = (void *)Rva0081BD40;
	strcpy( comm->m_name, "SERIAL" );
	InitializeCriticalSection( comm->m_lock );

	comm->m_recvRecordSize = first + 0x10;
	comm->m_recvBufferSize = comm->m_recvRecordSize * second;
	comm->m_recvBuffer = Rva007F0000Alloc(
		comm->m_recvBufferSize );
	comm->m_sendRecordSize = first + 0x10;
	comm->m_sendBufferSize = comm->m_sendRecordSize * third;
	comm->m_sendBuffer = Rva007F0000Alloc(
		comm->m_sendBufferSize );
	comm->m_field908 = 0;
	comm->m_field1914 = 0;
	comm->m_field1910 = 0;
	comm->m_field190c = 0x800;
	comm->m_state = 1;
	comm->m_pendingValue = 0;
	comm->m_threadId = GetCurrentThreadId();
	comm->m_handle = -1;
	comm->m_event0 = CreateEventA( 0, 1, 1, 0 );
	comm->m_event1 = CreateEventA( 0, 1, 1, 0 );
	comm->m_event2 = CreateEventA( 0, 1, 1, 0 );
	result = CreateThread( 0, 0, (Rva00819920ThreadProc)d_00819920,
		comm, 0, &pid );
	if( result == 0 )
		return 0;
	SetThreadPriority( result, 2 );
	CloseHandle( result );
	return comm;
}
