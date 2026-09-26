// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// The unproven owner has a virtual call at vtable offset 0x2c. The wrapper
// forwards eight arguments and returns the caller's first pointer argument.
class Rva008447E0VirtualForwarder
{
public:
	virtual void reserved00();
	virtual void reserved04();
	virtual void reserved08();
	virtual void reserved0c();
	virtual void reserved10();
	virtual void reserved14();
	virtual void reserved18();
	virtual void reserved1c();
	virtual void reserved20();
	virtual void reserved24();
	virtual void reserved28();
	virtual void forwardSlot(void *result, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8);

	void *forward_008447E0(void *result, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8);
};

void *Rva008447E0VirtualForwarder::forward_008447E0(
	void *result, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	forwardSlot(result, a2, a3, a4, a5, a6, a7, a8);
	return result;
}
