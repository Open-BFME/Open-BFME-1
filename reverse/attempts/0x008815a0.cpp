// ?bfmeAccept@BfmeSinkA@@QAEXPAVBfmeFlagTarget@@@Z
// partial score=0.93 date=2026-09-04
// cl: /GX
//
// Reloc-named sink the already-matched describe wrappers at 0x00881040 and
// 0x008F7650 call. 0x008815A0 is the Taint-grid snapshot on the Gen_008812D0
// layout: not-LightCRC xfers the Region3D prefix, two cell-size floats,
// width/height, reallocates the cell array on load, and seeds every cell.
// LightCRC checksums each 8-byte row through CRC_Memory. A final IsLoading()
// visit walks the grid.
//
// MSVC 7.1 folds `new T[n]` onto scalar new unless operator new[] is declared
// (same lever as PathfindZoneManager_allocateBlocks_Thunk.cpp).

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};

class BfmeFlagTarget
{
public:
	virtual void slot00();
	virtual bool isLoading();					// slot 1, vtable+0x04
	virtual void slot02();
	virtual void slot03();
	virtual bool isLightCRC();					// slot 4, vtable+0x10
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(BfmeFlagPair *pair);		// slot 10, vtable+0x28
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void xferRegion(void *region);			// slot 22, vtable+0x58
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferReal(float *value);			// slot 27, vtable+0x6C
	virtual void slot28();
	virtual void xferUnsignedInt(unsigned int *value);	// slot 29, vtable+0x74
	virtual void xferInt(int *value);			// slot 30, vtable+0x78
};

class BfmeSeedTarget;

class Gen_00881C60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);			// matched 0x00881C60
};

class Gen_008812D0
{
public:
	void bfmeVisitCells();					// matched 0x00881410
};

class BfmeCellFC
{
public:
	BfmeCellFC();
	~BfmeCellFC();

	unsigned char m_bfmeKind;
	unsigned char m_bfmeGap[3];
	int m_bfmeValue;
};

BfmeCellFC::BfmeCellFC()
	: m_bfmeKind(0x80), m_bfmeValue(0)
{
}

BfmeCellFC::~BfmeCellFC()
{
}

unsigned long CRC_Memory(const unsigned char *data, unsigned long length,
	unsigned long crc);

class BfmeSinkA
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x008815A0

private:
	char m_bfmeRegion[0x18];				// +0x00
	float m_bfmeCellSize;					// +0x18
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	BfmeCellFC *m_bfmeCells;				// +0x28
};

// ?bfmeAccept@BfmeSinkA@@QAEXPAVBfmeFlagTarget@@@Z
void BfmeSinkA::bfmeAccept(BfmeFlagTarget *target)
{
	BfmeFlagPair pair;
	unsigned int scratch;

	if (!target->isLightCRC())
	{
		pair.m_bfmeFirst = true;
		pair.m_bfmeSecond = true;
		target->xferVersion(&pair);
		target->xferRegion(this);
		target->xferReal(&m_bfmeCellSize);
		target->xferReal(&m_bfmeCellSizeInv);

		int *height = &m_bfmeHeight;
		int *width = &m_bfmeWidth;
		target->xferInt(width);
		target->xferInt(height);

		scratch = 0;
		target->xferUnsignedInt(&scratch);

		if (target->isLoading())
		{
			delete[] m_bfmeCells;
			m_bfmeCells = new BfmeCellFC[*width * *height];
		}

		BfmeCellFC *cell = m_bfmeCells;
		scratch = 0;
		for (; scratch < (unsigned int)m_bfmeHeight; ++scratch)
		{
			for (unsigned int x = 0; x < (unsigned int)m_bfmeWidth;
				++x, ++cell)
			{
				reinterpret_cast<Gen_00881C60 *>(cell)->bfmeSeed(
					reinterpret_cast<BfmeSeedTarget *>(target));
			}
		}
	}
	else
	{
		scratch = 0;
		for (unsigned int y = 0; y < (unsigned int)m_bfmeHeight; ++y)
		{
			unsigned int width = (unsigned int)m_bfmeWidth;
			BfmeCellFC *cells = m_bfmeCells;
			scratch += CRC_Memory(
				reinterpret_cast<const unsigned char *>(cells + width * y),
				width << 3,
				0);
		}
		target->xferUnsignedInt(&scratch);
	}

	if (target->isLoading())
		reinterpret_cast<Gen_008812D0 *>(this)->bfmeVisitCells();
}
