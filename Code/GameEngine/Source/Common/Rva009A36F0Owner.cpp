// cl: /O2 /Ob0
// Retail 0x009A36F0 (?d_009a36f0@@YAXXZ, dump d_0099d0c0.asm).
// Full control-flow decode (verified against tools/dis_retail.py):
//   this = ebx (a large object; the only fields it touches are a list-head
//   pointer at +8 and a flag byte at +0xC06D -- both address-derived, no
//   semantic class identity proven).
//   param (edi, the one stack arg, ret 4) exposes two virtual slots: +0x18
//   (void f(int), called with 0) and +0x1c (returns a "thing" pointer).
//   If param is null, or the +0x1c call returns null, the function is a
//   no-op.  Otherwise it calls param->slot18(0), then:
//     - if this->m_flag is set: link `thing` into the doubly-linked list
//       rooted at this+8 (same back-slot/next idiom as the landed
//       Rva009A3770HashChainInsert.cpp), unless it is already linked
//       (thing->m_10 != 0), then zero thing->m_4;
//     - else: call the still-dump unlinker at 0x009A3630 (ecx=this), the
//       matched dtor ??1Rva009A45A0CollisionData@@QAE@XZ on `thing`, then
//       operator delete(thing).
// callees: 0x009A3630 (dump, pinned below as unlinkChain), 0x009A2390
// (matched CollisionData dtor), 0x00881EB0 (operator delete).
// landed neighbour Rva009A3770HashChainInsert.cpp supplies the link idiom.

class Rva009A36F0Thing
{
public:
	unsigned char m_pad0[4];
	int m_4;
	unsigned char m_pad8[8];
	void *m_10;
	Rva009A36F0Thing *m_14;
};

class Rva009A36F0Param
{
public:
	virtual void slot0();
	virtual void slot4();
	virtual void slot8();
	virtual void slotc();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(int);
	virtual Rva009A36F0Thing *slot1c();
};

class Rva009A45A0CollisionData
{
public:
	void destroyDirect();
};

void __cdecl operator delete(void *block);

class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
	void unlinkChain(Rva009A36F0Thing *thing);

private:
	unsigned char m_pad0[8];
	Rva009A36F0Thing *m_listHead;
	unsigned char m_padToFlag[0xc06d - 0xc];
	unsigned char m_flag;
};

void Rva009A36F0Owner::apply(Rva009A36F0Param *param)
{
	if (param == 0)
		return;

	Rva009A36F0Thing *thing = param->slot1c();
	if (thing == 0)
		return;

	param->slot18(0);

	if (m_flag)
	{
		if (thing->m_10 == 0)
		{
			Rva009A36F0Thing **slot = (Rva009A36F0Thing **)&m_listHead;

			thing->m_10 = slot;

			Rva009A36F0Thing *head = *slot;
			thing->m_14 = head;
			if (head != 0)
				head->m_10 = &thing->m_14;

			*slot = thing;
		}

		thing->m_4 = 0;
		return;
	}

	unlinkChain(thing);
	((Rva009A45A0CollisionData *)thing)->destroyDirect();
	operator delete(thing);
}
