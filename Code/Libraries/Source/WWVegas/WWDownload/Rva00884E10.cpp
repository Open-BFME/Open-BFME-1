// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) char * __cdecl strncpy(char *, const char *, unsigned int);

class Rva00884E10Class
{
public:
	char m_pad0[0x384];
	char m_str[1]; // or something

	int d_00884e10( char *dst, unsigned int maxLen );
};

int Rva00884E10Class::d_00884e10( char *dst, unsigned int maxLen )
{
	if ( !dst )
	{
		return 0x80004005;
	}

	strncpy( dst, m_str, maxLen );
	dst[maxLen - 1] = 0;
	return 0;
}
