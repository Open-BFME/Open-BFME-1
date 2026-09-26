// cl: /EHs-c-

class Mem0090D090
{
public:
	~Mem0090D090();
};

class Mem009DB7A0
{
public:
	~Mem009DB7A0();
};

// The paired complete destructor at 0x0090E520 establishes this compact
// owner layout: the +0x3c subobject is destroyed first, then the head at +0.
// The scalar wrapper has no recovered public spelling, so the ledger keeps an
// address-derived body alias while the complete destructor and both member
// identities remain explicit.
class Rva0090E520
{
public:
	~Rva0090E520();
	Rva0090E520 *scalarDelete(unsigned flags);

private:
	Mem0090D090 m_head;
	char m_pad[59];
	Mem009DB7A0 m_tail;
};

void __cdecl operator delete(void *);

Rva0090E520 *Rva0090E520::scalarDelete(unsigned flags)
{
	this->~Rva0090E520();
	if (flags & 1)
		::operator delete(this);
	return this;
}

void ForceRva0090E520DeletingDestructor()
{
	Rva0090E520 value;
}
