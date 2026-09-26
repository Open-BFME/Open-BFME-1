// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<2>::operator= -- null-check the source, take its
// info sub-object at +8, and let DefaultUpdateModuleInfo's own operator= (ILT 0x00002A09) copy it.
// Replaces the naked lift of the same body.

namespace FXParticleSystem
{

class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo &operator=(const DefaultUpdateModuleInfo &other);
};

template <int Category>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate &operator=(const DefaultModuleTemplate &other);

private:
	unsigned char m_pad[8];
	DefaultUpdateModuleInfo m_info;
};

template <int Category>
DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate &other)
{
	const DefaultModuleTemplate *o = &other;
	const DefaultUpdateModuleInfo *p;

	if (o)
		p = (const DefaultUpdateModuleInfo *)((const char *)o + 8);
	else
		p = 0;

	m_info = *p;
	return *this;
}

template class DefaultModuleTemplate<2>;

}
