// ?bfmeCheckXR@BfmeOwnerXR@@QAE_NPAX@Z
// partial score=0.87 date=2026-09-23
// ?bfmeCheckXR@BfmeOwnerXR@@QAE_NPAX@Z

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class StealthUpdate
{
public:
	unsigned char m_pad00[0x2d];
	Bool m_field2d;
};

class BfmeXRResult
{
public:
	unsigned char m_pad00[0x14];
	int m_value14;
};

class BfmeXRChain
{
public:
	unsigned char m_pad00[4];
	BfmeXRChain *m_next;
	BfmeXRResult *friend_getFinalOverride();
};

class BfmeContain
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual UnsignedInt slot23();
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
	virtual UnsignedInt getContainCount(Bool countRiders) const;
};

class BfmePlayerXR
{
public:
	unsigned char m_pad1d8[0x1d8];
	BfmeXRChain *m_chain1d8;
	unsigned char m_pad1dc[0x238 - 0x1dc];
	UnsignedInt m_flags238;
	UnsignedInt m_flags23c;
	unsigned char m_pad240[0x24d - 0x240];
	Bool m_flag24d;
};

class BfmeObjectXR
{
public:
	unsigned char m_pad128[0x128];
	UnsignedInt m_status128;
	UnsignedInt m_status12c;
	UnsignedInt m_status130;
	unsigned char m_pad134[0x1fc - 0x134];
	BfmeContain *m_contain;
	StealthUpdate *findUpdateModule(NameKeyType key);
};

class BfmeOwnerXR
{
public:
	BfmePlayerXR *getPlayer()
	{
		return *(BfmePlayerXR **)((char *)this - 0x1c);
	}

	BfmeObjectXR *getObject()
	{
		return *(BfmeObjectXR **)((char *)this - 0x18);
	}

	bool bfmeCheckXR(void *argument);
};

bool BfmeOwnerXR::bfmeCheckXR(void *argument)
{
	BfmePlayerXR *const player = getPlayer();
	UnsignedInt flags238 = player->m_flags238;
	{
	BfmeObjectXR *const object = getObject();
	if ((flags238 & 1) != 0)
	{
		UnsignedInt objectStatus128 = object->m_status128;
		if ((objectStatus128 & 0x800) == 0)
			return 0;
	}
	if ((flags238 & 1) != 0)
	{
		UnsignedInt objectStatus130 = object->m_status130;
		if ((objectStatus130 & 0x1000) == 0)
			return 0;
	}

	UnsignedInt flags23c = player->m_flags23c;
	if ((flags23c & 1) != 0)
	{
		UnsignedInt objectStatus128 = object->m_status128;
		if ((objectStatus128 & 0x800) != 0)
			return 0;
	}
	if ((flags23c & 1) != 0)
	{
		UnsignedInt objectStatus130 = object->m_status130;
		if ((objectStatus130 & 0x1000) != 0)
			return 0;
	}
	}

	if (player->m_flag24d)
	{
		static NameKeyType key_StealthUpdate =
			TheNameKeyGenerator->nameToKey("StealthUpdate");

		BfmeObjectXR *stealthObject = *(BfmeObjectXR **)((char *)this - 0x18);
		StealthUpdate *module = stealthObject->findUpdateModule(key_StealthUpdate);
		if (module != 0 && module->m_field2d)
			return 0;
	}

	BfmeXRChain *chain = player->m_chain1d8;
	if (chain->m_next != 0 && chain->m_next->m_next != 0)
	{
		BfmeXRResult *final =
			chain->m_next->m_next->friend_getFinalOverride();
		int finalValue = final->m_value14;
		if (finalValue >= 0x27 && finalValue <= 0x28)
			{
				BfmeObjectXR *containmentObject =
					*(BfmeObjectXR **)((char *)this - 0x18);
				BfmeContain *contain = containmentObject->m_contain;
				if (contain == 0)
					return 0;
		UnsignedInt begin = contain->getContainCount(0);
				UnsignedInt end = contain->slot23();
				if (begin >= end)
					return 0;
			}
		}

	return 1;
}
