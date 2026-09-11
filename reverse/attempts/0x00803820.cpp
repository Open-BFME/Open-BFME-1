// ?bfmeInitVLB@BfmeThingVLB@@QAEPAV1@EPAVBfmeOwnerUNC@@@Z
// partial score=0.92 date=2026-09-11
// cl: /O2 /GX-
// Retail 0x00803820: BfmeThingVLB initialisation.

#include <new>

class BfmeOwnerUNC
{
};

class BfmeThingUNC
{
public:
	BfmeThingUNC(int value, BfmeOwnerUNC *owner);
};

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class BfmeThingVLB
{
public:
	BfmeThingVLB *bfmeInitVLB(unsigned char flag, BfmeOwnerUNC *owner);

private:
	void *m_vft;
	void * volatile m_vftSecondary;
	unsigned char m_flag;
	unsigned char m_padding[3];
	BfmeOwnerUNC *m_owner;
	int m_field10;
	int m_field14;
	void *m_inner;
};

BfmeThingVLB *BfmeThingVLB::bfmeInitVLB(unsigned char flag, BfmeOwnerUNC *owner)
{
	m_vftSecondary = (void *)0x0112B9C0;
	m_vft = (void *)0x0112C738;
	m_vftSecondary = (void *)0x0112C728;
	m_field10 = 0;
	m_field14 = 0;
	m_flag = flag;
	m_padding[0] = 0;
	m_owner = owner;
	void *raw = Gen007F0130::operator new(0x194);
	m_inner = raw != 0 ?
		(void *)new (raw) BfmeThingUNC((int)this, owner) : (void *)0;
	return this;
}
