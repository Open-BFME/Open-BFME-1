// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" __declspec(dllimport) char *__cdecl strncpy( char *destination, const char *source,
	unsigned int count );

class Rva007AE680Name
{
public:
	void setName( const char *name );

private:
	unsigned char m_pad0[0x10];
	char m_name[32];
};

void Rva007AE680Name::setName( const char *name )
{
	strncpy( m_name, name, 31 );
	m_name[31] = 0;
}
