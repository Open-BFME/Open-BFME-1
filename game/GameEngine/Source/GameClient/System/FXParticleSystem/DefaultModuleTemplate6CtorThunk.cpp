// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $06 / N=7) ctor
// Retail: shim construct then three vtbl stores at +0/+4/+8.

namespace FXParticleSystem
{

class DefaultModuleTemplate7CtorShim
{
public:
	void construct();
};

extern "C" char DefaultModuleTemplate6_vtbl0;
extern "C" char DefaultModuleTemplate6_vtbl4;
extern "C" char DefaultModuleTemplate6_vtbl8;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate();

private:
	void *m_v0;
	void *m_v4;
	void *m_v8;
};

// MSVC mangles DefaultModuleTemplate<7> as @$06
template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate()
{
	((DefaultModuleTemplate7CtorShim *)this)->construct();
	m_v0 = &DefaultModuleTemplate6_vtbl0;
	m_v4 = &DefaultModuleTemplate6_vtbl4;
	m_v8 = &DefaultModuleTemplate6_vtbl8;
}

template DefaultModuleTemplate<7>::DefaultModuleTemplate();
}
