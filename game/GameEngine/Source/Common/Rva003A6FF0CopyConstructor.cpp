// The imported increment target and the +4 adjustment identify m_at08 as a
// retained handle; keeping the increment after the pointer store reproduces
// the retail constructor's null branch and instruction order.

extern int R2Data010EC768;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

class Rva003A6FF0
{
public:
	void * m_at00;
	int m_at04;
	void * m_at08;
	char m_at0C;

	Rva003A6FF0( const Rva003A6FF0 & source );
};

Rva003A6FF0::Rva003A6FF0( const Rva003A6FF0 & source )
{
	m_at00 = &R2Data010EC768;
	m_at04 = source.m_at04;
	m_at08 = source.m_at08;
	if ( m_at08 != 0 )
		InterlockedIncrement( (long *)((char *)m_at08 + 4) );
	m_at0C = source.m_at0C;
}
