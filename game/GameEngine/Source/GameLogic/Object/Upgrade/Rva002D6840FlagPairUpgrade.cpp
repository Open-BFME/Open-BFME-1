// cl: /DNDEBUG /MD /EHsc
// Machine twin of ?upgradeImplementation@ModelConditionUpgrade@@MAEXXZ at
// 0x002D6930 (ModelConditionUpgradeUpgradeImplementation.cpp): identical
// shape and single callee (0x000095ed, clearAndSetModelConditionFlags), but
// this owner's two BfmeC1166 flag fields sit in the OPPOSITE struct order
// (set before clear) so the higher-offset field is checked first and each
// call's argument roles are swapped relative to the landed twin. No named
// caller, vtable slot or string anchor proves the owning class, so the
// class keeps its address token.

typedef unsigned int UnsignedInt;

class BfmeC1166
{
public:
	bool any() const
	{
		for (UnsignedInt i = 0; i < 10; ++i)
			if (m_bits[i] != 0)
				return true;

		return false;
	}

	int m_bits[10];
};

class Object
{
public:
	void clearAndSetModelConditionFlags(
		const BfmeC1166 &clear,
		const BfmeC1166 &set);
};

struct Rva002D6840PairData
{
	unsigned char pad[0x70];
	BfmeC1166 set;
	BfmeC1166 clear;
};

class Rva002D6840FlagPairUpgrade
{
public:
	void applyFlagPair();
};

void Rva002D6840FlagPairUpgrade::applyFlagPair()
{
	Rva002D6840PairData *data =
		*(Rva002D6840PairData **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);

	if (data->clear.any())
		object->clearAndSetModelConditionFlags(
			data->clear, BfmeC1166());

	if (data->set.any())
		object->clearAndSetModelConditionFlags(
			BfmeC1166(), data->set);
}
