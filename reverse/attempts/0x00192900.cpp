// ?xfer@BfmeHostBJ@@QAEXPAVXfer@@@Z (identity unknown)
// partial score=0.75 date=2026-09-07
// 308/279. This is a real Xfer::xfer snapshot-array transfer and the WHOLE
// shape is recovered -- isLightCRC guard, XferVersion{1,1}, the count round
// trip with the bfmeFormatText/_CxxThrowException assert, the bounds-checked
// accessor that returns NULL and is then dereferenced unguarded
// (xor eax,eax / mov edi,[eax+8]), the setne-built `present` byte, the
// four-way present/item cross-check with ONE shared throw block, and the
// trailing xferBool of the member at +0x660.
// The Xfer vtable model is the repo's own: slot 4 isLightCRC, 10 xferVersion,
// 12 xferSnapshot, 30 xferInt, 35 xferBool -- see
// Code/GameEngine/Source/Common/DozerAIUpdate_xferMethodThunk.cpp, which also
// carries the assert macro verbatim.
// Two residues, both allocation, worth ~29 bytes:
//   * frame slots -- SOLVED 2026-09-07. MSVC groups locals by size, so the
//     2-byte XferVersion was sinking below the 4-byte count and the 8-byte
//     error block. Padding XferVersion to 4 bytes puts it back at E-4 and
//     every stack displacement in the body then matches retail. Keep the pad.
//   * induction form. retail spills `i` to [esp+0x10] and keeps the SCALED
//     byte offset in ebp (`lea eax,[ebx+ebp+0x24]`); MSVC keeps `i` in ebx and
//     hoists the array base into a stack slot. `this` lands in ebx for retail
//     and ebp for MSVC, which is the same choice seen from the other side.
// Remaining: the induction form is the whole rest of the gap. retail builds a
// SCALED byte-offset IV in ebp (`test ebp,ebp / jl` for the i<0 check,
// `lea eax,[ebx+ebp+0x24]` for the element) and spills `i` to [esp+0x10] for
// the `i >= m_count` compare; MSVC never strength-reduces here, keeps `i` in
// ebx and hoists the array base into a slot instead. Naming the receiver in a
// local does NOT flip it (tried) -- the ebx/ebp role swap is a consequence of
// the IV choice, not the cause. Next lever: raise register pressure, or write
// the scaled offset explicitly as a second loop variable walked by 0x18.
// Open-BFME5: retail-layout C++ conversion of a snapshot-array transfer.
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersionBytes
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferVersion
{
	XferVersionBytes m_value;
	unsigned short m_pad;
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(void *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(int *);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

class BfmeSnapshotBJ;

struct BfmeEntryBJ
{
	unsigned char m_bfmeHeadBJ[8];
	BfmeSnapshotBJ *m_bfmeItemBJ;
	unsigned char m_bfmeTailBJ[0xc];
};

class BfmeHostBJ
{
public:
	void xfer(Xfer *x);

	BfmeEntryBJ *bfmeItemBJ(int i)
	{
		if (i < 0 || i >= m_bfmeCountBJ)
			return 0;

		return &m_bfmeArrayBJ[i];
	}

	unsigned char m_bfmeHeadBJ[0x20];
	int m_bfmeCountBJ;
	BfmeEntryBJ m_bfmeArrayBJ[66];
	unsigned char m_bfmePadBJ[0xc];
	Bool m_bfmeFlagBJ;
};

void BfmeHostBJ::xfer(Xfer *x)
{
	if (x->isLightCRC())
		return;

	XferVersion version;
	version.m_value.m_version = 1;
	version.m_value.m_currentVersion = 1;
	x->xferVersion(&version);

	int count = m_bfmeCountBJ;

	x->xferInt(&count);

	if (count != m_bfmeCountBJ)
	{
		BfmeFormattedText error;

		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	for (int i = 0; i < count; i++)
	{
		BfmeSnapshotBJ *item = bfmeItemBJ(i)->m_bfmeItemBJ;
		Bool present = (item != 0);

		x->xferBool(&present);

		if (item != 0)
		{
			if (!present)
			{
				BfmeFormattedText error;

				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}
		}
		else
		{
			if (present)
			{
				BfmeFormattedText error;

				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}
		}

		if (present)
			x->xferSnapshot(item);
	}

	x->xferBool(&m_bfmeFlagBJ);
}
