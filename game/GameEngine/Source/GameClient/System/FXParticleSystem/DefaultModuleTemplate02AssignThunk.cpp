// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DefaultModuleTemplate<3>::operator=.
// The category bases have no assignable state; assignment copies the
// DefaultPhysicsModuleInfo subobject at +8 while preserving its vtable.

namespace FXParticleSystem
{

struct GameClientRandomVariable
{
	unsigned int m_type;
	float m_low;
	float m_high;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo &operator=(const DefaultPhysicsModuleInfo &that)
	{
		m_vector = that.m_vector;
		m_field3 = that.m_field3;
		m_var1 = that.m_var1;
		return *this;
	}

private:
	void *m_vtable;
	Vector3 m_vector;
	int m_field3;
	GameClientRandomVariable m_var1;
};

template <int Category>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate &operator=(const DefaultModuleTemplate &that);

private:
	unsigned char m_category_bases[8];
	DefaultPhysicsModuleInfo m_info;
};

template <int Category>
DefaultModuleTemplate<Category> &DefaultModuleTemplate<Category>::operator=(const DefaultModuleTemplate &that)
{
	const DefaultModuleTemplate *source = &that;
	const DefaultPhysicsModuleInfo *info = source
		? (const DefaultPhysicsModuleInfo *)((const char *)source + 8)
		: 0;
	m_info = *info;
	return *this;
}

template class DefaultModuleTemplate<3>;

}
