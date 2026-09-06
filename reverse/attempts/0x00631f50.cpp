// ?bfmeFindFZ@BfmeMapFZ@@QAEPAHH@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 58/58 exact size; esi and edi are transposed throughout.
// Pin: ?bfmeIncrementFZ@@YAPAUBfmeNodeFZ@@PAU1@@Z,0x0082B870 (_Rb_global::_M_increment)
struct BfmeNodeFZ
{
	unsigned char m_bfmeHeadFZ[8];
	BfmeNodeFZ *m_bfmeFirstFZ;
	unsigned char m_bfmeMidFZ[8];
	int m_bfmeValueFZ;
	unsigned char m_bfmeTailFZ[0x10];
	volatile int m_bfmeKeyFZ;
};

BfmeNodeFZ *__cdecl bfmeIncrementFZ(BfmeNodeFZ *node);

class BfmeMapFZ
{
public:
	int *bfmeFindFZ(int key);

	unsigned char m_bfmeHeadFZ[0x4c];
	BfmeNodeFZ *m_bfmeTreeFZ;
};

int *BfmeMapFZ::bfmeFindFZ(int key)
{
	BfmeNodeFZ *node = m_bfmeTreeFZ->m_bfmeFirstFZ;

	while (node != m_bfmeTreeFZ)
	{
		int nodeKey = node->m_bfmeKeyFZ;
		int *value = &node->m_bfmeValueFZ;

		if (nodeKey == key)
			return value;

		node = bfmeIncrementFZ(node);
	}

	return 0;
}
