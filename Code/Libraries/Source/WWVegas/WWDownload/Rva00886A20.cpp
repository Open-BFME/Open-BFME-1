// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void* __cdecl fopen( const char*, const char* );
extern "C" __declspec(dllimport) int __cdecl fseek( void*, int, int );
extern "C" __declspec(dllimport) int __cdecl ftell( void* );
extern "C" __declspec(dllimport) int __cdecl fclose( void* );

class Rva00886A20Class
{
public:
	char pad[0x2C];
	int m_size2C;

	void d_008859d0( const char* name, char* outBuf );
	int d_00886a20( const char* name, int dummy );
};

int Rva00886A20Class::d_00886a20( const char* name, int dummy )
{
	char buf[256];
	d_008859d0( name, buf );

	int file = (int)fopen( buf, (const char*)0x0107FF20 );
	if ( !file )
	{
		m_size2C = file;
		return file;
	}

	fseek( (void*)file, 0, 2 );
	m_size2C = ftell( (void*)file );
	fclose( (void*)file );
	return m_size2C;
}
