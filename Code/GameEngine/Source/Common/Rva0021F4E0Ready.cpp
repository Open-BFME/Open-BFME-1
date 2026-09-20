// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x0021F4E0. The callers prove a readiness predicate, but they do not
// prove a semantic owner, so the class keeps the retail address in its name.

extern const float BfmeZeroRange;

class Rva0021F4E0Range
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual float range();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual int mode();
};

class Rva0021F4E0Owner
{
public:
	bool has(int value);

	unsigned char m_head[0x200];
	Rva0021F4E0Range *m_range;
};

class Rva0021F4E0Sub
{
public:
	bool test(void *first, void *second);
};

class Rva0021F4E0
{
public:
	char ready(void *first, void *second);

	unsigned char m_head[8];
	Rva0021F4E0Owner *m_owner;
	unsigned char m_middle[0x14];
	Rva0021F4E0Sub m_sub;
};

#pragma comment(linker, "/alternatename:?test@Rva0021F4E0Sub@@QAE_NPAX0@Z=?j_000237b8@@YAXXZ")
#pragma comment(linker, "/alternatename:?has@Rva0021F4E0Owner@@QAE_NH@Z=?j_0003251f@@YAXXZ")

char Rva0021F4E0::ready(void *first, void *second)
{
	if (m_sub.test(first, second) == 0)
		goto fail;
	if (m_owner->m_range->range() <= BfmeZeroRange)
		goto fail;
	if (m_owner->m_range->mode() == 2 && m_owner->has(0x4e) == 0)
		goto fail;
	goto success;
fail:
	return 0;
success:
	return 1;
}
