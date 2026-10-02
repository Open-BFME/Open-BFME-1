// cl: /DNDEBUG /MD /EHsc
// ScavengerSpecialPower::doSpecialPower at retail 0x00265A00: slot 11 of the
// SpecialPowerModuleInterface table 0x010B6E88, which ScavengerSpecialPower's registered
// constructor 0x002658B0 stores at +0x10. The body is reached only through ILT
// 0x00046E61, whose VA appears once in the image. Object::doSpecialPower
// (0x001C3790) calls slot 11 (+0x2C) with commandOptions; the body ends `ret 4`.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md


class Rva00265A00Result
{
public:
	void touch();
};

class Rva00265A00Owner
{
public:
	Rva00265A00Result *lookup( int key );
};

struct Rva00265A00Record
{
	unsigned char m_lead[ 0x210 ];
	int m_key;
};

typedef unsigned int UnsignedInt;

// The trailing call goes through ILT 0x00041BCD to 0x0026A550,
// SpecialPowerModule::doSpecialPower, the base body every non-overriding
// power's slot 11 holds; a qualified call makes it direct.
class SpecialPowerModule
{
public:
	virtual void doSpecialPower( UnsignedInt commandOptions );
};

class ScavengerSpecialPower
{
public:
	virtual void doSpecialPower( UnsignedInt value );
};

void ScavengerSpecialPower::doSpecialPower( UnsignedInt value )
{
	Rva00265A00Record *record = *(Rva00265A00Record **)( (char *)this - 0x0c );
	Rva00265A00Owner *owner = *(Rva00265A00Owner **)( (char *)this - 0x08 );
	owner->lookup( record->m_key )->touch();
	reinterpret_cast<SpecialPowerModule *>( this )->SpecialPowerModule::doSpecialPower( value );
}
