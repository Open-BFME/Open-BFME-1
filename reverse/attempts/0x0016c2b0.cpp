// ?d_0016c2b0@@YAXXZ
// partial score=0.93 date=2026-09-02
// ?d_0016c2b0@@YAXXZ (0x0016C2B0, 29 bytes)
// ghidra: FUN_0056c2b0
// score: 0.93 (27/29 bytes, extra mov eax, ecx before virtual call)

class TargetInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual bool slot7() = 0; // vtable+0x1c
};

struct SubClass
{
	unsigned char pad[0x1c];
	TargetInterface *m_inner;
};

class OuterClass
{
public:
	bool isNotReady() const;

	unsigned char pad[0x60];
	SubClass *m_sub;
};

bool OuterClass::isNotReady() const
{
	SubClass *s = m_sub;
	if (s && s->m_inner && !s->m_inner->slot7())
		return true;
	return false;
}
