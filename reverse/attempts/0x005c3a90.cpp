// ?bfmeMakeAndRead_005C3A90@@YGPAXPAXPAVHolder005C3A90@@0@Z
// partial score=0.71 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// stdcall wrapper: TheParticleSystemManager->make(src, extra) returns a
// 12-byte handle (same shape as BfmeParticleSystemHandle / BfmeVec3). If the
// first word is live and the middle argument is too, copy [arg+0x74] into
// the system at +0xB8. Return the pointer at system+0xAC.

extern class ParticleSystemManager *TheParticleSystemManager;

class ParticleSystem
{
public:
	char m_padAC[ 0xAC ];
	void *m_fieldAC;
	char m_padB4[ 8 ];
	void *m_fieldB8;
};

class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle( const BfmeParticleSystemHandle &that );
	~BfmeParticleSystemHandle() throw();

	ParticleSystem *m_system;
	char m_tail[ 8 ];
};

class Holder005C3A90
{
public:
	char m_pad74[ 0x74 ];
	void *m_field74;
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle make( void *src, void *extra );
};

void *__stdcall bfmeMakeAndRead_005C3A90( void *src, Holder005C3A90 *obj, void *extra )
{
	void *a = src;
	void *b = extra;
	BfmeParticleSystemHandle handle = TheParticleSystemManager->make( a, b );
	void *result = 0;
	if ( handle.m_system )
	{
		if ( obj )
			handle.m_system->m_fieldB8 = obj->m_field74;
		result = handle.m_system->m_fieldAC;
	}
	return result;
}
