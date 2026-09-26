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

// These independent, otherwise-identical eight-argument forwarding bodies
// differ only in the virtual slot selected. Keep each owner's address in its
// type and symbol rather than assuming a shared retail class identity.
#define BFME_FORWARD_EIGHT(ADDR, SLOT)                                       \
class Rva##ADDR##VirtualForwarder                                             \
{                                                                            \
public:                                                                      \
	virtual void slot00(void *, int, int, int, int, int, int, int);           \
	virtual void slot01(void *, int, int, int, int, int, int, int);           \
	virtual void slot02(void *, int, int, int, int, int, int, int);           \
	virtual void slot03(void *, int, int, int, int, int, int, int);           \
	virtual void slot04(void *, int, int, int, int, int, int, int);           \
	virtual void slot05(void *, int, int, int, int, int, int, int);           \
	virtual void slot06(void *, int, int, int, int, int, int, int);           \
	virtual void slot07(void *, int, int, int, int, int, int, int);           \
	virtual void slot08(void *, int, int, int, int, int, int, int);           \
	virtual void slot09(void *, int, int, int, int, int, int, int);           \
	virtual void slot10(void *, int, int, int, int, int, int, int);           \
	virtual void slot11(void *, int, int, int, int, int, int, int);           \
	void *forward_##ADDR(void *result, int a2, int a3, int a4, int a5,       \
		int a6, int a7, int a8);                                               \
};                                                                           \
void *Rva##ADDR##VirtualForwarder::forward_##ADDR(                            \
	void *result, int a2, int a3, int a4, int a5, int a6, int a7, int a8)   \
{                                                                            \
	slot##SLOT(result, a2, a3, a4, a5, a6, a7, a8);                          \
	return result;                                                            \
}

BFME_FORWARD_EIGHT(00844820, 10)
BFME_FORWARD_EIGHT(00844860, 09)
BFME_FORWARD_EIGHT(008448A0, 08)
BFME_FORWARD_EIGHT(008448E0, 07)
BFME_FORWARD_EIGHT(00844920, 02)
