// ?d_005ee8a0@@YAXXZ
// partial score=0.72 date=2026-09-10
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// The module-class factory at 0x005E7420 names this family
// "DefaultParticleAlphaModuleInfo", allocates 0x5c bytes, and forwards its
// TrackingPtr plus the alpha-module template to this constructor.  The two
// secondary vtables and the eight RandomAlphaKeyframe pairs establish the
// DefaultParticleModule<0> specialization independently of address proximity.

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
private:
	T *m_ptr;
};

struct RandomAlphaKeyframe
{
	RandomAlphaKeyframe() : value( 0.0f ), frame( 0 ) {}

	float value;
	unsigned int frame;
};

template <int Category>
class DefaultModuleTemplate;

template <int Category>
class DefaultParticleModule;

template <>
class DefaultParticleModule<0>
{
public:
	DefaultParticleModule( TrackingPtr<ParticleSystem> &system,
		const DefaultModuleTemplate<0> *module_template );
	virtual void unusedPrimary();

private:
	TrackingPtr<ParticleSystem> *m_system;
	void *m_categoryVtable;
	void *m_snapshotVtable;
	RandomAlphaKeyframe m_alphaKey[8];
	float m_alpha;
	float m_alphaRate;
	unsigned int m_alphaTargetKey;
};

template <>
class DefaultModuleTemplate<0>
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();

	RandomAlphaKeyframe m_alphaKey[8];
};

DefaultParticleModule<0>::DefaultParticleModule(
	TrackingPtr<ParticleSystem> &system,
	const DefaultModuleTemplate<0> *module_template )
	: m_system( &system )
{
	m_categoryVtable = (void *)0x0110f978;
	m_snapshotVtable = (void *)0x011128d0;

	for ( int i = 0; i < 8; ++i )
		m_alphaKey[i] = module_template->m_alphaKey[i];

	m_alpha = m_alphaKey[0].value;
	m_alphaTargetKey = 1;
	if ( m_alphaKey[1].frame == 0 )
	{
		m_alphaRate = 0.0f;
	}
	else
	{
		float delta = m_alphaKey[1].value - m_alphaKey[0].value;
		unsigned int time = m_alphaKey[1].frame - m_alphaKey[0].frame;
		m_alphaRate = delta / time;
	}
}

}
