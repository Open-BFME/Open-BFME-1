// cl: /DNDEBUG /MD /EHsc

class BfmeSubCLE;

class BfmeXCLE
{
public:
	bool bfmeRunCLE(BfmeSubCLE *condition, void *object, int index);
};

char __stdcall bfmeBannerCarrierCondition(
	BfmeSubCLE *object, BfmeXCLE *required, void *condition)
{
	if (object != 0 && condition != 0 && required != 0)
		return required->bfmeRunCLE(object, condition, 0) != 0;
	return false;
}
