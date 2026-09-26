// Retail RVA 0x00631F50. The prior bank labels are retained in the layout
// names, while the landed method carries the address token because ownership
// is not independently proven.
// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

struct Rva00631F50Value
{
	int m_bfmeValueFZ;
	unsigned char m_opaqueFZ[0x10];
	int m_bfmeKeyFZ;
};

typedef std::map<int, Rva00631F50Value> Rva00631F50Map;

class BfmeMapFZ
{
public:
	int *bfmeFindFZ_00631F50(int key);

	unsigned char m_bfmeHeadFZ[0x4c];
	Rva00631F50Map m_bfmeTreeFZ;
};

int *BfmeMapFZ::bfmeFindFZ_00631F50(int key)
{
	Rva00631F50Map::iterator node = m_bfmeTreeFZ.begin();

	while (node != m_bfmeTreeFZ.end())
	{
		Rva00631F50Value *value = &node->second;
		if (value->m_bfmeKeyFZ == key)
			return &value->m_bfmeValueFZ;

		++node;
	}

	return 0;
}
