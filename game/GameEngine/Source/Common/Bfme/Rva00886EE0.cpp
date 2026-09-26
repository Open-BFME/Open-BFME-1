// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset( void *body );
extern "C" __declspec(dllimport) void __stdcall Rva01358E4CInit( void *body );

class Rva00886EE0Class
{
public:
	char m_pad0[0x18];
	bool m_flag18;

	Rva00886EE0Class *d_00886ee0( void );
	void d_00886f00( void );
};

Rva00886EE0Class *Rva00886EE0Class::d_00886ee0( void )
{
	m_flag18 = true;
	Rva01358E4CInit( this );
	return this;
}

void Rva00886EE0Class::d_00886f00( void )
{
	Rva01358D0CReset( this );
	m_flag18 = false;
}
