// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CategoryModuleTemplate (N=7 / $06) copy ctor
// Retail: base copy; null-preserving sub at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

class CategoryModuleTemplate06BaseCopyShim
{
public:
	void construct_from(const void *src);
};

class CategoryModuleTemplate06SubCopyShim
{
public:
	void construct_from(const void *src_sub_or_null);
	virtual void dummy();
};

extern "C" char CategoryModuleTemplate06_vtbl0;
extern "C" char CategoryModuleTemplate06_vtbl4;
extern "C" char CategoryModuleTemplate06_sub_vtbl;

template <int N>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

template <int N>
CategoryModuleTemplate<N>::CategoryModuleTemplate(const CategoryModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate06BaseCopyShim *)this)->construct_from(src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	CategoryModuleTemplate06SubCopyShim *sub =
		(CategoryModuleTemplate06SubCopyShim *)((char *)this + 8);
	sub->construct_from(sub_src);
	*(void **)sub = &CategoryModuleTemplate06_sub_vtbl;
	m_v0 = &CategoryModuleTemplate06_vtbl0;
	m_v4 = &CategoryModuleTemplate06_vtbl4;
}

template CategoryModuleTemplate<7>::CategoryModuleTemplate(const CategoryModuleTemplate &);
}
