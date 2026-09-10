// ?rva001CF8F0@Object@@QAEX_N@Z
// partial score=0.92 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc-
// stlport
// Object status/model-condition helper at retail RVA 0x001CF8F0 (111 bytes).
// ObjectSetChanting is the named caller; the public Object method spelling is
// not recovered, so the implementation keeps an address-derived name.

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" void *memset(void *destination, int value, unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameClient/DrawModule.h
class ModelConditionFlags
{
public:
	void set(Int bit)
	{
		m_bits[(UnsignedInt)bit >> 5] |= 1 << ((UnsignedInt)bit & 31);
	}
	UnsignedInt m_bits[3];
};

class KindOfFlags
{
public:
	UnsignedInt m_unused0 : 20;
	UnsignedInt m_alwaysVisible : 1;
	UnsignedInt m_unused1 : 11;
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xd4 - 0x08];
	KindOfFlags m_kindof;

	__forceinline Bool isKindOf(Int kind) const
	{
		return (m_kindof.m_alwaysVisible != 0) && (kind == 20);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void applyRva1C7370(const ModelConditionFlags &flags, Bool set);
	void clearModelConditionState(Int flag);
	void rva001CF8F0(Bool flag);

private:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x214 - 0x08];
	Object *m_containedBy;
};

void Object::rva001CF8F0(Bool flag)
{
	Object *object = this;
	for (;;)
	{
		if (flag)
		{
			ModelConditionFlags flags = {};
			flags.set(0x34);
			object->applyRva1C7370(flags, true);
		}
		else
		{
			object->clearModelConditionState(0x34);
		}

		object = object->m_containedBy;
		if (object == 0)
			return;
		ThingTemplate *thingTemplate = object->m_template;
		if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
		{
			thingTemplate = const_cast<ThingTemplate *>(
				reinterpret_cast<const ThingTemplate *>(
					thingTemplate->m_nextOverride->getFinalOverride()));
		}
		const UnsignedInt kindOf = *reinterpret_cast<const volatile UnsignedInt *>(
			reinterpret_cast<const char *>(thingTemplate) + 0xd4);
		if (!(kindOf & (1u << 20)))
			return;
	}
}
