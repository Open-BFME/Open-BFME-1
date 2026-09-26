// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<7>::operator= -- null-check the source, take its
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
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate &operator=(const DefaultModuleTemplate &other);

private:
	unsigned char m_pad[8];
	WindModuleInfo m_info;
};

template <int Category>
DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate &other)
{
	const DefaultModuleTemplate *o = &other;
	const WindModuleInfo *p;

	if (o)
		p = (const WindModuleInfo *)((const char *)o + 8);
	else
		p = 0;

	m_info = *p;
	return *this;
}

template class DefaultModuleTemplate<7>;

}
