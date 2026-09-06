// ?d_002d2c20@@YAXXZ
// partial score=0.75 date=2026-09-06
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef unsigned int UnsignedInt;

class BfmeBaseTCB
{
public:
	void bfmeInitTCB();
};

extern UnsignedInt g_bfmeFlagTable[];

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();

	char m_prefix[0x110];
	UnsignedInt m_flags[0x3c];
	class BfmeFlagCallback *m_callback;
};

class BfmeFlagCallback
{
public:
	virtual void v00(UnsignedInt value);
	virtual void v01(UnsignedInt value);
	virtual void v02(UnsignedInt value);
	virtual void v03(UnsignedInt value);
	virtual void v04(UnsignedInt value);
	virtual void v05(UnsignedInt value);
	virtual void v06(UnsignedInt value);
	virtual void v07(UnsignedInt value);
	virtual void v08(UnsignedInt value);
	virtual void v09(UnsignedInt value);
	virtual void v10(UnsignedInt value);
	virtual void v11(UnsignedInt value);
	virtual void v12(UnsignedInt value);
	virtual void v13(UnsignedInt value);
};

struct BfmeFlagState
{
	char m_prefix[0x70];
	unsigned char m_mode;
	unsigned char m_guard;
	char m_between[2];
	UnsignedInt m_index;
};

__forceinline UnsignedInt bfmeLookupFlag(UnsignedInt index)
{
	return g_bfmeFlagTable[index];
}

class Rva002D2C20Thing
{
public:
	void update();
};

void Rva002D2C20Thing::update()
{
	BfmeOwnerVNI *owner = *(BfmeOwnerVNI **)((char *)this - 8);
	if (owner == 0)
		return;

	BfmeFlagState *state = *(BfmeFlagState **)((char *)this - 0xc);
	if (state == 0 || state->m_guard != 0)
		return;

	((BfmeBaseTCB *)((char *)this - 0x10))->bfmeInitTCB();
	BfmeFlagCallback *callback = owner->m_callback;
	if (callback == 0)
		return;

	if (state->m_mode != 0)
	{
		callback->v13(state->m_index);
		UnsignedInt bit = bfmeLookupFlag(state->m_index);
		UnsignedInt mask = 1U << (bit & 0x1f);
		UnsignedInt *word = &owner->m_flags[bit >> 5];
		if ((*word & mask) != 0)
		{
			*word &= ~mask;
			owner->bfmeApply1VNI();
		}
	}
	else
	{
		callback->v12(state->m_index);
		UnsignedInt bit = bfmeLookupFlag(state->m_index);
		UnsignedInt mask = 1U << (bit & 0x1f);
		UnsignedInt *word = &owner->m_flags[bit >> 5];
		if ((*word & mask) == 0)
		{
			*word |= mask;
			owner->bfmeApply1VNI();
		}
	}
}
