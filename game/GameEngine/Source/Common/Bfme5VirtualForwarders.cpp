// Four six-argument virtual forwarders.
//
// Each calls a fixed slot, hands all six of its arguments to a slot that
// differs per class, and then calls another fixed slot. The vptr is re-read
// before every call because each of them could have changed it.
//
// The six arguments are pushed back to front and each is loaded from a slot
// eight bytes further up than the last push left esp, which is what makes the
// displacements all read 0x18. The middle slot -- 0xB8, 0xBC, 0xC8 or 0xCC --
// is the only difference between the four.

class BfmeForwardBase
{
public:
	virtual void bfmeSlot_00(void);
	virtual void bfmeSlot_04(void);
	virtual void bfmeSlot_08(void);
	virtual void bfmeSlot_0C(void);
	virtual void bfmeSlot_10(void);
	virtual void bfmeSlot_14(void);
	virtual void bfmeSlot_18(void);
	virtual void bfmeSlot_1C(void);
	virtual void bfmeSlot_20(void);
	virtual void bfmeSlot_24(void);
	virtual void bfmeSlot_28(void);
	virtual void bfmeSlot_2C(void);
	virtual void bfmeSlot_30(void);
	virtual void bfmeSlot_34(void);
	virtual void bfmeSlot_38(void);
	virtual void bfmeSlot_3C(void);
	virtual void bfmeSlot_40(void);
	virtual void bfmeSlot_44(void);
	virtual void bfmeSlot_48(void);
	virtual void bfmeSlot_4C(void);
	virtual void bfmeSlot_50(void);
	virtual void bfmeSlot_54(void);
	virtual void bfmeSlot_58(void);
	virtual void bfmeSlot_5C(void);
	virtual void bfmeSlot_60(void);
	virtual void bfmeSlot_64(void);
	virtual void bfmeSlot_68(void);
	virtual void bfmeSlot_6C(void);
	virtual void bfmeSlot_70(void);
	virtual void bfmeSlot_74(void);
	virtual void bfmeSlot_78(void);
	virtual void bfmeSlot_7C(void);
	virtual void bfmeSlot_80(void);
	virtual void bfmeSlot_84(void);
	virtual void bfmeSlot_88(void);
	virtual void bfmeSlot_8C(void);
	virtual void bfmeSlot_90(void);
	virtual void bfmeSlot_94(void);
	virtual void bfmeSlot_98(void);
	virtual void bfmeSlot_9C(void);
	virtual void bfmeSlot_A0(void);
	virtual void bfmeSlot_A4(void);
	virtual void bfmeSlot_A8(void);
	virtual void bfmeSlot_AC(void);
	virtual void bfmeBefore(void);				// slot +0xB0
	virtual void bfmeSlot_B4(void);
	virtual void bfmeWork_B8(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);	// slot +0xB8
	virtual void bfmeWork_BC(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);	// slot +0xBC
	virtual void bfmeSlot_C0(void);
	virtual void bfmeSlot_C4(void);
	virtual void bfmeWork_C8(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);	// slot +0xC8
	virtual void bfmeWork_CC(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);	// slot +0xCC
	virtual void bfmeSlot_D0(void);
	virtual void bfmeSlot_D4(void);
	virtual void bfmeSlot_D8(void);
	virtual void bfmeAfter(void);				// slot +0xDC
};

class Gen_00433690 : public BfmeForwardBase
{
public:
	void bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
};

class Gen_00479E00 : public BfmeForwardBase
{
public:
	void bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
};

class Gen_00793C70 : public BfmeForwardBase
{
public:
	void bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
};

class Gen_00793CD0 : public BfmeForwardBase
{
public:
	void bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);
};

// ?bfmeRun@Gen_00433690@@QAEXPAX00000@Z
void Gen_00433690::bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6)
{
	bfmeBefore();
	bfmeWork_BC(a1, a2, a3, a4, a5, a6);
	bfmeAfter();
}

// ?bfmeRun@Gen_00479E00@@QAEXPAX00000@Z
void Gen_00479E00::bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6)
{
	bfmeBefore();
	bfmeWork_B8(a1, a2, a3, a4, a5, a6);
	bfmeAfter();
}

// ?bfmeRun@Gen_00793C70@@QAEXPAX00000@Z
void Gen_00793C70::bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6)
{
	bfmeBefore();
	bfmeWork_C8(a1, a2, a3, a4, a5, a6);
	bfmeAfter();
}

// ?bfmeRun@Gen_00793CD0@@QAEXPAX00000@Z
void Gen_00793CD0::bfmeRun(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6)
{
	bfmeBefore();
	bfmeWork_CC(a1, a2, a3, a4, a5, a6);
	bfmeAfter();
}
