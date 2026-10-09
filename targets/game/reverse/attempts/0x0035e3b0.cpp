// ??0Gen0035E3B0@@QAE@PAVHost0035E450@@@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc

class Host0035E450;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
static __forceinline void *rva0035E3B0Link(Host0035E450 *other)
{
	Host0035E450 *source = other;
	return source ? (char *)source + 4 : 0;
}

class DLinkAt4
{
public:
	DLinkAt4(void *other);
	~DLinkAt4();

private:
	void *m_a;
	void *m_b;
};

class NestedAt0C
{
public:
	NestedAt0C(const NestedAt0C &other);
	~NestedAt0C();
private:
	unsigned char m_data[0x20];
};

class NestedAt2C
{
public:
	NestedAt2C(const NestedAt2C &other);
private:
	unsigned char m_data[0x20];
};

class Base0035E3B0
{
public:
	__forceinline Base0035E3B0() { _ReadWriteBarrier(); }
	virtual ~Base0035E3B0();
};


class Gen0035E3B0 : public Base0035E3B0, public DLinkAt4
{
public:
	Gen0035E3B0(Host0035E450 *other);
	virtual ~Gen0035E3B0();

private:
	NestedAt0C m_at0C;
	NestedAt2C m_at2C;
};

static NestedAt0C &hostAt0C(Host0035E450 *other)
{
	return *(NestedAt0C *)((char *)other + 0xC);
}

static NestedAt2C &hostAt2C(Host0035E450 *other)
{
	return *(NestedAt2C *)((char *)other + 0x2C);
}

Gen0035E3B0::Gen0035E3B0(Host0035E450 *other)
	: DLinkAt4(rva0035E3B0Link(other)),
	  m_at0C(hostAt0C(other)),
	  m_at2C(hostAt2C(other))
{
}
