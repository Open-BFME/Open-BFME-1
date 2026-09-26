// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave( void* );
extern "C" __declspec(dllimport) void __stdcall Rva01358E54( void* );
extern "C" __declspec(dllimport) void __stdcall Rva01358ECC( void* );

class Rva00889720Class
{
public:
	char m_pad0[0x9DF8];
	int m_field9DF8;
	int m_field9DFC;
	char m_pad9E00[0x150];
	int m_field9F50;

	bool d_00889720( void );
};

bool Rva00889720Class::d_00889720( void )
{
	m_field9DFC = 0;
	Rva01358E74Leave( (void*)0x01336E60 );
	Rva01358E54( &m_field9DF8 );
	Rva01358ECC( (void*)m_field9F50 );
	return false;
}
