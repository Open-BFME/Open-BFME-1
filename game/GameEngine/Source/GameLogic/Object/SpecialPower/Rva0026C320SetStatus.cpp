// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class SpecialPowerTemplate;
class SpecialPowerModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void invoke(UnsignedInt arg) = 0;
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
	void notifyModelConditionChanged();
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spTemplate) const;
};

class Rva0026C320ModuleData
{
public:
	char m_pad00[0x1d8];
	SpecialPowerTemplate *m_template;
};

class Rva0026C320Owner
{
public:
	void apply(Object *object);

private:
	char m_pad00[4];
	Rva0026C320ModuleData *m_data;
};

// ?apply@Rva0026C320Owner@@QAEXPAVObject@@@Z
void Rva0026C320Owner::apply(Object *object)
{
	object->setStatus(MAKE_OBJECT_STATUS_MASK(15), false);
	object->setStatus(MAKE_OBJECT_STATUS_MASK(16), false);
	UnsignedInt *flags = (UnsignedInt *)((char *)object + 0x12c);
	UnsignedInt value = *flags;
	if ((value & 0x1000000) != 0)
	{
		*flags = value & ~0x1000000u;
		object->notifyModelConditionChanged();
	}
	SpecialPowerTemplate *power = m_data->m_template;
	SpecialPowerModuleInterface *mod = object->getSpecialPowerModule(power);
	if (mod != 0)
		mod->invoke(0);
}
