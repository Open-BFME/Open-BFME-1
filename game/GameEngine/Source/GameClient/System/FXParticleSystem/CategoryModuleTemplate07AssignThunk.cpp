// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CategoryModuleTemplate<8>::operator=
// Retail: null-check other; p = other? other+8 : 0; copy *p ushort.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate &operator=(const CategoryModuleTemplate &other);

private:
	unsigned char m_pad[8];
	unsigned short m_value;
};

template <int Category>
CategoryModuleTemplate<Category> &CategoryModuleTemplate<Category>::operator=(const CategoryModuleTemplate &other)
{
	const CategoryModuleTemplate *o = &other;
	const unsigned short *p;
	if (o)
		p = (const unsigned short *)((const char *)o + 8);
	else
		p = 0;
	m_value = *p;
	return *this;
}

template class CategoryModuleTemplate<8>;

}
