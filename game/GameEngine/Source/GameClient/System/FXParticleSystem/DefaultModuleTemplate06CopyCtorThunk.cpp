// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $06 / N=7) copy ctor
// Retail: push src; base copy; three vtbl stores at +0/+4/+8.

namespace FXParticleSystem
{

class DefaultModuleTemplate7CopyCtorShim
{
public:
	void construct_from(const void *src);
};

extern "C" char DefaultModuleTemplate6_vtbl0;
extern "C" char DefaultModuleTemplate6_vtbl4;
extern "C" char DefaultModuleTemplate6_vtbl8;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	void *m_v8;
};

template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	((DefaultModuleTemplate7CopyCtorShim *)this)->construct_from(&that);
	m_v0 = &DefaultModuleTemplate6_vtbl0;
	m_v4 = &DefaultModuleTemplate6_vtbl4;
	m_v8 = &DefaultModuleTemplate6_vtbl8;
}

template DefaultModuleTemplate<7>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
