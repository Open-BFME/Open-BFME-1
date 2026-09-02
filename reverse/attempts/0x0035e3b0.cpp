// ??0Gen0035E3B0@@QAE@PAVHost0035E450@@@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Host0035E450;

class DLinkAt4
{
public:
	DLinkAt4(void *other);

private:
	void *m_a;
	void *m_b;
};

class NestedAt0C
{
public:
	NestedAt0C(const NestedAt0C &other);
};

class NestedAt2C
{
public:
	NestedAt2C(const NestedAt2C &other);
};

class Base0035E3B0
{
public:
	Base0035E3B0(void *slot);
	virtual ~Base0035E3B0();

private:
	DLinkAt4 m_link;
};

Base0035E3B0::Base0035E3B0(void *slot)
	: m_link(slot)
{
}

class Gen0035E3B0 : public Base0035E3B0
{
public:
	Gen0035E3B0(Host0035E450 *other);

private:
	NestedAt0C m_at0C;
	char m_pad[0x2C - 0xC - sizeof(NestedAt0C)];
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
	: Base0035E3B0(other ? (char *)other + 4 : 0),
	  m_at0C(hostAt0C(other)),
	  m_at2C(hostAt2C(other))
{
}
