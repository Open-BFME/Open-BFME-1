// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<1>::operator= -- null-check the source, take its
// info sub-object at +8, and let DefaultAlphaModuleInfo's own operator= (ILT 0x0001EC36) copy it.
// Replaces the naked lift of the same body.

namespace FXParticleSystem
{

class DefaultAlphaModuleInfo
{
public:
	DefaultAlphaModuleInfo &operator=(const DefaultAlphaModuleInfo &other);
};

template <int Category>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate &operator=(const DefaultModuleTemplate &other);

private:
	unsigned char m_pad[8];
	DefaultAlphaModuleInfo m_info;
};

template <int Category>
DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate &other)
{
	const DefaultModuleTemplate *o = &other;
	const DefaultAlphaModuleInfo *p;

	if (o)
		p = (const DefaultAlphaModuleInfo *)((const char *)o + 8);
	else
		p = 0;

	m_info = *p;
	return *this;
}

template class DefaultModuleTemplate<1>;

}
