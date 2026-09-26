// cl: /DNDEBUG /MD /EHs-c-

extern "C" int __stdcall closesocket( int s );

class Rva00885980Class
{
public:
	char m_pad0[4];
	int m_socket; // at 0x4
	int m_socket8; // at 0x8

	int d_00885980( void );
	void d_00885960( void );
};

int Rva00885980Class::d_00885980( void )
{
	closesocket( m_socket );
	return 0;
}

void Rva00885980Class::d_00885960( void )
{
	closesocket( m_socket8 );
	m_socket8 = 0;
}

class Rva00885390Class
{
public:
	char m_pad0[4];
	int m_socket4;
	int m_socket8;

	void d_00885390( void );
};

void Rva00885390Class::d_00885390( void )
{
	if ( m_socket8 )
	{
		closesocket( m_socket8 );
		m_socket8 = 0;
	}
	if ( m_socket4 )
	{
		closesocket( m_socket4 );
		m_socket4 = 0;
	}
}
