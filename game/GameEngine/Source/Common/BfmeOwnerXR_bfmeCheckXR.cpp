// ?bfmeCheckXR@BfmeOwnerXR@@QAE_NPAX@Z
// Owner gate called by BfmeOwnerXR::Rva0025DDB0: status-bit gates against the
// holder's flags, a stealth refusal, then a final-override kind range check.

typedef unsigned char Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

protected:
	void *m_memoryPoolVTable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// Final override read through one extra inline link before the out-of-line walk.
class BfmeXRChain : public Overridable
{
public:
	BfmeXRChain *getFinalTemplate()
	{
		if (m_nextOverride)
			return (BfmeXRChain *)m_nextOverride->friend_getFinalOverride();
		return this;
	}

	UnsignedByte m_unreconstructed_00c[0x14 - 0x0c];
	int m_kind14;
};

class StealthUpdate
{
public:
	UnsignedByte m_unreconstructed_000[0x2d];
	Bool m_flag2d;
};

// Contain-module view: only the two virtual slots this body calls.
class Rva002A6C40Contain
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual UnsignedInt slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual UnsignedInt slot64(Bool flag) = 0;
};

class Object
{
public:
	StealthUpdate *findUpdateModule(NameKeyType key);

	UnsignedByte m_unreconstructed_000[0x128];
	UnsignedInt m_bits128;
	UnsignedByte m_unreconstructed_12c[0x130 - 0x12c];
	UnsignedInt m_bits130;
	UnsignedByte m_unreconstructed_134[0x1fc - 0x134];
	Rva002A6C40Contain *m_contain;
};

class BfmePlayerXR
{
public:
	UnsignedByte m_unreconstructed_000[0x1d8];
	BfmeXRChain *m_template1d8;
	UnsignedByte m_unreconstructed_1dc[0x238 - 0x1dc];
	UnsignedInt m_flags238;
	UnsignedInt m_flags23c;
	UnsignedByte m_unreconstructed_240[0x24d - 0x240];
	Bool m_flag24d;
};

class BfmeOwnerXR
{
public:
	bool bfmeCheckXR(void *item);

private:
	BfmePlayerXR *getHolder()
	{
		return *(BfmePlayerXR **)((char *)this - 0x1c);
	}

	Object *getObject()
	{
		return *(Object **)((char *)this - 0x18);
	}
};

// Function-scope object local plus per-test guarded field reads keep the holder
// flag in ecx and the object in eax; a nested block or && conditions do not.
bool BfmeOwnerXR::bfmeCheckXR(void *item)
{
	BfmePlayerXR *const holder = getHolder();
	Object *const object = getObject();
	UnsignedInt flags238 = holder->m_flags238;
	if ((flags238 & 1) != 0)
	{
		UnsignedInt bits128 = object->m_bits128;
		if ((bits128 & 0x800) == 0)
			return false;
	}
	if ((flags238 & 1) != 0)
	{
		UnsignedInt bits130 = object->m_bits130;
		if ((bits130 & 0x1000) == 0)
			return false;
	}

	UnsignedInt flags23c = holder->m_flags23c;
	if ((flags23c & 1) != 0)
	{
		UnsignedInt bits128 = object->m_bits128;
		if ((bits128 & 0x800) != 0)
			return false;
	}
	if ((flags23c & 1) != 0)
	{
		UnsignedInt bits130 = object->m_bits130;
		if ((bits130 & 0x1000) != 0)
			return false;
	}

	if (holder->m_flag24d)
	{
		static NameKeyType key_StealthUpdate = TheNameKeyGenerator->nameToKey("StealthUpdate");

		StealthUpdate *stealth = getObject()->findUpdateModule(key_StealthUpdate);
		if (stealth != 0 && stealth->m_flag2d)
			return false;
	}

	BfmeXRChain *final = holder->m_template1d8->getFinalTemplate();
	int kind = final->m_kind14;
	if (kind >= 0x27 && kind <= 0x28)
	{
		Rva002A6C40Contain *contain = getObject()->m_contain;
		if (contain == 0)
			return false;
		UnsignedInt first = contain->slot64(0);
		UnsignedInt second = contain->slot23();
		if (first >= second)
			return false;
	}

	return true;
}
