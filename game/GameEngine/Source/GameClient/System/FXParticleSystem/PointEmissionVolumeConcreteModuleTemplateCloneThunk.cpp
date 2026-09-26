// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: PointEmissionVolume ConcreteModuleTemplate::clone

namespace FXParticleSystem
{

struct PointEmissionVolumeModuleTag
{
};

class PointEmissionVolumeModuleTemplate
{
public:
	virtual ~PointEmissionVolumeModuleTemplate();
};

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <class Tag>
class ConcreteModuleTemplate;

template <>
class ConcreteModuleTemplate<PointEmissionVolumeModuleTag> : public PointEmissionVolumeModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual PointEmissionVolumeModuleTemplate *clone() const;

private:
	unsigned char m_pad[0xc];
};

// ?clone@?@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVPointEmissionVolumeModuleTemplate@2@XZ
PointEmissionVolumeModuleTemplate *ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::clone() const
{
	return new ConcreteModuleTemplate<PointEmissionVolumeModuleTag>(*this);
}

}
