// Five guarded global dispatchers.
//
// Each tests a global -- four of them a pointer variable, one the fourth
// argument -- and calls through it only when it is not null. The guard's
// pointer is what lands in ecx, so the call is a member of whatever the global
// names, not a free function.
//
// Two dispatch virtually and append a literal zero; three call a member
// directly with the two arguments they were handed. The ret immediate
// separates the conventions: ret 4 on the virtual pair makes those __stdcall
// with one argument, while the bare ret on the rest makes them __cdecl.


class Gen_002EDA90Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot35(void);
	virtual void bfmeSlot36(void);
	virtual void bfmeSlot37(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeSlot39(void);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot41(void);
	virtual void bfmeSlot42(void);
	virtual void bfmeSlot43(void);
	virtual void bfmeSlot44(void);
	virtual void bfmeSlot45(void);
	virtual void bfmeSlot46(void);
	virtual void bfmeSlot47(void);
	virtual void bfmeSlot48(void);
	virtual void bfmeSlot49(void);
	virtual void bfmeSlot50(void);
	virtual void bfmeSlot51(void);
	virtual void bfmeSlot52(void);
	virtual void bfmeSlot53(void);
	virtual void bfmeSlot54(void);
	virtual void bfmeSlot55(void);
	virtual void bfmeInvoke(void *item, int flag);	// slot 56, vtable+0xE0
};

extern Gen_002EDA90Target *TheBfmeTarget_002EDA90;			// 0x012ED668

void __stdcall bfmeDispatch_002EDA90(void *item);

class Gen_002EDAC0Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot35(void);
	virtual void bfmeSlot36(void);
	virtual void bfmeSlot37(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeSlot39(void);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot41(void);
	virtual void bfmeSlot42(void);
	virtual void bfmeSlot43(void);
	virtual void bfmeSlot44(void);
	virtual void bfmeSlot45(void);
	virtual void bfmeSlot46(void);
	virtual void bfmeSlot47(void);
	virtual void bfmeSlot48(void);
	virtual void bfmeSlot49(void);
	virtual void bfmeSlot50(void);
	virtual void bfmeSlot51(void);
	virtual void bfmeSlot52(void);
	virtual void bfmeSlot53(void);
	virtual void bfmeSlot54(void);
	virtual void bfmeSlot55(void);
	virtual void bfmeSlot56(void);
	virtual void bfmeInvoke(void *item, int flag);	// slot 57, vtable+0xE4
};

extern Gen_002EDAC0Target *TheBfmeTarget_002EDAC0;			// 0x012ED668

void __stdcall bfmeDispatch_002EDAC0(void *item);

class Gen_006CDF70Target
{
public:
	void bfmeInvoke(void *first, void *second);
};

extern Gen_006CDF70Target *TheBfmeTarget_006CDF70;

void bfmeDispatch_006CDF70(void *first, void *second);

class Gen_009EBA60Target
{
public:
	void bfmeInvoke(void *first, void *second);
};

extern Gen_009EBA60Target *TheBfmeTarget_009EBA60;

void bfmeDispatch_009EBA60(void *first, void *second);

class Gen_0064C6A0Target
{
public:
	void bfmeInvoke(void *first, void *second);
};

void bfmeDispatch_0064C6A0(void *first, void *second, void *third, Gen_0064C6A0Target *target);

// ?bfmeDispatch_002EDA90@@YGXPAX@Z
void __stdcall bfmeDispatch_002EDA90(void *item)
{
	if (TheBfmeTarget_002EDA90)
		TheBfmeTarget_002EDA90->bfmeInvoke(item, 0);
}

// ?bfmeDispatch_002EDAC0@@YGXPAX@Z
void __stdcall bfmeDispatch_002EDAC0(void *item)
{
	if (TheBfmeTarget_002EDAC0)
		TheBfmeTarget_002EDAC0->bfmeInvoke(item, 0);
}

// ?bfmeDispatch_006CDF70@@YAXPAX0@Z
void bfmeDispatch_006CDF70(void *first, void *second)
{
	if (TheBfmeTarget_006CDF70)
		TheBfmeTarget_006CDF70->bfmeInvoke(first, second);
}

// ?bfmeDispatch_009EBA60@@YAXPAX0@Z
void bfmeDispatch_009EBA60(void *first, void *second)
{
	if (TheBfmeTarget_009EBA60)
		TheBfmeTarget_009EBA60->bfmeInvoke(first, second);
}

// ?bfmeDispatch_0064C6A0@@YAXPAX00PAVGen_0064C6A0Target@@@Z
void bfmeDispatch_0064C6A0(void *first, void *second, void *third, Gen_0064C6A0Target *target)
{
	if (target)
		target->bfmeInvoke(first, second);
}
