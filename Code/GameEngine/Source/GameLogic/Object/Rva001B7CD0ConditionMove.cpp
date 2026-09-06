// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Retail 0x001B7CD0 is an address-derived two-argument model-condition bit
// move.  The owner name is intentionally not guessed: the body has no named
// caller in the current source surface.  The helper is the existing pinned
// BfmeOwnerVNI::bfmeApply1VNI body reached by the retail ILT.

typedef unsigned int UnsignedInt;

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

class Rva001B7CD0Owner
{
public:
	void moveCondition(UnsignedInt from, UnsignedInt to);

private:
	unsigned char m_beforeConditionWords[0x110];
	UnsignedInt m_conditionWords[8];
};

void Rva001B7CD0Owner::moveCondition(UnsignedInt from, UnsignedInt to)
{
	UnsignedInt fromBit = 1U << (from & 0x1f);

	if ((m_conditionWords[from >> 5] & fromBit) == 0)
	{
		UnsignedInt toBit = 1U << (to & 0x1f);
		if ((m_conditionWords[to >> 5] & toBit) != 0)
			return;
	}

	m_conditionWords[from >> 5] &= ~fromBit;
	UnsignedInt toBit = 1U << (to & 0x1f);
	m_conditionWords[to >> 5] |= toBit;
	((BfmeOwnerVNI *)this)->bfmeApply1VNI();
}
