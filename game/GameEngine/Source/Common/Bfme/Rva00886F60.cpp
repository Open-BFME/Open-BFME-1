// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave( void *body );

class Rva00886EE0Class
{
public:
	char m_pad0[0x18];
	bool m_flag18;
};

class Rva00886F60Class
{
public:
	Rva00886EE0Class *m_lock;

	virtual ~Rva00886F60Class();
};

Rva00886F60Class::~Rva00886F60Class()
{
	if ( m_lock )
	{
		if ( m_lock->m_flag18 )
		{
			Rva01358E74Leave( m_lock );
		}
	}
}
