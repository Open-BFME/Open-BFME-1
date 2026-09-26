// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $00 / N=1) copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class DefaultModuleTemplate00BaseCopyShim
{
public:
	void construct_from(const void *src);
};

class DefaultModuleTemplate00SubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char DefaultModuleTemplate00_vtbl0;
extern "C" char DefaultModuleTemplate00_vtbl4;
extern "C" char DefaultModuleTemplate00_sub_vtbl;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// MSVC mangles DefaultModuleTemplate<1> as @$00
template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	const void *src = &that;
	((DefaultModuleTemplate00BaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	DefaultModuleTemplate00SubCopyShim *sub =
		(DefaultModuleTemplate00SubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &DefaultModuleTemplate00_sub_vtbl;
	m_v0 = &DefaultModuleTemplate00_vtbl0;
	m_v4 = &DefaultModuleTemplate00_vtbl4;
}

template DefaultModuleTemplate<1>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
