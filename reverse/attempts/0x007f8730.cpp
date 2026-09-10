// ?rva007F8730@BfmeThingTWA@@QAEPAV1@PAX@Z
// partial score=0.9 date=2026-09-10
// Best real-C++ reconstruction for retail RVA 0x007F8730 (95 bytes).
// Owner identity is BfmeThingTWA: vtables 0x0112B8A4/0x0112B8A0
// resolve to its matched 0x007F8970 destructor and 0x007F8940 step body.
class Rva00803080
{
public:
	void * volatile m_vtable;
};

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *owner);
};

class Rva7F4CC0Child
{
public:
	Rva7F4CC0Child();
	virtual void v0();
	volatile int m_04;
	volatile int m_08;
	volatile int m_0c;
};

class BfmeStrTWA
{
public:
	void bfmeDtorTWA();
	char m_bfmePad[0x20];
};

class BfmeThingTWA
{
public:
	BfmeThingTWA *rva007F8730(void *serviceList);
	void *m_bfmeVft0;
	void *m_bfmeVft1;
	char m_bfmePad[8];
	BfmeStrTWA m_bfmeStr;
};

BfmeThingTWA *BfmeThingTWA::rva007F8730(void *serviceListArgument)
{
	Rva007EAServiceList &serviceList =
		*(Rva007EAServiceList *)serviceListArgument;
	Rva00803080 *owner = (Rva00803080 *)((char *)this + 4);

	owner->m_vtable = (void *)0x0112B89C;
	Rva7F4CC0Child &packet =
		*(Rva7F4CC0Child *)((char *)&m_bfmeStr);
	*(volatile int *)((char *)this + 0x00) = 0x0112B8A4;
	owner->m_vtable = (void *)0x0112B8A0;
	packet.Rva7F4CC0Child::Rva7F4CC0Child();
	*(volatile int *)&packet = 0x011296B0;
	packet.m_08 = 0;
	packet.m_0c = 0;
	packet.m_04 = 0;
	*(volatile int *)((char *)this + 0x0c) = 0;
	*(volatile int *)((char *)this + 0x08) = 0;
	*(volatile int *)((char *)this + 0x18) = 0;
	*(volatile int *)((char *)this + 0x1c) = 0;
	*(volatile int *)((char *)this + 0x20) = 0;
	*(volatile unsigned char *)((char *)this + 0x24) = 0;
	*(volatile int *)((char *)this + 0x28) = 0;
	*(volatile int *)((char *)this + 0x2c) = 0;
	serviceList.add(owner);
	return this;
}
