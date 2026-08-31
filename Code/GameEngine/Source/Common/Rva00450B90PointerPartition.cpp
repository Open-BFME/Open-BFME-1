// cl: /O2 /D_STLP_USE_STATIC_LIB
// stlport
// Retail's caller at 0x00451E60 supplies the bidirectional iterator tag and
// reaches this __partition body through the ILT at 0x00043004. The earlier
// synthetic __uninitialized_copy pin cannot describe the in-place pointer
// swaps; the three byte fields and six mask bits are all directly observable.
#include <algorithm>

struct Rva00450B90Item
{
	char m_beforeFlags[0x24];
	bool m_flag24;
	bool m_flag25;
	bool m_flag26;
};

class Rva00450B90Predicate
{
public:
	bool operator()(const Rva00450B90Item *item) const
	{
		if ((m_mask & 0x01) != 0 && item->m_flag26)
			goto selected26;
		if ((m_mask & 0x02) == 0 || item->m_flag26)
			return false;

	selected26:
		if ((item->m_flag24 && (m_mask & 0x04) != 0)
				|| (!item->m_flag24 && (m_mask & 0x08) != 0))
			return false;

		return !((item->m_flag25 && (m_mask & 0x10) != 0)
			|| (!item->m_flag25 && (m_mask & 0x20) != 0));
	}

	unsigned int m_mask;
};

typedef Rva00450B90Item **(*Rva00450B90PartitionFn)(
	Rva00450B90Item **, Rva00450B90Item **, Rva00450B90Predicate);

Rva00450B90PartitionFn Rva00450B90PartitionAnchor =
	&_STL::partition<Rva00450B90Item **, Rva00450B90Predicate>;
