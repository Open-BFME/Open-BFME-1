// cl: /DNDEBUG /MD /EHs-c-

extern "C" int __stdcall accept( int, void*, void* );
extern "C" int __stdcall WSAGetLastError( void );

class Rva00885920Class
{
public:
	char m_pad0[4];
	int m_socket4;
	int m_socket8;

	int d_00885920( void );
	int d_00885530( const char* command, int size );
};


int Rva00885920Class::d_00885920( void )
{
	if ( !m_socket8 )
	{
		return 0x80040001;
	}
	int s = accept( m_socket8, 0, 0 );
	if ( s < 0 )
	{
		return ( WSAGetLastError() == 10035 ) ? 0x80040002 : 0x80040001;
	}
	m_socket8 = s;
	return 0;
}

extern "C" int __stdcall send( int, const char*, int, int );
extern "C" __declspec(dllimport) void __stdcall Rva01358EA8( void* );

int Rva00885920Class::d_00885530( const char* command, int size )
{
	if ( send( m_socket4, command, size, 0 ) > 0 )
	{
		Rva01358EA8( (void*)0x01132E90 );
		Rva01358EA8( (void*)command );
		return 0;
	}
	return 0x80040001;
}
