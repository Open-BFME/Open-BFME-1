// stlport
// cl: /DNDEBUG /MD /EHsc
// BFME's structure test inlines the template flag check and constructs the
// five-kind mask on the stack.  This focused TU keeps that six-dword mask
// separate from the reference Object.cpp layout.

#include <bitset>

typedef bool Bool;
typedef int Int;

class Overridable
{
public:
	void *m_vptr;
	Overridable *m_nextOverride;

	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
};

class ThingTemplate : public Overridable
{
};

class Object
{
public:
	Bool isNonFactionStructure(void) const;
};

class BfmeKindOfMask
{
public:
	__forceinline BfmeKindOfMask(Int idx1, Int idx2, Int idx3, Int idx4, Int idx5)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
		m_bits.set(idx4);
		m_bits.set(idx5);
	}

private:
	std::bitset<192> m_bits;
};

class BfmeKindOfTester
{
public:
	Bool isAnyKindOf(const BfmeKindOfMask &mask) const;
};

// ?isNonFactionStructure@Object@@QBE_NXZ
Bool Object::isNonFactionStructure(void) const
{
	const ThingTemplate *tmplate = *(const ThingTemplate **)((const char *)this + 4);
	if (tmplate && *(const ThingTemplate **)((const char *)tmplate + 4))
		tmplate = (const ThingTemplate *)tmplate->getFinalOverride();
	return (*(const unsigned char *)((const char *)tmplate + 0xC8) & 0x80) != 0 &&
		!reinterpret_cast<const BfmeKindOfTester *>(this)->isAnyKindOf(
			BfmeKindOfMask(61, 62, 63, 64, 134));
}
