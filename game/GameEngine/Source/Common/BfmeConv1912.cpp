// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// stlport
#include <bitset>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeAgentBH;

// Retail ILT 0x000044C1 (targets/game/reverse/functions.csv, gen-thunk row
// ?j_000044c1@@YAXXZ) is a 5-byte `jmp 0x6b2080`, i.e. RVA 0x002B2080, which
// the ledger matches as
// ?handle@Gen002B2080@@QAEXPAVFlagPairTarget@@@Z
// (game/GameEngine/Source/GameLogic/AI/Gen002B2080Handle.cpp). Only the one
// member is spelled here, so no layout of that class is imported; the caller
// passes its own `this` and the same pointer the ILT took, exactly as retail
// does (ecx + one pushed argument, `ret 4` on the callee side).
class FlagPairTarget;

class Gen002B2080
{
public:
	void handle(FlagPairTarget *target);
};

struct BfmeInfoBH
{
	unsigned char m_bfmeFlagBH;
	unsigned char m_bfmeLevelBH;
};

struct __declspec(align(4)) BfmeSubTwoVersionBH
{
	unsigned char version;
	unsigned char current;
};

struct BfmeSubTwoExceptionBH
{
	char *text;
	int tag;
};

class Xfer
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual bool save() = 0;
	virtual void slot03() = 0;
	virtual bool crc() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void xferUser(void *data, int size) = 0;
	virtual void version(BfmeSubTwoVersionBH *value) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void text(AsciiString *value) = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void integer(int *value) = 0;
};

template <int NUMBITS>
class BitFlags
{
public:
	_STL::bitset<NUMBITS> m_bits;
	void xfer(Xfer *xfer);
	static const char **getBitNames() { return s_bitNameList; }
private:
	static const char *s_bitNameList[];
};

extern unsigned char g_bfmeTableDH[];
extern int __cdecl bfmeLookup_001c6340(void *name);
extern "C" BfmeSubTwoExceptionBH *__cdecl bfmeFormatText(
	BfmeSubTwoExceptionBH *exception, int reserved, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *exception, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class BfmeAgentBH
{
public:
	virtual void bfmeSlot00BH();
	virtual char bfmeReadingBH();
	virtual void bfmeSlot02BH();
	virtual void bfmeSlot03BH();
	virtual char bfmeSkipBH();
	virtual void bfmeSlot05BH();
	virtual void bfmeSlot06BH();
	virtual void bfmeSlot07BH();
	virtual void bfmeSlot08BH();
	virtual void bfmeSlot09BH();
	virtual void bfmeFillBH(BfmeInfoBH *info);
	virtual void bfmeSlot11BH();
	virtual void bfmeSlot12BH();
	virtual void bfmeSlot13BH();
	virtual void bfmeSlot14BH();
	virtual void bfmeSlot15BH();
	virtual void bfmeSlot16BH();
	virtual void bfmeSlot17BH();
	virtual void bfmeSlot18BH();
	virtual void bfmeSlot19BH();
	virtual void bfmeSlot20BH();
	virtual void bfmeSlot21BH();
	virtual void bfmeSlot22BH();
	virtual void bfmeSlot23BH();
	virtual void bfmeMarkBH(void *dst);
	virtual void bfmeSlot25BH();
	virtual void bfmeSlot26BH();
	virtual void bfmeSlot27BH();
	virtual void bfmeSlot28BH();
	virtual void bfmeSlot29BH();
	virtual void bfmeSlot30BH();
	virtual void bfmeSlot31BH();
	virtual void bfmeSlot32BH();
	virtual void bfmeSlot33BH();
	virtual void bfmeSlot34BH();
	virtual void bfmeByteBH(unsigned char *dst);
};

class BfmeSubOneBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);

	unsigned char m_bfmePadBH[0x28];
};

class BfmeSubTwoBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);

	unsigned char m_bfmePadBH[0xc];
};

class BfmeHostBH
{
public:
	void bfmeSaveBH(BfmeAgentBH *ag);
	void bfmeOnBH();
	void bfmeOffBH();

	unsigned char m_bfmeHeadBH[0x24];
	unsigned char m_bfmeSlotABH[4];
	unsigned char m_bfmePadOneBH[8];
	BfmeSubOneBH m_bfmeSubOneBH;
	BfmeSubTwoBH m_bfmeSubTwoBH;
	unsigned char m_bfmeSlotDBH;
	unsigned char m_bfmeStateBH;
};

void BfmeSubTwoBH::bfmeSaveBH(BfmeAgentBH *ag)
{
	Xfer *xfer = reinterpret_cast<Xfer *>(ag);
	BfmeSubTwoVersionBH version;
	version.version = 1;
	version.current = 1;
	xfer->version(&version);

	if (xfer->crc())
	{
		reinterpret_cast<BitFlags<86> *>(this)->xfer(xfer);
		return;
	}

	_STL::bitset<86> *bits = reinterpret_cast<_STL::bitset<86> *>(this);
	if (xfer->save())
	{
		int count = bits->count();
		xfer->integer(&count);
		for (int i = 0; i < 86; ++i)
		{
			if (bits->_Unchecked_test(i) && BitFlags<86>::getBitNames()[i])
			{
				AsciiString name(BitFlags<86>::getBitNames()[i]);
				xfer->text(&name);
				--count;
			}
		}
	}
	else
	{
		bits->reset();
		int count;
		xfer->integer(&count);
		AsciiString name;
		for (int i = 0; i < count; ++i)
		{
			xfer->text(&name);
			const char *value = *reinterpret_cast<const char *const *>(&name);
			if (value != 0)
				value += 8;
			else
				value = "";

			int bit = bfmeLookup_001c6340(const_cast<char *>(value));
			if (bit < 0)
			{
				BfmeSubTwoExceptionBH exception;
				bfmeFormatText(&exception, 0, 0);
				_CxxThrowException(&exception, &g_guardTargetTypeThrowInfo);
			}
			bits->_Unchecked_set(bit);
		}
	}
}

void BfmeHostBH::bfmeSaveBH(BfmeAgentBH *ag)
{
	((Gen002B2080 *)this)->handle((FlagPairTarget *)ag);

	if (ag->bfmeSkipBH() != 0)
		return;

	BfmeInfoBH info;

	info.m_bfmeFlagBH = 1;
	info.m_bfmeLevelBH = 1;
	ag->bfmeFillBH(&info);

	ag->bfmeMarkBH(m_bfmeSlotABH);
	m_bfmeSubOneBH.bfmeSaveBH(ag);
	m_bfmeSubTwoBH.bfmeSaveBH(ag);
	ag->bfmeByteBH(&m_bfmeSlotDBH);

	if (ag->bfmeReadingBH() != 0)
	{
		unsigned char v;

		ag->bfmeByteBH(&v);

		if (v == m_bfmeStateBH)
			return;

		if (v != 0)
			bfmeOnBH();
		else
			bfmeOffBH();
	}
	else
		ag->bfmeByteBH(&m_bfmeStateBH);
}
