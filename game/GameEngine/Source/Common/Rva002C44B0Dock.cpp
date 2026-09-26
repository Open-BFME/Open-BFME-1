// cl: /O2 /Ob0

class ContainRva002C44B0
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual bool testArg(void *arg);      // +0x18
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void useArg(void *arg);       // +0x2C
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3c();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4c();
	virtual void pad50();
	virtual void pad54();
	virtual void pad58();
	virtual void pad5c();
	virtual void pad60();
	virtual void pad64();
	virtual ContainRva002C44B0 *getInner(); // +0x68
};

class ObjRva002C44B0
{
public:
	char m_lead[0x1FC];
	ContainRva002C44B0 *m_contain;
};

class Rva002C44B0
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void usePair(void *a, void *b); // +0x14

	bool run(void *a, void *b, int *out);
};

bool Rva002C44B0::run(void *a, void *b, int *out)
{
	ContainRva002C44B0 *inner =
		(*(ObjRva002C44B0 **)((char *)this - 0x338))->m_contain->getInner();
	if (!inner)
		return false;
	if (!inner->testArg(a))
		inner->useArg(a);
	usePair(a, b);
	if (out)
		*out = 0;
	return true;
}
