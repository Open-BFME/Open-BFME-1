// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: CategoryModuleTemplate<7>::operator= -- null-check the source, take its
// info sub-object at +8, and let WindModuleInfo's own operator= (ILT 0x00017F53) copy it.
// Replaces the naked lift of the same body.

namespace FXParticleSystem
{

class WindModuleInfo
{
public:
	WindModuleInfo &operator=(const WindModuleInfo &other);
};

template <int Category>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate &operator=(const CategoryModuleTemplate &other);

private:
	unsigned char m_pad[8];
	WindModuleInfo m_info;
};

template <int Category>
CategoryModuleTemplate<Category> &CategoryModuleTemplate<Category>::operator=(const CategoryModuleTemplate &other)
{
	const CategoryModuleTemplate *o = &other;
	const WindModuleInfo *p;

	if (o)
		p = (const WindModuleInfo *)((const char *)o + 8);
	else
		p = 0;

	m_info = *p;
	return *this;
}

template class CategoryModuleTemplate<7>;

}
