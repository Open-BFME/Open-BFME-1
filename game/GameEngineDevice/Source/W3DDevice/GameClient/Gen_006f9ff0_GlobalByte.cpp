// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F9FF0. Return a global byte.

class WW3D
{
public:
	static bool Are_Static_Sort_Lists_Enabled() { return AreStaticSortListsEnabled; }

private:
	static bool AreStaticSortListsEnabled;
};

// ?get_006f9ff0@@YAEXZ
unsigned char get_006f9ff0(void)
{
	return WW3D::Are_Static_Sort_Lists_Enabled();
}
