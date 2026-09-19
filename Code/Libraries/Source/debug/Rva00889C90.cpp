// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) void* __cdecl memmove( void*, const void*, unsigned int );

struct Element {
	int val0;
	void* val4;
	void* val8;
};

extern void* Rva0088EB90( void*, unsigned int );

class Rva00889C90Class
{
public:
	int m_val0;
	Element* m_data; // +4
	unsigned int m_size;      // +8

	void d_00889c90( void* arg1, void* arg2 );
};

void Rva00889C90Class::d_00889c90( void* arg1, void* arg2 )
{
	if ( !arg1 ) return;

	for ( unsigned int i = 0; i < m_size; ++i )
	{
		Element* p = &m_data[i];
		if ( p->val4 == arg1 && p->val8 == arg2 )
		{
			memmove( p, p + 1, (m_size - i - 1) * sizeof(m_data) );
			m_data = m_data - 1;
			m_data = (Element*)Rva0088EB90( m_data, m_size * sizeof(Element) );
		}
	}
}
