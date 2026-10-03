// cl: /DNDEBUG /MD /EHsc

class BfmeSubCLE;

// 0x0002E85C is retail's 5-byte ILT thunk (?j_0002e85c@@YAXXZ).  The
// __thiscall member behind it has no proven name, so the call is routed
// through the thunk's address with a member-pointer thunk.
extern void j_0002e85c();

class BfmeXCLE
{
public:
	bool runCLE(BfmeSubCLE *condition, void *object, int index)
	{
		typedef bool (BfmeXCLE::*Call)(BfmeSubCLE *, void *, int);
		union { void *raw; Call method; } u;
		u.raw = (void *)j_0002e85c;
		return (this->*u.method)(condition, object, index);
	}
};

char __stdcall bfmeBannerCarrierCondition(
	BfmeSubCLE *object, BfmeXCLE *required, void *condition)
{
	if (object != 0 && condition != 0 && required != 0)
		return required->runCLE(object, condition, 0) != 0;
	return false;
}