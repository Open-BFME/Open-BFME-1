// cl: /DNDEBUG /MD /EHsc
// ModelConditionUpgrade::upgradeImplementation at retail 0x002D6930, 180 bytes.
// The vtable at 0x010CD378 puts this body in slot 7. The constructor at
// 0x002D66D0 installs that vtable for ModelConditionUpgrade.

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

struct BfmeModelConditionUpgradeDataAAN
{
	unsigned char pad[0x70];
	BfmeC1166 clear;
	BfmeC1166 set;
};

class ModelConditionUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void ModelConditionUpgrade::upgradeImplementation()
{
	BfmeModelConditionUpgradeDataAAN *data =
		*(BfmeModelConditionUpgradeDataAAN **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);

	if (data->set.any())
		object->clearAndSetModelConditionFlags(
			BfmeC1166(), data->set);

	if (data->clear.any())
		object->clearAndSetModelConditionFlags(
			data->clear, BfmeC1166());
}
