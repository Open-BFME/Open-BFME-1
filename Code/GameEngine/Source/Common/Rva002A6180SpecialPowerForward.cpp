// Clean reconstruction of the address-derived special-power forwarder at
// retail RVA 0x002A6180.

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate ) const;
};

class Rva002A6180TemplateHolder
{
public:
	char m_padding[0x1D8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	__forceinline const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPowerTemplate;
	}
};

class Rva002A6180
{
public:
	SpecialPowerModuleInterface *forward();

private:
	char m_padding[4];
	Rva002A6180TemplateHolder *m_templateHolder;
	Object *m_object;
};

SpecialPowerModuleInterface *Rva002A6180::forward()
{
	return m_object->getSpecialPowerModule(
		m_templateHolder->getSpecialPowerTemplate() );
}
