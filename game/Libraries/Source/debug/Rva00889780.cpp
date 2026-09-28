// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) char * __cdecl strncpy(char *, const char *, unsigned int);
extern const char g_Rva0107301CEmptyString[];

class Rva00889780Class
{
public:
	char m_pad0[0x9E70];
	char m_str[0x10]; // 0x9E70
	int m_field9E80;

	void d_00889780( const char *arg1, int arg2 );
};

void Rva00889780Class::d_00889780( const char *arg1, int arg2 )
{
	strncpy( m_str, arg1 ? arg1 : g_Rva0107301CEmptyString, 0x0F );
	m_str[0x0F] = 0;
	m_field9E80 = arg2;
}
