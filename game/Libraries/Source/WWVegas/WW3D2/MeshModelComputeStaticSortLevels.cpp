// cl: /DNDEBUG /MD /EHsc

// MeshModelClass::compute_static_sort_levels, retail 0x0096DD80 (59 B): the
// Zero Hour meshmdlio.cpp body. Retail stores the sort level byte at +0x1C
// (MeshModelPostProcess0096E750.cpp documents the same field); the shared
// meshmdl.h view puts SortLevel at +0x20, so this TU keeps a local view and
// game meshmdlio.cpp no longer carries its own (+0x20) copy.

#define SORT_LEVEL_NONE 0
#define SORT_LEVEL_BIN1 20
#define SORT_LEVEL_BIN2 15
#define SORT_LEVEL_BIN3 10

class MeshModelClass
{
public:
	unsigned char m_pad00[0x1C];
	unsigned char SortLevel;

protected:
	unsigned int get_sort_flags(int pass) const;
	unsigned int get_sort_flags(void) const;
	void compute_static_sort_levels(void);
};

void MeshModelClass::compute_static_sort_levels(void)
{
	enum StaticSortCategoryBitFieldType
	{
		SSCAT_OPAQUE_BF		= (1 << 0),
		SSCAT_ALPHA_TEST_BF	= (1 << 1),
		SSCAT_ADDITIVE_BF		= (1 << 2),
		SSCAT_SCREEN_BF		= (1 << 3),
		SSCAT_OTHER_BF			= (1 << 4)
	};

	if (get_sort_flags(0) == SSCAT_OPAQUE_BF) {
		SortLevel = SORT_LEVEL_NONE;
		return;
	}

	switch (get_sort_flags())
	{
	case (SSCAT_OPAQUE_BF | SSCAT_ALPHA_TEST_BF):
		SortLevel = SORT_LEVEL_NONE;
		break;

	case SSCAT_ADDITIVE_BF:
		SortLevel = SORT_LEVEL_BIN3;
		break;

	case SSCAT_SCREEN_BF:
		SortLevel = SORT_LEVEL_BIN2;
		break;

	default:
		SortLevel = SORT_LEVEL_BIN1;
		break;
	};
}
