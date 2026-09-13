// cl: /DNDEBUG /MD
//
// Retail 0x0071CD20. Same DualType array BaseHeightMapResetBuffer::clear3098
// walks (stride 0xA4 count at +0x1E1CC8 first entry at +0x15DC). Each live
// row's dword at DualType+0x0C becomes 1 when TheShroudManager is null.

typedef int Int;

class PartitionManager;
class RefCountClass;

extern PartitionManager *TheShroudManager;

struct BaseHeightMapResetDualType
{
	char m_padding00[4];
	RefCountClass *m_first;
	RefCountClass *m_second;
	Int m_visible;
	char m_padding10[0x94];
};

class BaseHeightMapResetBuffer
{
public:
	void stampShroudVisible(void);

private:
	char m_pad[0x15dc];
	BaseHeightMapResetDualType m_entries[11999];
	char m_pad2[0x10];
	Int m_count;
};

void BaseHeightMapResetBuffer::stampShroudVisible(void)
{
	for (Int i = 0; i < m_count; ++i)
		m_entries[i].m_visible = !TheShroudManager;
}
