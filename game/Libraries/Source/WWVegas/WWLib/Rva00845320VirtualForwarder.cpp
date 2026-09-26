// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// A six-argument forwarding member with an independently witnessed virtual
// slot at +0x20. Its enclosing type is not established by the call alone.
class Rva00845320VirtualForwarder
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
	virtual void forwardSlot(void *result, int a2, int a3, int a4,
		int a5, int a6);

	void *forward_00845320(void *result, int a2, int a3, int a4,
		int a5, int a6);
};

void *Rva00845320VirtualForwarder::forward_00845320(
	void *result, int a2, int a3, int a4, int a5, int a6)
{
	forwardSlot(result, a2, a3, a4, a5, a6);
	return result;
}
