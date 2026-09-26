// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CategoryModuleTemplate (N=8 / $07) copy ctor
// Retail: base copy; null-preserving word at +8; dual outer vtbl.

namespace FXParticleSystem
{

class CategoryModuleTemplate07BaseCopyShim
{
public:
	void construct_from(const void *src);
};

extern "C" char CategoryModuleTemplate07_vtbl0;
extern "C" char CategoryModuleTemplate07_vtbl4;

template <int N>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	unsigned short m_word;
};

template <int N>
CategoryModuleTemplate<N>::CategoryModuleTemplate(const CategoryModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate07BaseCopyShim *)this)->construct_from(src);
	const void *p = src ? (const char *)src + 8 : 0;
	m_word = *(const unsigned short *)p;
	m_v0 = &CategoryModuleTemplate07_vtbl0;
	m_v4 = &CategoryModuleTemplate07_vtbl4;
}

template CategoryModuleTemplate<8>::CategoryModuleTemplate(const CategoryModuleTemplate &);
}
