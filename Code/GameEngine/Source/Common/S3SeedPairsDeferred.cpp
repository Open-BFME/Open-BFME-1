// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: twenty-six more seeders, unlocked by one observation about the
// __cdecl hand-over helper: MSVC does not always clean its two arguments at
// the call.  It defers the `add esp,8` past the NEXT hand-over's vtable load,
// and in a run of helpers it merges several cleanups into one.  Nothing in
// the source says so -- the bodies here are written exactly like the ones in
// S3SeedPairsForms.cpp, and the cleanup lands wherever the scheduler puts it.
//
// This batch is helper-heavy: 46 of its hand-overs go through the __cdecl
// helper rather than a slot on the target.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	void releaseBuffer(void);

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

extern AsciiString TheBfmeCrateNameDefault;

class BfmeMgrF1D
{
public:
	void *registerObj(void *field);
};

extern BfmeMgrF1D *g_mgr12EF1D8;

struct BfmeSeedPair
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual bool bfmeSlot2(void);
	virtual bool bfmeSlot3(void);
	virtual bool bfmeSkip(void);		// slot 4, vtable+0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);		// slot 9, vtable+0x24
	virtual void bfmeSeed(BfmeSeedPair *pair);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);		// slot 12, vtable+0x30
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeTakeAt4C(void *item);		// slot 19, vtable+0x4C
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);		// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeTakeAt68(AsciiString *name);	// slot 26, vtable+0x68
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

struct BfmeFlagsAXB
{
	unsigned char m_bfmeOne;
	unsigned char m_bfmeTwo;
};

class BfmeSrcAXB;

class BfmeThingAXB
{
public:
	void bfmeSendAXB(BfmeSrcAXB *src, BfmeFlagsAXB *flags);
};

class BfmeAcceptManager
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
	virtual void *bfmeRegister(void *owner, void *item);
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
	virtual bool bfmeCheck(void *field);
};

// ?bfmeHandOver_000353C8@@YAXPAVBfmeSeedTarget@@PAX@Z		// 140 bytes
__declspec(noinline) void bfmeHandOver_000353C8(BfmeSeedTarget *target, void *item)
{
	const AsciiString *source;
	void *old = *(void **)item;

	if (old)
		source = (const AsciiString *)((char *)old + 0x20);
	else
		source = &TheBfmeCrateNameDefault;

	AsciiString name(*source);
	target->bfmeTakeAt68(&name);

	if (target->bfmeSlot1())
		*(void **)item = g_mgr12EF1D8->registerObj(&name);
}

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0002C41C

private:
	char m_bfmePad0[0xC];
	void *m_bfmeField;
};

// ?bfmeAccept@BfmeSubAccept_0002C41C@@QAEXPAVBfmeSeedTarget@@@Z		// 187 bytes
void BfmeSubAccept_0002C41C::bfmeAccept(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;
	volatile unsigned char accepted;

	if (target->bfmeSlot3())
		return;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 2;
	target->bfmeSeed(&pair);

	if (target->bfmeSlot2())
		accepted = !g_mgr12EF1D8
			? false
			: reinterpret_cast<BfmeAcceptManager *>(g_mgr12EF1D8)->bfmeCheck(m_bfmeField);
	target->bfmeTakeAt8C((void *)&accepted);

	void *item = m_bfmeField;
	target->bfmeTakeAt74(&item);
	reinterpret_cast<BfmeThingAXB *>(this)->bfmeSendAXB(
		reinterpret_cast<BfmeSrcAXB *>(target), reinterpret_cast<BfmeFlagsAXB *>(&pair));

	if (accepted && target->bfmeSlot1() && g_mgr12EF1D8)
		m_bfmeField = reinterpret_cast<BfmeAcceptManager *>(g_mgr12EF1D8)->bfmeRegister(this, item);
}

void bfmeHandOver_0000240A(BfmeSeedTarget *target, void *item);		// ILT 0x0000240A
void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);		// ILT 0x0000C9B4
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);		// ILT 0x0000FFE2
void bfmeHandOver_0002A450(BfmeSeedTarget *target, void *item);		// ILT 0x0002A450
void bfmeHandOver_000353C8(BfmeSeedTarget *target, void *item);		// ILT 0x000353C8
void bfmeHandOver_0003EE32(BfmeSeedTarget *target, void *item);		// ILT 0x0003EE32
void bfmeHandOver_0004420B(BfmeSeedTarget *target, void *item);		// ILT 0x0004420B

class Gen_0016BC50
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x60
	char m_bfmePad3[0x7];
	char m_bfmeItem3;				// +0x68
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x6C
};

class Gen_0016D210
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
};

class Gen_001F61B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000160B3

	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x20
};

class Gen_00215AF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
};

class Gen_00232590
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeItem0;				// +0x00
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x04
};

class Gen_00255F60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00001681

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x18
};

class Gen_00257D10
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0xEC
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0xF0
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0xF4
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0xF8
};

class Gen_0025EF10
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0xEC
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0xF0
};

class Gen_00286E30
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
};

class Gen_00295C70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x30
	char m_bfmeItem3;				// +0x31
	char m_bfmeItem4;				// +0x32
};

class Gen_00298FD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x30
};

class Gen_002A1280
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x2C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x30
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x34
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x38
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x3C
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x40
	char m_bfmeItem7;				// +0x41
};

class Gen_002B1490
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x38
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x3C
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x40
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x44
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x48
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x4C
	char m_bfmePad9[0x3];
	char m_bfmeItem9;				// +0x50
	char m_bfmePad10[0x3];
	char m_bfmeItem10;				// +0x54
};

class Gen_002B2150
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x28];
	char m_bfmeItem0;				// +0x28
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x2C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x30
	char m_bfmeItem3;				// +0x31
};

class Gen_002B3190
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00043441

	char m_bfmePad0[0x344];
	char m_bfmeItem0;				// +0x344
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x348
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x354
	char m_bfmeItem3;				// +0x355
};

class Gen_002B9EC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	BfmeSubAccept_0002C41C m_bfmeSub0;		// +0x24
	char m_bfmePad1[0x60];
	char m_bfmeItem1;				// +0x94
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x98
};

class Gen_002C4BD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0000EC6E

	char m_bfmePad0[0x344];
	char m_bfmeItem0;				// +0x344
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x348
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x34C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x350
};

class Gen_002C58B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00043441

	char m_bfmePad0[0x344];
	void *m_bfmeHeld0;				// +0x344
	char m_bfmeItem1;				// +0x348
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x34C
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x358
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x35C
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x360
	char m_bfmeItem6;				// +0x361
	char m_bfmePad7[0x2];
	BfmeSubAccept_0002C41C m_bfmeSub7;		// +0x364
};

class Gen_002CEED0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001D043

	char m_bfmePad0[0x88];
	char m_bfmeItem0;				// +0x88
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x8C
};

class Gen_002D0550
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x34
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x38
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x3C
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x40
};

class Gen_005F8F70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x28
};

class Gen_005F9E40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x34
};

class Gen_005FA160
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x28
};

class Gen_005FB150
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x30
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x3C
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x48
	char m_bfmePad4[0xB];
	char m_bfmeItem4;				// +0x54
	char m_bfmePad5[0xB];
	char m_bfmeItem5;				// +0x60
	char m_bfmePad6[0xB];
	char m_bfmeItem6;				// +0x6C
	char m_bfmePad7[0xB];
	char m_bfmeItem7;				// +0x78
	char m_bfmePad8[0xB];
	char m_bfmeItem8;				// +0x84
	char m_bfmePad9[0xB];
	char m_bfmeItem9;				// +0x90
	char m_bfmePad10[0xB];
	char m_bfmeItem10;				// +0x9C
};

class Gen_00603240
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003D2A8

	char m_bfmePad0[0xC];
	char m_bfmeItem0;				// +0x0C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x10
};

// ?bfmeSeed@Gen_0016BC50@@QAEXPAVBfmeSeedTarget@@@Z		116 bytes
void Gen_0016BC50::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt4C(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem0);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem3);
		target->bfmeTakeAt8C(&m_bfmeItem4);
	}
}

// ?bfmeSeed@Gen_0016D210@@QAEXPAVBfmeSeedTarget@@@Z		68 bytes
void Gen_0016D210::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
}

// ?bfmeSeed@Gen_001F61B0@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_001F61B0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
		bfmeHandOver_0002A450(target, &m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00215AF0@@QAEXPAVBfmeSeedTarget@@@Z		83 bytes
void Gen_00215AF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	target->bfmeTakeAt74(&m_bfmeItem0);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_00232590@@QAEXPAVBfmeSeedTarget@@@Z		58 bytes
void Gen_00232590::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_000353C8(target, &m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_00255F60@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_00255F60::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00257D10@@QAEXPAVBfmeSeedTarget@@@Z		126 bytes
void Gen_00257D10::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000FFE2(target, &m_bfmeItem0);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
		target->bfmeTakeAt78(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem4);
		target->bfmeTakeAt78(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_0025EF10@@QAEXPAVBfmeSeedTarget@@@Z		99 bytes
void Gen_0025EF10::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000FFE2(target, &m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00286E30@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_00286E30::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
	target->bfmeTakeAt74(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_00295C70@@QAEXPAVBfmeSeedTarget@@@Z		118 bytes
void Gen_00295C70::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem3);
		target->bfmeTakeAt8C(&m_bfmeItem4);
	}
}

// ?bfmeSeed@Gen_00298FD0@@QAEXPAVBfmeSeedTarget@@@Z		98 bytes
void Gen_00298FD0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_002A1280@@QAEXPAVBfmeSeedTarget@@@Z		140 bytes
void Gen_002A1280::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0004420B(target, &m_bfmeItem1);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem2);
	target->bfmeTakeAt78(&m_bfmeItem3);
	target->bfmeTakeAt78(&m_bfmeItem4);
	target->bfmeTakeAt8C(&m_bfmeItem6);
	target->bfmeTakeAt78(&m_bfmeItem5);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem7);
}

// ?bfmeSeed@Gen_002B1490@@QAEXPAVBfmeSeedTarget@@@Z		184 bytes
void Gen_002B1490::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt6C(&m_bfmeItem0);
		target->bfmeTakeAt6C(&m_bfmeItem1);
		target->bfmeTakeAt60(&m_bfmeItem2);
		target->bfmeTakeAt24(&m_bfmeItem3, 4);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt6C(&m_bfmeItem5);
		target->bfmeTakeAt78(&m_bfmeItem6);
		target->bfmeTakeAt8C(&m_bfmeItem7);
		target->bfmeTakeAt74(&m_bfmeItem8);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem9);
		target->bfmeTakeAt6C(&m_bfmeItem10);
	}
}

// ?bfmeSeed@Gen_002B2150@@QAEXPAVBfmeSeedTarget@@@Z		97 bytes
void Gen_002B2150::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt8C(&m_bfmeItem3);
}

// ?bfmeSeed@Gen_002B3190@@QAEXPAVBfmeSeedTarget@@@Z		109 bytes
void Gen_002B3190::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt60(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem3);
	bfmeAccept(target);

}

// ?bfmeSeed@Gen_002B9EC0@@QAEXPAVBfmeSeedTarget@@@Z		98 bytes
void Gen_002B9EC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		m_bfmeSub0.bfmeAccept(target);
	}
	bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_002C4BD0@@QAEXPAVBfmeSeedTarget@@@Z		104 bytes
void Gen_002C4BD0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem2);
	target->bfmeTakeAt8C(&m_bfmeItem3);
}

// ?bfmeSeed@Gen_002C58B0@@QAEXPAVBfmeSeedTarget@@@Z		177 bytes
void Gen_002C58B0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt30(m_bfmeHeld0);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
		target->bfmeTakeAt60(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem3);
		target->bfmeTakeAt78(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem5);
		target->bfmeTakeAt8C(&m_bfmeItem6);
		m_bfmeSub7.bfmeAccept(target);
	}
}

// ?bfmeSeed@Gen_002CEED0@@QAEXPAVBfmeSeedTarget@@@Z		82 bytes
void Gen_002CEED0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
		target->bfmeTakeAt6C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_002D0550@@QAEXPAVBfmeSeedTarget@@@Z		123 bytes
void Gen_002D0550::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem5);
		target->bfmeTakeAt74(&m_bfmeItem4);
	}
}

// ?bfmeSeed@Gen_005F8F70@@QAEXPAVBfmeSeedTarget@@@Z		60 bytes
void Gen_005F8F70::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0003EE32(target, &m_bfmeItem0);
	bfmeHandOver_0003EE32(target, &m_bfmeItem1);
}

// ?bfmeSeed@Gen_005F9E40@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_005F9E40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0003EE32(target, &m_bfmeItem0);
	bfmeHandOver_0003EE32(target, &m_bfmeItem1);
	bfmeHandOver_0003EE32(target, &m_bfmeItem2);
}

// ?bfmeSeed@Gen_005FA160@@QAEXPAVBfmeSeedTarget@@@Z		60 bytes
void Gen_005FA160::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0003EE32(target, &m_bfmeItem0);
	bfmeHandOver_0003EE32(target, &m_bfmeItem1);
}

// ?bfmeSeed@Gen_005FB150@@QAEXPAVBfmeSeedTarget@@@Z		164 bytes
void Gen_005FB150::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt60(&m_bfmeItem0);
	target->bfmeTakeAt60(&m_bfmeItem1);
	bfmeHandOver_0003EE32(target, &m_bfmeItem2);
	bfmeHandOver_0003EE32(target, &m_bfmeItem3);
	bfmeHandOver_0003EE32(target, &m_bfmeItem4);
	bfmeHandOver_0003EE32(target, &m_bfmeItem5);
	bfmeHandOver_0003EE32(target, &m_bfmeItem6);
	bfmeHandOver_0003EE32(target, &m_bfmeItem7);
	bfmeHandOver_0003EE32(target, &m_bfmeItem8);
	bfmeHandOver_0003EE32(target, &m_bfmeItem9);
	bfmeHandOver_0003EE32(target, &m_bfmeItem10);
}

// ?bfmeSeed@Gen_00603240@@QAEXPAVBfmeSeedTarget@@@Z		80 bytes
void Gen_00603240::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		bfmeHandOver_0000240A(target, &m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
	}
}
