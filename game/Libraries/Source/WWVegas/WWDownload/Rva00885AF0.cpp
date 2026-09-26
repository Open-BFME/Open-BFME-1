// cl: /DNDEBUG /MD /EHs-c-

extern "C" int __stdcall closesocket( int );
extern "C" __declspec(dllimport) int __cdecl fclose( void* );

class Rva00885AF0Class
{
public:
	char pad0[4];
	int m_socket4;
	int m_socket8;
	char padC[0x3AC];
	void* m_file3B8;

	void d_00885af0();
};

void Rva00885AF0Class::d_00885af0()
{
	*(void**)this = (void*)0x01132ECC;
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
	if ( m_file3B8 )
	{
		fclose( m_file3B8 );
		m_file3B8 = 0;
	}
}
