// cl: /DNDEBUG /MD /EHsc
// ModelConditionUpgrade::upgradeImplementation at retail 0x002D6840, 180 bytes.
// The constructor at 0x002D66D0 installs the vtable 0x010CD378, whose slot 9
// reaches this body through ILT 0x0001131A. Slot 9 is the call
// UpgradeMux::attemptUpgrade (0x002D9AD0) makes where Zero Hour's
// giveSelfUpgrade calls upgradeImplementation. Slot 7 (0x002D6930) is the
// mirror-image body that undoes this one. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

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
};

// Retail's Object::clearAndSetModelConditionFlags reaches the 0x000095ED ILT
// thunk, which the ledger owns as ?j_000095ed@@YAXXZ
// (game/gen_small/thunks_004.cpp). Call it by its defining name instead of
// through an undefined member.
extern void j_000095ed();
typedef void (Object::*ClearAndSetModelConditionFlagsCall)(
	const BfmeC1166 &, const BfmeC1166 & );

struct Rva002D6840PairData
{
	unsigned char pad[0x70];
	BfmeC1166 set;
	BfmeC1166 clear;
};

class ModelConditionUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void ModelConditionUpgrade::upgradeImplementation()
{
	Rva002D6840PairData *data =
		*(Rva002D6840PairData **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);

	union { void (*raw)(); ClearAndSetModelConditionFlagsCall member; } call;
	call.raw = j_000095ed;

	if (data->clear.any())
		(object->*call.member)(
			data->clear, BfmeC1166());

	if (data->set.any())
		(object->*call.member)(
			BfmeC1166(), data->set);
}
