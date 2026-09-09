// cl: /Od /GZ /GS /MD /DNDEBUG

/*
 * The generated row at 0x00813100 is the six-word callback used by the
 * address parser at 0x00813E50 and 0x00813D00.  Those callers pass the same
 * two control values (2 and 0x4000), and the retail epilogue is `ret 18h`,
 * so this TU keeps the raw callback ABI instead of assigning a class name.
 *
 * The object view is deliberately local.  The two parser callers prove the
 * port at +7c, while this body proves the transport pointer at +78, line
 * application at +84, line handle at +88, address at +8c, state/result at
 * +90/+94, and the NUL-terminated host string beginning at +98.  The
 * enclosing TAPI allocation is 0x19c bytes: the host storage occupies
 * +98..+197 (0x100 bytes), followed by the worker id at +198.  The callback
 * receives this same live object from both parser callers; it does not own a
 * temporary one-byte flag.
 */

struct Rva00813100Comm
{
	char m_head[ 0x78 ];
	void *m_transport;              /* +0x78 */
	int m_port;                     /* +0x7c */
	char m_gap80[ 0x04 ];
	int m_lineApplication;          /* +0x84 */
	unsigned int m_handle;          /* +0x88 */
	int m_address;                  /* +0x8c */
	int m_state;                    /* +0x90 */
	int m_result;                   /* +0x94 */
	char m_hostName[ 0x100 ];        /* +0x98..+0x197, NUL-terminated */
	unsigned int m_workerId;         /* +0x198, allocated TAPI tail */
};

extern "C"
{
	int Rva008136C0( int lineApplication, int deviceId, void *line,
		void *callbackInstance, int privileges, int mediaModes );
	int Rva00813780( unsigned int handle );
	int Rva008137C0( int line );
	int Rva00813890( int line, void *address, const char *destination,
		int countryCode );
	int Rva0081B010( void *transport, void *argument );
	int Rva0081B790( void *transport, void *argument );
	int Rva0081B910( void *transport, void *argument );
	int __stdcall Rva0081BDAE( unsigned int handle );
}

extern "C" int Rva0081B9D0( void *transport );

/* Each 0x100-byte RTC-scoped buffer intentionally uses retail's local name `addr`.
 * The generated import wrapper is the proven body at 0x0081BDA8.  Its
 * stock declaration has no useful parameter list, so only this TU's typed
 * call view supplies the three stack words observed at the caller. */
extern void ji_0081bda8();
typedef int ( __stdcall *Rva0081BDA8Answer )( int address, int first,
	int second );

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
	char *destination, const char *format, ... );

extern "C" void __stdcall Rva00813100( int port, int kind,
	Rva00813100Comm *comm, int size, int unusedA, int unusedB )
{
	int openResult;
	Rva00813100Comm *active = comm;

	if ( kind == 2 && size == 0x4000 )
	{
		if ( active->m_state == 4 )
		{
			Rva0081BDAE( active->m_handle );
			active->m_handle = (unsigned int)-1;
			openResult = Rva008136C0( active->m_lineApplication,
				active->m_port, &active->m_handle,
				active, 4, 0x10 );
			return;
		}
		else if ( active->m_state == 3 )
		{
			Rva0081BDAE( active->m_handle );
			active->m_handle = (unsigned int)-1;
			openResult = Rva008136C0( active->m_lineApplication,
				active->m_port,
				&active->m_handle, active, 1, 0x10 );
			if ( openResult != 0 )
			{
				active->m_state = 8;
				return;
			}
			active->m_result = Rva00813890( active->m_handle,
				&active->m_address, active->m_hostName, 0 );
			if ( active->m_result <= 0 )
			{
				Rva0081BDAE( active->m_handle );
				active->m_handle = (unsigned int)-1;
				active->m_state = 8;
				return;
			}
		}

		if ( active->m_state == 5 && Rva0081B9D0(
			active->m_transport ) == 3 &&
			active->m_hostName[ 0 ] == 0 )
		{
			active->m_state = 7;
			Rva0081B010( active->m_transport, 0 );
			Rva0081BDAE( active->m_handle );
			active->m_handle = (unsigned int)-1;
			openResult = Rva008136C0( active->m_lineApplication,
				active->m_port, &active->m_handle,
				active, 4, 0x10 );
			if ( openResult != 0 )
				active->m_state = 8;
			return;
		}

		if ( active->m_state == 5 && Rva0081B9D0(
			active->m_transport ) == 3 &&
			active->m_hostName[ 0 ] != 0 )
		{
			active->m_state = 6;
			Rva0081B010( active->m_transport, 0 );
			Rva0081BDAE( active->m_handle );
			active->m_handle = (unsigned int)-1;
			openResult = Rva008136C0( active->m_lineApplication,
				active->m_port,
				&active->m_handle, active, 1, 0x10 );
			if ( openResult != 0 )
			{
				active->m_state = 8;
				goto Rva00813100Done;
			}
		active->m_result = Rva00813890( active->m_handle,
				&active->m_address, active->m_hostName, 0 );
			if ( active->m_result <= 0 )
			{
				Rva0081BDAE( active->m_handle );
				active->m_handle = (unsigned int)-1;
				active->m_state = 8;
				return;
			}
			return;
		}
	}

	if ( kind == 2 && size == 2 &&
		( active->m_state == 4 || active->m_state == 7 ) )
	{
		active->m_address = port;
		active->m_result = ((Rva0081BDA8Answer)ji_0081bda8)(
			active->m_address, 0, 0 );
		if ( active->m_result == 0 )
			size = 0x100;
	}

	if ( kind == 2 && size == 0x100 )
	{
		if ( active->m_state == 4 || active->m_state == 3 )
		{
			char addr[ 0x100 ];
			int firstResult;
			firstResult = Rva008137C0( active->m_handle );
			if ( firstResult == -1 )
			{
				Rva00813780( active->m_handle );
				active->m_handle = (unsigned int)-1;
				active->m_state = 8;
				return;
			}
			else
			{
				wsprintfA( addr, (const char *)0x012C4A50,
					firstResult );
				if ( active->m_state == 3 )
					Rva0081B910( active->m_transport, addr );
				else
					Rva0081B790( active->m_transport, addr );
				active->m_state = 5;
			}
			return;
		}

		if ( active->m_state == 7 || active->m_state == 6 )
		{
			char addr[ 0x100 ];
			int secondResult;
			secondResult = Rva008137C0( active->m_handle );
			if ( secondResult == -1 )
			{
				Rva00813780( active->m_handle );
				active->m_handle = (unsigned int)-1;
				active->m_state = 8;
			}
			else
			{
				wsprintfA( addr, (const char *)0x012C4A58,
					secondResult );
				Rva0081B010( active->m_transport, addr );
				active->m_state = 5;
			}
		}
	}

Rva00813100Done:
	(void)unusedA;
	(void)unusedB;
}
