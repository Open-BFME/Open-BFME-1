// cl: /Od /GZ /GS /MD /DNDEBUG

struct Rva0081B010Comm
{
	char m_head[ 0x7c ];
	void *m_handle;
	char m_gap80[ 0x10 ];
	void *m_event0;
	char m_gap94[ 0x10 ];
	void *m_event1;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	char m_gapBC[ 0x10 ];
	int m_state;
};

struct Rva0081B010Dcb
{
	unsigned int m_length;
	unsigned int m_baudRate;
	unsigned int m_flags;
	unsigned short m_reserved;
	unsigned short m_xonLimit;
	unsigned short m_xoffLimit;
	unsigned char m_byteSize;
	unsigned char m_parity;
	unsigned char m_stopBits;
	char m_xonChar;
	char m_xoffChar;
	char m_errorChar;
	char m_eofChar;
	char m_evtChar;
	unsigned short m_reserved1;
};

struct Rva0081B010Timeouts
{
	unsigned int m_readInterval;
	unsigned int m_readMultiplier;
	unsigned int m_readConstant;
	unsigned int m_writeMultiplier;
	unsigned int m_writeConstant;
};

struct Rva0081B010Locals
{
	unsigned int m_configSize;
	char m_gap08[ 4 ];
	char *m_parse;
	struct Rva0081B010Dcb *m_dcb;
	char m_gap14[ 4 ];
	char m_config[ 0x1000 ];
	char m_gap1018[ 8 ];
	struct Rva0081B010Timeouts m_timeouts;
};

extern "C" {
__declspec(dllimport) int __stdcall Rva01358CCC( void *handle );
__declspec(dllimport) void *__stdcall Rva01358CE8( const char *name,
	unsigned int desiredAccess, unsigned int shareMode, void *security,
	unsigned int creation, unsigned int flags, void *templateHandle );
__declspec(dllimport) int __stdcall Rva01358D54( void *handle, void *config,
	unsigned int *size );
__declspec(dllimport) int __stdcall Rva01358D58( void *handle,
	struct Rva0081B010Dcb *dcb );
__declspec(dllimport) int __stdcall Rva01358F28( void *handle,
	unsigned int inQueue, unsigned int outQueue );
__declspec(dllimport) int __stdcall Rva01358ED8( void *handle, void *config,
	unsigned int size );
__declspec(dllimport) int __stdcall Rva01358EDC( void *handle,
	unsigned int mask );
__declspec(dllimport) int __stdcall Rva01358EE0( void *handle,
	struct Rva0081B010Dcb *dcb );
__declspec(dllimport) int __stdcall Rva01358EE4( void *handle,
	struct Rva0081B010Timeouts *timeouts );
__declspec(dllimport) int __stdcall Rva01358EB0( void *handle,
	unsigned int flags );
__declspec(dllimport) int __stdcall Rva01358F0C( void *eventHandle );

char *__cdecl strncpy( char *destination, const char *source,
	unsigned int count );
char *__cdecl strchr( const char *string, int character );
int __cdecl strncmp( const char *left, const char *right,
	unsigned int count );
}

extern void d_0081b700( void );

extern "C" int Rva0081B010( struct Rva0081B010Comm *comm, char *argument )
{
	int baud;
	char temp[ 0x20 ];
	struct Rva0081B010Locals locals;

	baud = 0;
	locals.m_timeouts.m_readInterval = 0xffffffff;
	locals.m_timeouts.m_readMultiplier = 0;
	locals.m_timeouts.m_readConstant = 0;
	locals.m_timeouts.m_writeMultiplier = 0;
	locals.m_timeouts.m_writeConstant = 0;
	locals.m_dcb = (struct Rva0081B010Dcb *)( locals.m_config + 8 );

	if ( argument == 0 && comm->m_state == 4 )
	{
		comm->m_state = 5;
		Rva01358EDC( comm->m_handle, 2 );
		Rva01358EB0( comm->m_handle, 0x0f );
		Rva01358CCC( comm->m_handle );
		comm->m_handle = (void *)-1;
		return 0;
	}

	if ( comm->m_state != 1 && comm->m_state != 5 )
		return -8;

	if ( comm->m_state == 1 )
		((void (__cdecl *)( struct Rva0081B010Comm * ))d_0081b700)( comm );

	strncpy( temp, argument, 0x20 );
	if ( strchr( temp, ':' ) != 0 )
	{
		*( strchr( temp, ':' ) ) = 0;
		argument = strchr( argument, ':' ) + 1;
	}
	else
	{
		argument = (char *)0x0130b18c;
	}

	if ( strncmp( temp, "TAPI", 4 ) == 0 )
	{
		locals.m_parse = temp + 4;
		baud = 0;
		for ( ; *locals.m_parse >= '0' && *locals.m_parse <= '9';
			locals.m_parse++ )
		{
			baud = baud * 10 + ( *locals.m_parse & 0x0f );
		}
		comm->m_handle = (void *)baud;
	}
	else
	{
		comm->m_handle = Rva01358CE8( temp, 0xc0000000, 0, 0,
			3, 0x40000080, 0 );
		if ( comm->m_handle == (void *)-1 )
			return -4;
	}

	Rva01358F28( comm->m_handle, 0x2000, 0x1000 );
	Rva01358EE4( comm->m_handle, &locals.m_timeouts );
	Rva01358EDC( comm->m_handle, 2 );

	if ( baud != 0 )
	{
		locals.m_configSize = 0x1000;
		Rva01358D54( comm->m_handle, locals.m_config, &locals.m_configSize );
		locals.m_dcb->m_evtChar = 0x0a;
		locals.m_dcb->m_flags = locals.m_dcb->m_flags | 1;
		locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffff7ff;
		locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffeff;
		locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffdff;
		locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xffffbfff;
		Rva01358ED8( comm->m_handle, locals.m_config, locals.m_configSize );
		goto finish;
	}

	locals.m_dcb->m_length = 0x1c;
	Rva01358D58( comm->m_handle, locals.m_dcb );
	locals.m_dcb->m_evtChar = 0x0a;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags | 1;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffff7ff;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffeff;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffdff;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xffffbfff;
	locals.m_dcb->m_byteSize = 8;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags | 2;
	locals.m_dcb->m_stopBits = 0;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xffffffbf;
	locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffff7;
	locals.m_dcb->m_flags = ( locals.m_dcb->m_flags & 0xffffffcf ) | 0x10;

	while ( argument != 0 && *argument != 0 )
	{
		if ( *argument == ',' )
			argument++;

		if ( strncmp( argument, "+RTS", 4 ) == 0 )
			locals.m_dcb->m_flags = ( locals.m_dcb->m_flags & 0xffffcfff ) | 0x2000;
		if ( strncmp( argument, "-RTS", 4 ) == 0 )
			locals.m_dcb->m_flags = ( locals.m_dcb->m_flags & 0xffffcfff ) | 0x1000;
		if ( strncmp( argument, "+CTS", 4 ) == 0 )
			locals.m_dcb->m_flags = locals.m_dcb->m_flags | 4;
		if ( strncmp( argument, "-CTS", 4 ) == 0 )
			locals.m_dcb->m_flags = locals.m_dcb->m_flags & 0xfffffffb;

		if ( *argument >= '0' && *argument <= '9' )
		{
			locals.m_dcb->m_baudRate = 0;
			while ( *argument >= '0' && *argument <= '9' )
			{
				locals.m_dcb->m_baudRate = locals.m_dcb->m_baudRate * 10
					+ ( *argument & 0x0f );
				argument++;
			}
		}

		while ( *argument != ',' && *argument != 0 )
			argument++;
	}

	Rva01358EE0( comm->m_handle, locals.m_dcb );

finish:
	Rva01358EB0( comm->m_handle, 0x0c );
	Rva01358F0C( comm->m_event0 );
	Rva01358F0C( comm->m_event1 );
	Rva01358F0C( comm->m_event2 );
	comm->m_state = ( comm->m_state != 5 ) + 4;
	return 0;
}
