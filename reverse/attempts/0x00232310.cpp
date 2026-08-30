// ?d_00232310@@YAXXZ
// partial score=0.96 date=2026-08-30
// cl: /DNDEBUG /MD /EHsc

class BfmeXCLE;
class BfmeRequired;
class BfmeSubCLE;

unsigned char __stdcall bfmeRunCLE(BfmeXCLE *object, BfmeSubCLE *condition, int index);

char __stdcall bfmeBannerCarrierCondition(
	BfmeXCLE *object, BfmeRequired *required, BfmeSubCLE *condition)
{
	if (object != 0 && condition != 0 && required != 0)
		return bfmeRunCLE(object, condition, required == 0) != 0;
	return false;
}
