// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void* __cdecl fopen( const char*, const char* );
extern "C" __declspec(dllimport) int __cdecl fseek( void*, int, int );
extern "C" __declspec(dllimport) int __cdecl ftell( void* );
extern "C" __declspec(dllimport) int __cdecl fclose( void* );

// The download-name builder at retail 0x008859D0 is defined, matched, in
// Rva008859D0.cpp as a member of Rva008859D0Class.  CftpGetNextFileBlock.cpp
// reaches the same body the same way: a TU-local view of that class and a call
// through `this`, which is what the retail bytes do (one `call`, no vtable).
class Rva008859D0Class
{
public:
	void d_008859d0( const char* name, char* outBuf );
};

class Rva00886A20Class
{
public:
	char pad[0x2C];
	int m_size2C;

	int d_00886a20( const char* name, int dummy );
};

int Rva00886A20Class::d_00886a20( const char* name, int dummy )
{
	char buf[256];
	((Rva008859D0Class *)this)->d_008859d0( name, buf );

	int file = (int)fopen( buf, "rb" );
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
