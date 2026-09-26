// BFME 0x00192900: Xfer transfer for the snapshot array.
// The frame mirror is deliberately TU-local.  Its first int is the count
// slot and its XferVersion follows at +4, matching the retail stack reuse.
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte version;
	UnsignedByte currentVersion;
	UnsignedByte pad[2];
};

struct BfmeVersionFrame
{
	int count;
	XferVersion version;
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __stdcall _CxxThrowException(void *, void *);

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

	BfmeEntryBJ *bfmeItemBJ(int i, int offset)
	{
		BfmeEntryBJ *candidate = reinterpret_cast<BfmeEntryBJ *>(
			reinterpret_cast<UnsignedByte *>(this) + 0x24 + offset);

		if (i < 0 || i >= m_bfmeCountBJ)
			return 0;

		return candidate;
	}

	unsigned char m_bfmeHeadBJ[0x20];
	int m_bfmeCountBJ;
	BfmeEntryBJ m_bfmeArrayBJ[66];
	unsigned char m_bfmePadBJ[0xc];
	Bool m_bfmeFlagBJ;
};

// ?xfer@BfmeHostBJ@@QAEXPAVXfer@@@Z
void BfmeHostBJ::xfer(Xfer *x)
{
	if (x->isLightCRC())
		return;

	BfmeVersionFrame versionFrame;
	versionFrame.version.version = 1;
	versionFrame.version.currentVersion = 1;
	x->xferVersion(&versionFrame.version);
	versionFrame.count = m_bfmeCountBJ;
	x->xferInt(&versionFrame.count);

	if (versionFrame.count != m_bfmeCountBJ)
	{
		BfmeFormattedText error;

		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
		__assume(0);
	}

	int i = 0;
	register int offset = 0;
	while (i < versionFrame.count)
	{
		BfmeEntryBJ *entry;
		if (offset < 0 || *reinterpret_cast<volatile int *>(&i) >= m_bfmeCountBJ)
			entry = 0;
		else
			entry = reinterpret_cast<BfmeEntryBJ *>(
				reinterpret_cast<UnsignedByte *>(this) + 0x24 + offset);
		BfmeSnapshotBJ *item = entry->m_bfmeItemBJ;
		Bool present = (item != 0);

		x->xferBool(&present);

		if (item == 0)
		{
			if (present == true)
				goto mismatch;
		}
		else
		{
			if (!present)
				goto mismatch;
		}
		if (present)
			x->xferSnapshot(item);

		++i;
		offset += 0x18;
	}

	x->xferBool(&m_bfmeFlagBJ);
	return;

mismatch:
	{
		BfmeFormattedText error;

		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
		__assume(0);
	}
}
