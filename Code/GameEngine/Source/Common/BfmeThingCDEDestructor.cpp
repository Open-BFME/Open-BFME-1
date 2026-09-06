// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// ?bfmeDtorCDE@BfmeThingCDE@@QAEXXZ
//
// The node at 0x008F7EC0 clears the same 0x10-byte entries that this
// destructor passes to the array-delete helper. Its Ghidra body has no
// source row, so the member call uses an address pin for that helper.

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *arg);
};

class CDELeading
{
public:
	virtual void f0();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class CDELinkNode
{
public:
	void *m_00;
	char m_pad04[8];
	void *m_0c;
	char m_pad10[4];
	void *m_14;
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
	void d_008f7990();
	void d_008f7ec0();

	void *m_owner;
	CDEProvider *m_ptr4;
	CDEProvider *m_ptr8;
	CDELinkNode *m_link0;
	CDELinkNode *m_link1;
	CDELinkNode *m_prev;
	CDELinkNode *m_next;
	void *m_array;
};

#pragma comment(linker, "/alternatename:?d_008f7990@BfmeThingCDE@@QAEXXZ=?d_008f7990@@YAXXZ")
#pragma comment(linker, "/alternatename:?d_008f7ec0@BfmeThingCDE@@QAEXXZ=?d_008f7ec0@@YAXXZ")
#pragma comment(linker, "/alternatename:?ArrayDeleteHelperBodyThunk@@YGXPAXII0@Z=?ArrayDeleteHelperBodyThunk@@YAXXZ")

void __stdcall ArrayDeleteHelperBodyThunk(void *, unsigned, unsigned, void *);
extern void __cdecl operator delete[](void *);

void BfmeThingCDE::bfmeDtorCDE()
{
	d_008f7990();
	if (m_ptr4 != 0)
		m_ptr4->f3(0);
	if (m_ptr8 != 0)
	{
		m_ptr8->f3(0);
		m_ptr8->f0();
		m_ptr8 = 0;
	}
	d_008f7ec0();
	if (m_array != 0)
	{
		void *cookie = (char *)m_array - 4;
		ArrayDeleteHelperBodyThunk(m_array, 0x10, *(unsigned *)cookie,
			reinterpret_cast<void *>(0x00CF7BD0));
		::operator delete[](cookie);
	}
	if (m_prev != 0)
	{
		m_prev->m_00 = m_next;
		if (m_next != 0)
			m_next->m_14 = m_prev;
		m_prev = 0;
	}
	if (m_link1 != 0)
		m_link1->m_0c = m_link0;
	m_link0->m_00 = m_link1;
}
