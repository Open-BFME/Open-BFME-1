// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate (N=6) copy ctor
// Retail: base copy; null-preserving sub at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class DefaultModuleTemplate05BaseCopyShim
{
public:
	void construct_from(const void *src);
};

class DefaultModuleTemplate05SubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char DefaultModuleTemplate05_vtbl0;
extern "C" char DefaultModuleTemplate05_vtbl4;
extern "C" char DefaultModuleTemplate05_sub_vtbl;

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

template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	const void *src = &that;
	((DefaultModuleTemplate05BaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	DefaultModuleTemplate05SubCopyShim *sub =
		(DefaultModuleTemplate05SubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	*(void **)sub = &DefaultModuleTemplate05_sub_vtbl;
	m_v0 = &DefaultModuleTemplate05_vtbl0;
	m_v4 = &DefaultModuleTemplate05_vtbl4;
}

template DefaultModuleTemplate<6>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
