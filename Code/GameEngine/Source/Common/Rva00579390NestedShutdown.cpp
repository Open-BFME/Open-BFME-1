// Open-BFME5 clean C++ conversion of the retail body at 0x00579390.
//
// The owner carries two embedded interface subobjects.  Retail invokes slot 3
// on the subobject at +0x3AC, invokes slot 1 on the subobject at +0x25C, then
// tail-dispatches that same +0x25C address to the verified shutdown body.

class Rva00579390First
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
};

class Rva00579390Second
{
public:
	virtual void v0();
	virtual void v1();
};

class Gen_00525EE0
{
public:
	void bfmeShutdown(void);
};

class Rva00579390Owner
{
public:
	void bfmeNestedShutdown(void);

private:
	unsigned char m_beforeSecond[0x25C];
	Rva00579390Second m_second;
	unsigned char m_between[0x14C];
	Rva00579390First m_first;
};

void Rva00579390Owner::bfmeNestedShutdown(void)
{
	m_first.v3();
	m_second.v1();
	reinterpret_cast<Gen_00525EE0 *>(&m_second)->bfmeShutdown();
}
