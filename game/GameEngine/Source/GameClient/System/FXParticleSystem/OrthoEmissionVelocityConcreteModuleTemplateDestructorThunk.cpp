// cl: /DNDEBUG /MD /EHsc
// ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> empty triple-vtbl dtor
// at 0x005DB6F0. Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked).
// Destructor ILT 0x00043A8B routes directly to 0x005DB6F0; scalar deleting
// dtor at 0x005DB780 and vector deleting dtor at 0x005DB7B0 call through the
// same ILT; landed neighbours (ctor 0x005DB6C0, copy ctor 0x005DB730,
// operator= 0x005DB760) sit either side in the same TU family.

namespace FXParticleSystem
{

struct OrthoEmissionVelocityModuleTag;

template <class Tag>
class __declspec(novtable) ConcreteModuleTemplate
{
public:
	virtual ~ConcreteModuleTemplate();
};

typedef ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> OrthoEmissionVelocityConcreteTemplate;

// ??1?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
OrthoEmissionVelocityConcreteTemplate::~OrthoEmissionVelocityConcreteTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110f9cc;
	*(volatile unsigned int *)this = 0x01073758;
}

}
