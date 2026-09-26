// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class BuffManager;

struct Gen_t_004312a0_m4pod
{
	BuffManager *m_manager;
};

class BuffManagerRegistry
{
public:
	void add( BuffManager *manager );

private:
	char m_pad00[ 0xE4 ];
	_STL::vector<Gen_t_004312a0_m4pod> m_managers;
};

// ?add@BuffManagerRegistry@@QAEXPAVBuffManager@@@Z
void BuffManagerRegistry::add( BuffManager *manager )
{
	Gen_t_004312a0_m4pod *begin = m_managers.begin();
	Gen_t_004312a0_m4pod *end = m_managers.end();
	while ( begin != end )
	{
		if ( begin->m_manager == manager )
			return;
		++begin;
	}
	m_managers.push_back(
		*reinterpret_cast<const Gen_t_004312a0_m4pod *>( &manager ) );
}
