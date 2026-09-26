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

// Other six-argument wrappers use the same shape, but retain their own
// address-derived type until their retail owners can be identified.
#define BFME_FORWARD_SIX(ADDR, SLOT)                                         \
class Rva##ADDR##VirtualForwarder                                             \
{                                                                            \
public:                                                                      \
	virtual void slot00(void *, int, int, int, int, int);                     \
	virtual void slot01(void *, int, int, int, int, int);                     \
	virtual void slot02(void *, int, int, int, int, int);                     \
	virtual void slot03(void *, int, int, int, int, int);                     \
	virtual void slot04(void *, int, int, int, int, int);                     \
	virtual void slot05(void *, int, int, int, int, int);                     \
	virtual void slot06(void *, int, int, int, int, int);                     \
	virtual void slot07(void *, int, int, int, int, int);                     \
	virtual void slot08(void *, int, int, int, int, int);                     \
	void *forward_##ADDR(void *result, int a2, int a3, int a4, int a5,       \
		int a6);                                                               \
};                                                                           \
void *Rva##ADDR##VirtualForwarder::forward_##ADDR(                            \
	void *result, int a2, int a3, int a4, int a5, int a6)                    \
{                                                                            \
	slot##SLOT(result, a2, a3, a4, a5, a6);                                  \
	return result;                                                            \
}

BFME_FORWARD_SIX(00845470, 08)
BFME_FORWARD_SIX(008454A0, 07)
BFME_FORWARD_SIX(008454D0, 06)
