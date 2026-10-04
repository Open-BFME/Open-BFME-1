class BfmeDX8VertexBuffer
{
public:
	virtual void bfmeDropXZ();

	int m_bfmeRefsXZ;
};

class BFMEVertexFVFInfo
{
public:
	void Rva00964150(unsigned int fvf, unsigned int vertex_size);

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
// Retail .rdata VA 0113BD28: RVA 0091DACB reads one dword per
// iteration of the fifteen-slot loop below. Preserve external const linkage.
extern const unsigned int BfmeDynamicFVFTable[15] = {
	0x002, 0x012, 0x112, 0x212, 0x152, 0x252, 0x142, 0x242,
	0x102, 0x202,
	// D3DFVF_* values: inputs/reference/shims/d3d8_shim_validated.h:63-85.
	// XYZ + normal + diffuse, four texture coordinates; coordinates 1-3 have size 3.
	0x052 | 0x400 | (1u << 18) | (1u << 20) | (1u << 22),
	0xB0312, 0x052, 0x344, 0x444
};
extern bool BfmeDynamicDX8VertexBufferInUse[];
unsigned short BfmeDynamicDX8VertexBufferSize[15] = {};
extern unsigned short BfmeDynamicDX8VertexBufferOffset[];
BFMEVertexFVFInfo BfmeDynamicVBSlots[15] = {};

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

		BfmeDynamicVBSlots[i].Rva00964150(BfmeDynamicFVFTable[i], 0);
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
