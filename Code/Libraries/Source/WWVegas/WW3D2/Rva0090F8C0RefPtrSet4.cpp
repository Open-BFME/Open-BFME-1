// cl: /DNDEBUG /MD /EHsc

// Four REF_PTR_SET slots plus a signed count at +0x10, retail 0x0090F8C0.
// Add_Ref/Release_Ref match the NDEBUG inlines: inc/dec the dword at +4,
// Delete_This at vtable slot 0 when the count hits zero.

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0) {
			Delete_This();
		}
	}

private:
	int NumRefs;
};

#define REF_PTR_SET(dst,src)	{ if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }

class Rva0090F8C0Holder
{
public:
	void set(int count, RefCountClass *a, RefCountClass *b, RefCountClass *c, RefCountClass *d);

private:
	RefCountClass *m_a;
	RefCountClass *m_b;
	RefCountClass *m_c;
	RefCountClass *m_d;
	int m_count;
};

void Rva0090F8C0Holder::set(int count, RefCountClass *a, RefCountClass *b, RefCountClass *c, RefCountClass *d)
{
	if (count < 0) {
		return;
	}
	if (!a) {
		return;
	}
	m_count = count;
	REF_PTR_SET(m_a, a);
	REF_PTR_SET(m_b, b);
	REF_PTR_SET(m_c, c);
	REF_PTR_SET(m_d, d);
}
