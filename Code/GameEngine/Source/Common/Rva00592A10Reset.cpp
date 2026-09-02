// cl: /O2 /Ob0

void __cdecl bfmeFree592A10( void *block );

class Rva00592A10Resource
{
public:
	void destroy();
};

class Rva00592A10Owner
{
public:
	void reset();
	void stop();
	void finish();

private:
	bool m_active;
	volatile bool m_flag1;
	volatile bool m_flag2;
	char m_pad03;
	volatile int  m_index;
	Rva00592A10Resource * volatile m_first;
	Rva00592A10Resource * volatile m_second;
};

void Rva00592A10Owner::reset()
{
	if( m_active )
	{
		stop();
		m_active = false;
	}

	m_flag1 = false;
	m_flag2 = false;
	m_index = -1;

	Rva00592A10Resource *resource;
	resource = m_first;
	if( resource )
	{
		resource->destroy();
		bfmeFree592A10( resource );
	}
	m_first = 0;

	resource = m_second;
	if( resource )
	{
		resource->destroy();
		bfmeFree592A10( resource );
	}
	m_second = 0;

	finish();
}
