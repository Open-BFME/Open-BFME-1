// cl: /DNDEBUG /MD
//
// W3DShrubBuffer, retail 0x0071CD20. Same record array W3DShrubBuffer::clearAllTrees
// walks (stride 0xA4 count at +0x1E1CC8 first entry at +0x15DC). Each live
// row's dword at DualType+0x0C becomes 1 when TheShroudManager is null.

typedef int Int;

class PartitionManager;
class RefCountClass;

extern PartitionManager *TheShroudManager;

struct ShrubRecordMeshes
{
	char m_padding00[4];
	RefCountClass *m_first;
	RefCountClass *m_second;
	Int m_visible;
	char m_padding10[0x94];
};

class W3DShrubBuffer
{
public:
	void stampShroudVisible(void);

private:
	char m_pad[0x15dc];
	ShrubRecordMeshes m_entries[11999];
	char m_pad2[0x10];
	Int m_count;
};

void W3DShrubBuffer::stampShroudVisible(void)
{
	for (Int i = 0; i < m_count; ++i)
		m_entries[i].m_visible = !TheShroudManager;
}
