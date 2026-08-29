// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Both calls go through the same Miles import slot.  Retail preserves the
// first preference while querying the second and returns their product.
extern "C" __declspec(dllimport) int __stdcall AIL_get_preference(
	unsigned int preference);

int bfmeMilesPreferenceProduct_006962A0()
{
	return AIL_get_preference(0x2A) * AIL_get_preference(0x22);
}
