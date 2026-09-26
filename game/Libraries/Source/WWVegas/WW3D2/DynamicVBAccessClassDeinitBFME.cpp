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

extern BfmeDX8VertexBuffer *BfmeDynamicDX8VertexBuffer[];
extern unsigned int BfmeDynamicFVFTable[];
extern bool BfmeDynamicDX8VertexBufferInUse[];
extern unsigned short BfmeDynamicDX8VertexBufferSize[];
extern unsigned short BfmeDynamicDX8VertexBufferOffset[];
extern BfmeDynElemXZ BfmeDynamicVBSlots[];

extern SortingVertexBufferClass *BfmeDynamicSortingVertexArray;
extern bool BfmeDynamicSortingVertexArrayInUse;
extern unsigned short BfmeDynamicSortingVertexArraySize;
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
