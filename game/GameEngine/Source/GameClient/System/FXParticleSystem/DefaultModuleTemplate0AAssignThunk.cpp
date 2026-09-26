// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<0>::operator= -- null-check the source, take its
// info sub-object at +8, and let DefaultColorModuleInfo's own operator= (ILT 0x000111C6) copy it.
// Replaces the naked lift of the same body.

namespace FXParticleSystem
{

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo &operator=(const DefaultColorModuleInfo &other);
};

template <int Category>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate &operator=(const DefaultModuleTemplate &other);

private:
	unsigned char m_pad[8];
	DefaultColorModuleInfo m_info;
};

template <int Category>
DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate &other)
{
	const DefaultModuleTemplate *o = &other;
	const DefaultColorModuleInfo *p;

	if (o)
		p = (const DefaultColorModuleInfo *)((const char *)o + 8);
	else
		p = 0;

	m_info = *p;
	return *this;
}

template class DefaultModuleTemplate<0>;

}
