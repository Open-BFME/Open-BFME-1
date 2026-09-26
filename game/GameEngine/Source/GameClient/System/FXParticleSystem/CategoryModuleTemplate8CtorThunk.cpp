// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CategoryModuleTemplate (ledger $07 / N=8) default ctor
// Retail: construct sub at +4 (interim vtbl), set two bools at +8/+9 to 1,
// then dual most-derived vtbls at +0/+4. novtable so final vtbls are sequenced
// in the body after the bools.

namespace FXParticleSystem
{

extern "C" char CategoryModuleTemplate8_vtbl0;
extern "C" char CategoryModuleTemplate8_vtbl4;

class CategoryModuleTemplate8Sub
{
public:
	virtual void dummy();
};

template <int N>
class __declspec(novtable) CategoryModuleTemplate
{
public:
	CategoryModuleTemplate();

private:
	void *m_v0;
	CategoryModuleTemplate8Sub m_sub;
	bool m_a;
	bool m_b;
};

// MSVC mangles CategoryModuleTemplate<8> as @$07
template <int N>
CategoryModuleTemplate<N>::CategoryModuleTemplate()
	: m_a(true),
	  m_b(true)
{
	m_v0 = &CategoryModuleTemplate8_vtbl0;
	*reinterpret_cast<void **>(&m_sub) = &CategoryModuleTemplate8_vtbl4;
}

template CategoryModuleTemplate<8>::CategoryModuleTemplate();
}
