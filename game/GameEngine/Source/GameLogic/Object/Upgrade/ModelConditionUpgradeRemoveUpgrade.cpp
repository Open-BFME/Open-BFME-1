// cl: /DNDEBUG /MD /EHsc
// ModelConditionUpgrade::removeUpgrade (UpgradeMux slot 7) at retail 0x002D6930, 180 bytes.
// The vtable at 0x010CD378 puts this body in slot 7. The constructor at
// 0x002D66D0 installs that vtable for ModelConditionUpgrade.
// Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot),
// a virtual that UpgradeMux::attemptUpgrade (0x002D9AD0)
// never calls; slot 9 is upgradeImplementation (0x002D6840), which this
// body undoes.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

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

struct BfmeModelConditionUpgradeDataAAN
{
	unsigned char pad[0x70];
	BfmeC1166 clear;
	BfmeC1166 set;
};

class ModelConditionUpgrade
{
protected:
	virtual void removeUpgrade();
};

void ModelConditionUpgrade::removeUpgrade()
{
	BfmeModelConditionUpgradeDataAAN *data =
		*(BfmeModelConditionUpgradeDataAAN **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);

	union { void (*raw)(); ClearAndSetModelConditionFlagsCall member; } call;
	call.raw = j_000095ed;

	if (data->set.any())
		(object->*call.member)( BfmeC1166(), data->set );

	if (data->clear.any())
		(object->*call.member)( data->clear, BfmeC1166() );
}
