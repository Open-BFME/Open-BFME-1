class BfmeDX8VertexBuffer
{
public:
	virtual void bfmeDropXZ();

	int m_bfmeRefsXZ;
};

class BfmeDynElemXZ
{
public:
	void bfmeResetXZ(unsigned int fvf, int flag);

	unsigned char m_bfmePadXZ[0x40];
};

class SortingVertexBufferClass : public BfmeDX8VertexBuffer
{
};

class DynamicVBAccessClass
{
public:
	static void _Deinit();
};

// Retail RVA 0091DAA0 walks fifteen slots: VA 013467F0 through
// 01346BB0 in 0x40-byte steps, indexing pointer/word arrays once per slot.
// The tail accesses the sorting pointer at VA 013467DC and word capacity
// at VA 013467E0. All five storage extents are initially zero in retail.
BfmeDX8VertexBuffer *BfmeDynamicDX8VertexBuffer[15] = {};
extern unsigned int BfmeDynamicFVFTable[];
extern bool BfmeDynamicDX8VertexBufferInUse[];
unsigned short BfmeDynamicDX8VertexBufferSize[15] = {};
extern unsigned short BfmeDynamicDX8VertexBufferOffset[];
BfmeDynElemXZ BfmeDynamicVBSlots[15] = {};

SortingVertexBufferClass *BfmeDynamicSortingVertexArray = 0;
extern bool BfmeDynamicSortingVertexArrayInUse;
unsigned short BfmeDynamicSortingVertexArraySize = 0;
extern unsigned short BfmeDynamicSortingVertexArrayOffset;

void DynamicVBAccessClass::_Deinit()
{
	int i;

	for (i = 0; i < 15; i++)
	{
		BfmeDX8VertexBuffer *buf = BfmeDynamicDX8VertexBuffer[i];

		if (buf != 0)
		{
			if (--buf->m_bfmeRefsXZ == 0)
				buf->bfmeDropXZ();

			BfmeDynamicDX8VertexBuffer[i] = 0;
		}

		BfmeDynamicDX8VertexBufferInUse[i] = 0;
		BfmeDynamicDX8VertexBufferSize[i] = 0x1388;
		BfmeDynamicDX8VertexBufferOffset[i] = 0;

		BfmeDynamicVBSlots[i].bfmeResetXZ(BfmeDynamicFVFTable[i], 0);
	}

	SortingVertexBufferClass *sorting = BfmeDynamicSortingVertexArray;
	if (sorting != 0)
	{
		if (--sorting->m_bfmeRefsXZ == 0)
			sorting->bfmeDropXZ();

		BfmeDynamicSortingVertexArray = 0;
	}

	BfmeDynamicSortingVertexArrayInUse = 0;
	BfmeDynamicSortingVertexArraySize = 0;
	BfmeDynamicSortingVertexArrayOffset = 0;
}
