// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc
// stlport
// STLport list<handle>::clear. Each 0x14-byte node holds a 12-byte intrusive
// handle at +8; destroying the handle unlinks it from ParticleSystem +0x98/+0x9C.

class ParticleSystem;

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
public:
	unsigned char m_pad[ 0x98 ];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
};

inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle()
{
	if ( m_system )
	{
		if ( m_previous )
			m_previous->m_next = m_next;
		else
			m_system->m_firstHandle = m_next;
		if ( m_next )
			m_next->m_previous = m_previous;
		else
			m_system->m_lastHandle = m_previous;
		m_previous = 0;
		m_next = 0;
	}
}

#include <list>

template void _STL::_List_base< BfmeParticleSystemHandle, _STL::allocator< BfmeParticleSystemHandle > >::clear();
